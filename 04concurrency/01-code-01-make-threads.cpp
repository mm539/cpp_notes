#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>
using namespace std;

/*
  In this file, we see:
    A. how to pass a function to a thread
    B. how to add threads to a vector
    C. the important of joining

  Note about compiling and executing:
    i. compile in WSL
      g++ -pthread program_name

      "pthread adds support for multithreading, setting flags for both the preprocessor and linker"

    ii. run in WSL
*/

void f1(){
  this_thread::sleep_for(chrono::milliseconds(1000));
  cout << "f1 work completed!\n";
}

void f2(int n){ // because the thread constructor is a variadic template, we can pass f2 and its argument to it.
  int elapsed_time{0};

  for (int i = 0; i < n; i++){
    this_thread::sleep_for(chrono::milliseconds(300));
    elapsed_time += 300;
    cout << elapsed_time << endl;
  }
  cout << "f2 work for thread id " << this_thread::get_id() << " completed!\n";
}

int main(){
  cout << "Number of cores available for concurrency: " << thread::hardware_concurrency() << endl;

  /* A. what can be supplied to the thread constructor as its fn argument to instantiate a thread?
    1. lambda
    2. fn
    3. ... ?
    
    see 02-notes-01-callable-objects.txt for more details
  */

  // 1. lambda function
  thread t1([](){
    int count = 0;
    while(count < 3){
      this_thread::sleep_for(chrono::milliseconds(300));
      cout << count << endl;
      count++;
      // what happens to the CPU% utilization when a time delay is added to the while loop?
    }
    cout << "t1 counting completed!\n";
  });
  t1.join(); // <---- what happens if join is commented out?

  // 2. a function
  thread t2(f1);
  t2.join();

  thread t3(f2, 4);
  t3.join();

  // B. emplacing threads onto a vector
  cout << endl;

  vector<thread> threads;
  unsigned int n_threads = 3;
  for (int i = 0; i < n_threads; i++){
    threads.emplace_back(thread(f2, 2) );
  }
  // observe: what is special about the output to terminal for this example?
  // ANSWER: non-deterministic behavior!

  for_each(threads.begin(), threads.end(), [](thread &t){t.join();});
  // for (auto& th : threads) th.join();


  // C. joining is required!
  thread tt([](){});
  this_thread::sleep_for(chrono::milliseconds(1000)); // <-- put main to sleep
  // even though thread tt had no real work to do (and therefore finished first)and main had 1000ms of work to do, the program still crashed! joining is required by design by the makers of c++ to make debugging multi-threaded programs easier

  // the requirement for joining can be turned off by the detach function.


  return 0;
}