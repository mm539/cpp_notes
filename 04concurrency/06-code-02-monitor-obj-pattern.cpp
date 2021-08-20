#include <mutex>
#include <thread>
#include <future>
#include <queue>
#include <vector>
#include <iostream>
#include <memory>
#include <time.h>
using namespace std;

/*
  
  Monitor object.

  1. The udacity code used a vector, and thus the queue was LIFO.
  That bugged me, so I implemented a real queue, which is FIFO.

  2. The vehicles get added at random times.

  3. added a counter so that program will eventually terminate.

  STILL, this code is not optimal. Depending on the time delay we put in the polling loop, it will either put too much load on the processor OR not be as responsive as we would like it to be.

  The solution to this is to use a condition variable, which can be used to implement a protocol in which the main thread only wakes up when a vehicle is waiting in the queue.

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
    queue<Vehicle> _vehicles;
    int _count;
    mutex _mutex;
  public:
    void decrementCount(){ _count--; }
    bool countZeroed(){ return _count == 0;}
    void setCount(int c){ _count = c; }

    bool dataIsAvailable(){
      lock_guard<mutex> lck(_mutex);
      return !_vehicles.empty();
    }

    Vehicle popFront(){
      lock_guard<mutex> lck(_mutex);

      Vehicle v = move(_vehicles.front());
      _vehicles.pop();
      decrementCount();
      return v;
    }
    void pushBack(Vehicle &&v){
      int r = 500 + rand() % 5000;
      this_thread::sleep_for(chrono::milliseconds(r));

      lock_guard<mutex> lck(_mutex);
      cout << "r: " << r << endl;
      cout << "vehicle #" << v.getID() << " will be added to the queue\n";
      _vehicles.emplace(move(v));
    }
};

int main(){
  srand( time(NULL) );
  int c = 10; // number of vehicles

  vector<future<void>> ftrs;
  shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
  queue->setCount(c);

  for (int i = 0; i < c; i++){
    Vehicle v(i);
    ftrs.emplace_back( async(launch::async, &WaitingVehicles::pushBack, queue, move(v)) );
  }

  while(true){
    if( queue->dataIsAvailable() ){
      Vehicle v = move(queue->popFront());
      cout << v.getID() << " has been removed from the queue.\n";
    }

    if( queue->countZeroed() ){ break; }

    int t = 2000;
    this_thread::sleep_for(chrono::milliseconds(t));
  }

  for (auto &ftr: ftrs) ftr.wait();

  return 0;
}