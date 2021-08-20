#include <iostream>
#include <future>
#include <thread>
#include <string>
using namespace std;

// Vehicle has a member that is a pointer.

class Vehicle{
  private:
    int _id;
    string *_name;
  public:
    Vehicle(): _id(0), _name(new string("default name")){}
    Vehicle(int id, string name): _id(id), _name(new string(name)){}

    void setID(int id){ _id = id; }
    int getID(){ return _id; }
    void setName(string name){ *_name = name; }
    string getName(){return *_name; }
};

int main(){
  Vehicle v1(1, "one");

  auto fn = [](Vehicle v){
    this_thread::sleep_for(chrono::milliseconds(200));
    v.setName("thread vehicle");
  };

  future<void> ftr = async(fn, v1);

  cout << "vehicle name: " << v1.getName() << endl;
  v1.setName("main thread vehicle");
  cout << "vehicle name: " << v1.getName() << endl;
  ftr.wait();
  cout << "vehicle name: " << v1.getName() << endl;
  return 0;
}