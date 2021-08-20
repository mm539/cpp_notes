#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

/*
  In most cases, your code should only hold one lock on a mutex at a time. Occasionally you can nest your locks, for example by calling a subsystem that protects its internal data with a mutex while holding a lock on another mutex, but it is generally better to avoid locks on multiple mutexes at the same time, if possible. Sometimes, however, it is necessary to hold a lock on more than one mutex because you need to perform an operation on two different data elements, each protected by its own mutex.

  Deadlock example #2:

  In this example:
    - ThreadA locks mutex2 
    - ThreadB locks mutex1
    
    - ThreadA waits to lock mutex1
    - ThreadB waits to lock mutex2

    - They wait forever because these mutexes will never be unlocked.
*/

mutex mutex1, mutex2;

void ThreadA(){
  mutex2.lock();
  cout << "Thread A\n";
  mutex1.lock();
  cout << "Thread A locked mutex1\n";
  mutex2.unlock();
  mutex1.unlock();
}

void ThreadB(){
  mutex1.lock();
  cout << "Thread B\n";
  mutex2.lock();
  cout << "Thread b locked mutex2\n";
  mutex1.unlock();
  mutex2.unlock();
}


int main(){
  thread tA( ThreadA );
  thread tB( ThreadB );

  tA.join();
  tB.join();
  return 0;
}