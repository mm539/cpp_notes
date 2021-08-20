#include <iostream>
#include <thread>
#include <future>
#include <string>
using namespace std;
/*
  -> overwriting the copy constructor to make a deep copy

  Observe:
    1. the copy constructor signature param MUST have "const", otherwise there will be a compile error related to async. Why?
*/
class Vehicle{
  private:
    string *_name;
  public:
    Vehicle(): _name(new string("default name")) {}
    Vehicle(Vehicle const &src); // copy constructor

    string getName(){ return *_name; }
    void setName(string name){ *_name = name; }
};

Vehicle::Vehicle(Vehicle const &src){
  if (src._name != nullptr) _name = new string(*src._name);
}

int main(){
  Vehicle v0;

  std::future<void> ftr = std::async(launch::async, [](Vehicle v) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work
        v.setName("Vehicle 2");
    },v0);

  v0.setName("main thread vehicle");
  ftr.wait();
  cout << v0.getName() << endl;
  return 0;
}
