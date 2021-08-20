#include <mutex>
#include <thread>
#include <future>
#include <vector>
#include <iostream>
#include <memory>
using namespace std;

/*
  WaitingVehicles comes close to being a monitor object. It has a major disadvantage:

  The main thread has to wait until all worker threads have completed their jobs. Only then can it access the added data in bulk (printIDs).

  Monitor objects are interactive. A system that is truly interactive has to react to events as they arrive. It should not wait until all threads have completed their jobs, but instead act immediately as soon as new data arrives.

  We can use an inifinite polling loop to achieve this interactivity.
  see 06-code-02-monitor-obj-pattern.cpp

*/

class Vehicle{
  private:
    int _id;
  public:
    Vehicle(int id): _id(id){}
    int getID(){ return _id; }
};

class WaitingVehicles{
  private:
    vector<Vehicle> _vehicles;
    mutex _mutex;
  public:
    void printIDs(){
      lock_guard<mutex> lck(_mutex);
      cout << "The following vehicles are waiting in the queue:\n";
      for (auto &v: _vehicles) cout << "\tvehicle id: " << v.getID() << endl;
    }
    void pushBack(Vehicle &&v){
      lock_guard<mutex> lck(_mutex);
      cout << "vehicle #" << v.getID() << " will be added to the queue\n";
      _vehicles.emplace_back(move(v));
      this_thread::sleep_for(chrono::milliseconds(200));
    }
};

int main(){
  vector<future<void>> ftrs;
  shared_ptr<WaitingVehicles> queue(new WaitingVehicles);

  for (int i = 0; i < 10; i++){
    Vehicle v(i);
    ftrs.emplace_back( async(launch::async, &WaitingVehicles::pushBack, queue, move(v)) );
  }

  for (auto &ftr: ftrs) ftr.wait();
  cout << endl;

  queue->printIDs();

  return 0;
}