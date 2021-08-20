#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

/*
  std::lock and adopt_lock should be used when a multiple threads needs access to TWO or more shared resources at the same time.

  1. How to use std::lock 
    i. pass the mutexes to the function std::lock
    ii. create an instance of lock_guard with std::adopt_lock as a parameter

  2. lock is blocking. 
  tB must wait for tA to finish.

  3. how is this different than using mutex1.lock and mutex2.lock as the first lines to execute in ThreadA?
    - perhaps there is something special about std::lock that makes it different? I don't know

  4. adopt_lock allows us to use lock_guard on already locked mutexes.
*/

mutex mutex1, mutex2;

void ThreadA(){
  lock(mutex1, mutex2);
  lock_guard<mutex> lock2(mutex2, adopt_lock);
  cout << "ThreadA: created lock guard 2\n";
  lock_guard<mutex> lock1(mutex1, adopt_lock);
  cout << "ThreadA: created lock guard 1\n";
  cout << "ThreadA: finished\n";
}

void ThreadB(){
  lock(mutex1, mutex2);
  lock_guard<mutex> lock1(mutex1, adopt_lock);
  cout << "ThreadB: created lock guard 1\n";
  lock_guard<mutex> lock2(mutex2, adopt_lock);
  cout << "ThreadB: created lock guard 2\n";
  cout << "ThreadB: finished\n";
}

int main(){

  thread tA(ThreadA);
  thread tB(ThreadB);

  tA.join();
  tB.join();

  return 0;
}