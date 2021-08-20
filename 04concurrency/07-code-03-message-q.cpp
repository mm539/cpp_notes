#include <thread>
#include <future>
#include <mutex> // #include <memory> ??
#include <iostream>
#include <queue> // #include <vector> <-- redundant
#include <time.h>
using namespace std;

/*
  This protocol (including a queue) solves the problems I was encountering with what I used in 07-code-01-cond-var.cpp.

*/

template<class T>
class MessageQueue{
  private:
    mutex _mutex;
    condition_variable _cond;
    queue<T> _queue;
  public:
    T receive(){
      unique_lock<mutex> uLock(_mutex);
      _cond.wait(uLock, [this](){ return !_queue.empty(); });
      int msg = _queue.front();
      _queue.pop();
      cout << "message : " << msg << " received\n"; 
      return msg;
    }
    void send(T&& msg){
      // simulate messages coming in at different times
      // what happens if there is no time delay here? :)
      int t = 300 + rand() % 5000;
      this_thread::sleep_for(chrono::milliseconds(t));

      lock_guard<mutex> lck(_mutex);
      this_thread::sleep_for(chrono::milliseconds(100));
      cout << "sending message " << msg << " to the queue\n";
      _queue.emplace(move(msg));
      _cond.notify_one();
    }
};

int main(){
  srand( time(NULL) );
  vector<future<void>> ftrs;
  shared_ptr<MessageQueue<int>> queue(new MessageQueue<int>);

  for (int i = 0; i < 100; i++){
    int msg = i;
    ftrs.emplace_back( async(launch::async, &MessageQueue<int>::send, queue, move(msg)) );
  }

  while(true){
    int msg = queue->receive();
  }

  for(auto &ftr: ftrs) ftr.wait();

  cout << "Finished Waiting\n";
  return 0;
}