#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
// why don't i have to include <memory> ?
using namespace std;

/*
  This example uses std::timed_mutex instead of std::mutex.

*/

class Vehicle{
  private:
    int _id;
  public:
    Vehicle(int id): _id(id) {}
    int getID(){ return _id; }
};

class WaitingVehicles{
  private:
    vector<Vehicle> _vehicles;
    timed_mutex _mutex;

  public:
    void printSize(){
      _mutex.lock();
      cout << "nVehicles: " << _vehicles.size() << endl;
      _mutex.unlock();
    }
    void pushBack(Vehicle &&v){
      for(int i = 0; i < 3; i++){
        if ( _mutex.try_lock_for(chrono::milliseconds(3)) ){
          _vehicles.emplace_back(move(v));
          _mutex.unlock();
          break;
        }else{
          cout << "attempt for vehicle id " << v.getID() << " failed\n";
          this_thread::sleep_for(chrono::milliseconds(2));
        }
        
      }
    }
};

int main(){
  shared_ptr<WaitingVehicles> _queue(new WaitingVehicles);
  vector<future<void>> ftrs;

  for(int i = 0; i < 1000; i++){
    Vehicle v(i);
    ftrs.emplace_back( async(launch::async, &WaitingVehicles::pushBack, _queue, move(v)) );
  }

  for (auto &ftr: ftrs) ftr.wait();

  _queue->printSize();
  return 0;
}