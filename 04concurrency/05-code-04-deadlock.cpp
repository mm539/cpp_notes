#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
using namespace std;

/*
  Note: Earlier, I made a mental mistake and thought it was necessary to lock the mutexes in the printResult function. This is not necessary.


  *** Deadlock example #1:

  In this example, the divideByNumber function throws an error and returns before it can unlock the mutex, causing a deadlock.

  I don't really understand the purpose of the return statement included on line 44. If not for that, this would not be a deadlock scenario.

  The solution to this problem is to use a lock_guard, as seen in 05-code-06-lock-guard.cpp (however, this solution still results in mangled output from the error message)
*/

mutex _mutex;
double result;

void printResult(int denom){
  cout << "for denom = " << denom << ", the result is: " << result << endl;
}

void divideByNumber(double numer, int denom){
  _mutex.lock();
  try{
    if (denom == 0) throw invalid_argument("Cannot divide by 0.");
    result = numer / denom;
    this_thread::sleep_for(chrono::milliseconds(1));
    printResult(denom);
  }
  catch(const std::exception& e){
    std::cerr << e.what() << '\n';
    return; // <--- simulate code without a try-catch block?
  }
  _mutex.unlock();
}

int main(){
  vector<future<void>> ftrs;

  for (int i = -5; i < 5; i++){
    ftrs.emplace_back( async(launch::async, divideByNumber, 50, i) );
  }

  for (auto &ftr: ftrs) ftr.wait();
  return 0;
}