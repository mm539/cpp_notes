#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
using namespace std;

/*


*/

class Vehicle{
  private:
    int _id;
  public:
    Vehicle(int id): _id(id) {}
    void printID(){ cout << "vehicle ID: " << _id << endl; }
};

class WaitingVehicles{
  private:
    vector<Vehicle> _vehicles;
    mutex _stdMutex;
    timed_mutex _tMutex;
    recursive_mutex _rMutex;
    recursive_timed_mutex _rtMutex;
  public:
    int getSize(){
      int nVehicles;
      _stdMutex.lock();
      nVehicles = _vehicles.size();
      _stdMutex.unlock();
      return nVehicles;
    }
};

int main(){
  return 0;
}