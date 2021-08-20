#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <time.h>
using namespace std;

/*
  I tried working this with shared_ptr for cond and mutex and it didn't work.
  Next attempt will be with a Shell class.
  Shell class successful.

  Observations:
    i. within addOne, if I put a time delay after locking the mutex, then a deadlock will most likely occur

    ii. waitForNotification should be called before addOne has a chance to lock the mutex, otherwise a deadlock will occur
      - how do get around this to ensure that the worker threads only notify when their notification is ready to be received?
        - a time delay before the mutex lock in addOne is an imprecise solution, that may break down if there sufficient threads launched.
        - maybe try something with a second mutex and notify all

    iii. the important of PRED and why this protocol deadlocks under certain conditions

    std::condition_variable::wait
    ...
      If pred is specified (2), the function only blocks if pred returns false, and notifications can only unblock the thread when it becomes true (which is specially useful to check against spurious wake-up calls). This version (2) behaves as if implemented as:

  In 07-code-03-message-q.cpp, a queue object is used with this construct... how will time delays affect its functionality?
  ANSWER: IT WORKS BEAUTIFULLY


*/

class Shell{
  private:
    int _count{0};
    condition_variable _cond;
    mutex _mutex;
  public:
    int getCount(){ return _count; }
    void waitForNotification(){
      cout << "calling waitForNotification\n";
      unique_lock<mutex> uLock(_mutex);
      _cond.wait(uLock);
      // cond.wait(unique_lock, pred); // LOOK ABOVE TO READ ABOUT PRED
      _count++;
      cout << "notification received; count incremented by 1; new count: " << _count << endl;
    }
    void addOne(){
      // without any sort of time delay, there is a deadlock
      // this_thread::sleep_for(chrono::milliseconds(100));
      // int t = 500 + rand() % 50000;
      // this_thread::sleep_for(chrono::milliseconds(t));

      lock_guard<mutex> lck(_mutex);
      // this_thread::sleep_for(chrono::milliseconds(t)); // <--- causes deadlock
      _cond.notify_one();
      cout << "calling notify_one\n";
    }
};

/*
Unsuccessful attempt with local variables and shared pointers for cond and mtx.

void receiveNotification(shared_ptr<condition_variable> cond, shared_ptr<mutex> mtx){...}

void doSomething(int i, shared_ptr<condition_variable> cond, shared_ptr<mutex> mtx){...}

*/

int main(){
  srand( time(NULL) );
  vector<future<void>> ftrs;
  shared_ptr<Shell> shell(new Shell);
  int count = 10;

  for (int i = 0; i < count; i++){
    ftrs.emplace_back( async(launch::async, &Shell::addOne, shell) );
  }
  

  while(true){
    shell->waitForNotification();
    if (shell->getCount() == count) break;
  }

  for (auto &ftr: ftrs) ftr.wait();

  cout << "\nfinished waiting\n";

  return 0;
}