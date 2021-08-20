#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
using namespace std;

/*
   I'm reall not sure what the udacity example is trying to show.
   it just unlocks and locks the mutex... per the lecture notes, there are many things that can be done with unique_locks

   the output is still mangled, as writing to cerr and cout occurs simultaneously.

*/

mutex mtx;
double result;

void printResult(int denom){
  cout << "result for denom " << denom << " is " << result << endl;
}

void divideByNumber(int numer, int denom){
  try
  {
    if (denom == 0) throw invalid_argument("Cannot divide by 0.");

    unique_lock<mutex> lck(mtx);
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