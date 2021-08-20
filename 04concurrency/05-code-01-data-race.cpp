#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include<algorithm>
using namespace std;

/*

  This is an example of an object (a vector) being accessed by multiple threads at the same time.

  It's useful to introduce time delays to concurrent programs for debugging. In this example, if the program is run without sleep_for, it will appear to run correctly the vast majority of the time, thus masking the data race.

  If we launch the tasks with deferred, then there is no bug.
*/

class Vehicle{
  private:
    int _id;
  public:
    Vehicle(int id): _id(id){}
};

class WaitingVehicles{
  private:
    vector<Vehicle> _vehicles;
    int _tmpVehicles{0};
  public:
    void printSize(){ cout << "#vehicles = " << _tmpVehicles << endl; }
    void pushBack(Vehicle &&v){
      // _vehicles.push_back(move(v)); // <--- if uncommented, this line crashes the program
      int oldNum = _tmpVehicles; // <--- simulate concurrent access by multiple threads without crashing the program
      this_thread::sleep_for(chrono::milliseconds(1)); // strangely, without this line, the program APPEARS to run correctly.
      _tmpVehicles = oldNum + 1;
    }
};

int main(){
  // launch launch_type = launch::deferred;
  launch launch_type = launch::async;
  shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
  vector<future<void>> ftrs;

  for(int i = 0; i < 1000; i++){
    Vehicle v(i);
    ftrs.emplace_back(async(launch_type, &WaitingVehicles::pushBack, queue, move(v)));
  }

  for(auto &ftr: ftrs) ftr.wait();

  queue->printSize();
  return 0;
}