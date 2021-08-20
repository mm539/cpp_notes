#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
using namespace std;

/*
  Basic steps to using a mutex:
    1. include the <mutex> header
    2. create a std::mutex
    3. lock the mutex using lock() before a read/write operation is called on the variable
    4. unlock the mutex using unlock() after the read/write operation is finished

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
    void printSize(){
      _mutex.lock();
      cout << "#vehicles = " << _vehicles.size() << endl;
      _mutex.unlock();
    }
    void pushBack(Vehicle &&v){
      for (int i = 0; i < 3; i++){
        if (_mutex.try_lock()){
          _vehicles.emplace_back(v);
          _mutex.unlock();
          break;
        } else{
          cout << "pushBack attempt failed for vehicle ID " << v.getID() << endl;
          this_thread::sleep_for(chrono::milliseconds(2));
        }
      }

    }
};

int main(){
  shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
  vector<future<void>> ftrs;
  int nVehicles = 1000;

  for (int i = 0; i < nVehicles; i++){
    Vehicle v(i);
    ftrs.emplace_back(async(launch::async, &WaitingVehicles::pushBack, queue, v));
  }

  for ( auto &ftr: ftrs) ftr.wait();

  queue->printSize();
  return 0;
}