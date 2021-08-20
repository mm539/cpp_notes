#include <iostream>
#include <thread>
using namespace std;

// will we see the cout from threadFn?

void threadFn(){
  this_thread::sleep_for(chrono::milliseconds(200));
  cout << "Finished the work in the thread\n";
}

int main(){
  thread t(threadFn);
  t.detach();

  this_thread::sleep_for(chrono::milliseconds(50));
  cout << "Finished work in main\n";

  return 0;
}