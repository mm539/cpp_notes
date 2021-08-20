#include <iostream>
#include <thread>
#include <string>
#include <vector>
using namespace std;


// 1. make a vector of threads
// 2. make a for loop, i < 10
// 3. in each iter, emplace_back a thread created with a lambda
// 4. join the threads

int main(){
  vector<thread> threads;

  for (size_t i = 0; i < 10; i++){
    threads.emplace_back([i](){
      this_thread::sleep_for(chrono::milliseconds(50));
      cout << "Hello from thread #" << i << endl;
    });
  }

  for (auto &t: threads) t.join();

  return 0;
}