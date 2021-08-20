#include <iostream>
#include <future>
#include <thread>
#include <cmath>
#include <chrono>
#include <vector>
#include <string>
using namespace std;

// ASSESSING THE ADVANTAGE OF PARALLEL EXECUTION

/*
  Observe:
    1. a vector of futures is initialized as vector<future<void>>

*/

void workerFunction(int n){
  cout << "worker thread id: " << this_thread::get_id() << endl;
  for(int i = 0; i < n; i++) sqrt(12345.6789);
}

struct LaunchParameters{
  int _nThreads, _nLoops;
  launch _launchType;
  LaunchParameters(int nThreads, int nLoops, launch launchType): _nThreads(nThreads), _nLoops(nLoops), _launchType(launchType) {}
};

void Execute(LaunchParameters &lp){
  cout << "main thread id: " << this_thread::get_id() << endl;
  chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

  // part 1: launch various tasks
  vector<future<void>> ftrs;
  launch launch_type = lp._launchType;
  string l_type = (launch_type == launch::async) ? "async" : "deferred";
  int nLoops = lp._nLoops, nThreads = lp._nThreads;
  cout << "nLoops = " << nLoops << " , nThreads = " << nThreads << " , " << l_type << endl;

  for (int i = 0; i < nThreads; i++){
    ftrs.emplace_back(async(launch_type, workerFunction, nLoops));
  }

  // part 2: wait for them to finish and record elapsed time
  for (const future<void> &ftr: ftrs) ftr.wait();
  chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
  cout << "Execution finished after " << duration <<" microseconds" << "\n\n";
}

int main(){
  LaunchParameters lp1(5, 1e7, launch::async);
  LaunchParameters lp2(5, 1e7, launch::deferred);
  LaunchParameters lp3(5, 10, launch::async);
  LaunchParameters lp4(5, 10, launch::deferred);

  Execute(lp1);
  Execute(lp2);
  Execute(lp3);
  Execute(lp4);

  return 0;
}