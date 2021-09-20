#include <iostream>
#include <thread>
#include <future>
#include <cmath>
using namespace std;

/*
  Observe:
    1. std::future_status

    2. What is the difference between using:
      i. ftr.get
      ii. ftr.wait
      iii. ftr.wait_for

      see 03-notes-02-prms-ftrs.txt

    3. When might we want to separate the waiting and the getting?

*/

void computeSqrt(promise<double> && prms, double d){
  this_thread::sleep_for(chrono::milliseconds(5000));
  prms.set_value(sqrt(d));
}


std::string ToString(future_status s){
  switch (s){
    case future_status::ready:   return "Ready";
    case future_status::timeout: return "Timeout";
    case future_status::deferred:return "Deferred";
    default:      return "unknown";
  }
}

int main(){

  double d = 43.5;

  // EXAMPLE 1
  cout << "EXAMPLE 1\n";
  promise<double> prms;
  future<double> ftr = prms.get_future();
  thread t(computeSqrt, move(prms), d);

  future_status status = ftr.wait_for(chrono::milliseconds(300));

  if (status == future_status::ready){
    cout << "Result: " << ftr.get() << endl;
  } else{
    cout << "Status: " << ToString(status) << endl;
    cout << "Result Unvailable\n";
  }

  t.join();

  return 0;
}
