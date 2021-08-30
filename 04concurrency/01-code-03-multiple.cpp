#include <iostream>
#include <thread>
#include <string>
#include <vector>
using namespace std;
/* 
  This example is about running multiple threads at once
  #forkjoinparallelism
*/

void printHello(){
  cout << "Hello from worker thread #" << this_thread::get_id() << endl; 
  // observe that the insertion operator << is used 3 times
  // if multiple threads are sending to cout, then the output can be out of order.
}

void printGoodbye(int i){
  this_thread::sleep_for(chrono::milliseconds(50));
  cout << "Goodbye from worker thread #" << i << endl;
}

int main()
{
  vector<thread> threads;

  // PART 1: HELLO (Problem with interleaving)
  for (size_t i = 0; i < 5; i++)
  {
    /*
    // push_back copies an object into a vector
      however, thread objects do not have a copy constructor
      so, the following code will cause a compile error

      thread t(printHello);
      threads.push_back(t);

      // a solution is to use move semantics here
      // another solution is to use emplace_back (which implicitly calls the move constructor)
    */

    threads.emplace_back(thread(printHello)); // emplace_back uses move semantics internally
  }

  cout << "Hello from Main thread #" << this_thread::get_id() << endl;

  for (auto &t : threads) t.join();

  /*
  *** Output from this program:
      Hello from Worker thread #Hello from Worker thread #140370329347840140370337740544
      Hello from Worker thread #140370320955136
      Hello from Worker thread #140370346133248
      Hello from Main thread #140370363660096
      Hello from Worker thread #140370312562432

  This is surely not the intended output.

  *** Properties of concurrent programs:
  1. order of execution of threads is non-deterministic
  2. threads may get preempted in the middle of execution and another thread may be selected to run. (this can happen when the hardware concurrency limit is reached and the OS attempts to simulate asynchroncity)

  These two properties pose a major problem with concurrent applications.

  A program may run correctly for thousands of times and suddenly due to a particular "interleaving" of threads, there might be a problem. From a debugging perspective, this is a big problem because the problem may be difficult to reproduce.
  */

  // clearing a vector:
  //threads.clear(); // <-- per cplusplus.com, memory reallocation and vector resizing is not guaranteed to happen with this
  vector<thread>().swap(threads); // clear x, reallocate memory


  // PART 2: GOODBYE (Solution: add time delay to fn)
  // note: although the time delay gives us the desired output, it is not a good solution to the problem of multiple threads accessing the same resource (in this case, cout)
  // what if each thread had spent more time sending to cout than the added time delay?
  // the solution, as will be seen later, is a message queue (that utilizes a monitor object pattern)
  
  for (int i = 0; i < 10; i++){
    threads.emplace_back(thread(printGoodbye, i) );
  }
  for (auto &t : threads) t.join();

  return 0;
}