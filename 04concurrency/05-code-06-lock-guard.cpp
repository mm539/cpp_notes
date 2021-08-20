#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
using namespace std;

mutex mtx;
double result;

void printResult(int denom){
  cout << "result for denom " << denom << " is " << result << endl;
}

void divideByNumber(int numer, int denom){
  try
  {
    lock_guard<mutex> lck(mtx); // is there any significance to the placement of this lock_guard?
    if (denom == 0) throw invalid_argument("Cannot divide by 0.");
    result = numer / denom;
    printResult(denom);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return;
  }
  
}

int main(){
  vector<future<void>> ftrs;

  for (int i = -5; i < 5; i++){
    ftrs.emplace_back( async(launch::async, divideByNumber, 50, i) );
  }

  for (auto &ftr: ftrs) ftr.wait();
  return 0;
}