#include <future>
#include <iostream>
#include <thread>
using namespace std;

/*
  Observe:
    1. compare with promises; promise set-up, promise exception handling
    2. std::launch
*/

double divide(double num, double denom){
  cout << "worker thread id: " << this_thread::get_id() << endl;

  this_thread::sleep_for(chrono::milliseconds(1000));
  if (denom == 0) throw runtime_error("Cannot divide by Zero!");
  return num / denom;
}

int main(){
  cout << "main thread id: " << this_thread::get_id() << endl;

  // example 1: basics
  double num = 42, denom = 0;
  future<double> ftr = async(divide, num, denom);
  try
  {
    double result = ftr.get();
    cout << "result: " << result << endl;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  // example 2: std::launch
  cout << "\n";
  auto fn = [](int delay){
    this_thread::sleep_for(chrono::milliseconds(delay));
    cout << "thread id: " << this_thread::get_id() << endl;
    return delay + 1.1;
  };

  future<double> ftr1 = async(launch::async, fn, 4000);
  future<double> ftr2 = async(launch::deferred, fn, 30);
  cout << ftr1.get() << endl;
  cout << ftr2.get() << endl;
  
  return 0;
}