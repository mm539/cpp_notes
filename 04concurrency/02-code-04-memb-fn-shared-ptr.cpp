#include <iostream>
#include <thread>
#include <string>
using namespace std;

/*
  How can we ensure that the objects v1,v2 will exist throughout the lifetime of the threads? -> shared ptrs

  Because I'm new to concurrency, I can't think of a situation where we'd have to worry about this problem. :/
*/

class Vehicle{
  private:
    int _id;
  public:
    Vehicle(): _id(0) {}
    void setID(int id){ _id = id;}
    void printID() { cout << "id: " << _id << endl; }
};

int main(){

  Vehicle v0;
  shared_ptr<Vehicle> v1 = make_shared<Vehicle>();
  shared_ptr<Vehicle> v2(new Vehicle);

  thread t0(&Vehicle::setID, &v0, 0); // <-- reference to object
  thread t1(&Vehicle::setID, v1, 1); // <-- CANNOT pass a reference to a shared_ptr here.
  thread t2 = thread(&Vehicle::setID, v2, 2);

  t0.join();
  t1.join();
  t2.join();
 
  return 0;
}