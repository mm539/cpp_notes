#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
using namespace std;

/*
  I was trying to code to avoid a deadlock and instead I got a deadlock.
  -_-
  
  I don't know what I'm doing wrong here... save this for another time.
*/


class Result{
  private:
    mutex _mutex;
    double _result;
  public:
    double getResult(){ return _result; }
    void printResult();
    void divideByNumber(double num, double denom);
};

void Result::printResult(){
  _mutex.lock();
  cout << "Result: " << getResult() << endl;
  _mutex.unlock();
}

void Result::divideByNumber(double num, double denom){
  _mutex.lock();
  try
  {
    if (denom == 0) throw invalid_argument("Cannot divide by 0.");
    _result = num / denom;
    printResult();
    
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  _mutex.unlock();
  
}

int main(){
  // PART 1: DEADLOCK PROBLEM

  // PART 2: SOLUTION
  vector<future<void>> ftrs;
  Result r;

  for (int i = -5; i < 5; i++){
    ftrs.emplace_back( async(launch::async, &Result::divideByNumber, &r, 50,i) );
  }

  for (auto &ftr: ftrs) ftr.wait();
  return 0;
}