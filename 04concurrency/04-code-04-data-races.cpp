#include <thread>
#include <future>
#include <iostream>
#include <string>
using namespace std;

/*
  avoiding data races by using move semantics and overriding the move constructor

  1. raw ptr example
  2. unique ptr example
    - take notice of how a parameter list can be used in the move constructor

*/

class Vehicle{
  private:
    string *_name;
  public:
    Vehicle():_name(new string("default name")){}
    Vehicle(string name): _name(new string(name)){
      cout << "vehicle name: " << *_name << endl;
    }

    //
    Vehicle(Vehicle &&src){
      cout << *src._name << " : Move Constructor called\n";
      if (src._name != nullptr){
        _name = new string(*src._name);
        src._name = nullptr;
      }
      else _name = new string;
    }

    void setName(string name){*_name = name; }
    string getName(){ return _name == nullptr ? "vehicle has no name" : *_name; }
};

class UniqueVehicle{
  private:
    unique_ptr<string> _name;
  public:
    UniqueVehicle(){}
    UniqueVehicle(string name): _name(make_unique<string>(name)){
      cout << "vehicle name: " << *_name << endl;
    }

    /*/ ALTERNATIVE IMPLEMENTATION
    UniqueVehicle(UniqueVehicle &&src): _name(move(src._name)){
      cout << *_name << " : Move constructor called\n";
    }*/
    UniqueVehicle(UniqueVehicle &&src){
      _name.swap(src._name);
      cout << *_name << " : Move constructor called\n";
    }

    void setName(string name){ 
      if (_name == nullptr) _name.reset(new string(name));
      else *_name = name; 
    }
    string getName(){return _name == nullptr ? "vehicle has no name" : *_name; }
};

int main(){

  //  EXAMPLE 1: RAW POINTER
  Vehicle v0("rover");

  auto fn = [](Vehicle v){v.setName("cruiser");};

  future<void> ftr = async(fn, move(v0));
  ftr.wait();
  cout << "vehicle name: " << v0.getName() << endl;

  // EXAMPLE 2: UNIQUE POINTER
  cout << endl;

  UniqueVehicle uv0("duck car");
  
  auto fn1 = [](UniqueVehicle uv){uv.setName("unique cruiser");};
  future<void> ftr1 = async(fn1, move(uv0));
  ftr1.wait();
  cout << "vehicle name: " << v0.getName() << endl;

  return 0;
}