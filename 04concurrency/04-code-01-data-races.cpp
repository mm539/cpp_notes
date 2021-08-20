#include <iostream>
#include <future>
#include <thread>
using namespace std;

/*
  Here are basic examples of data races. They are a bit contrived.

  To see an example of a more realistic scenario, see 04-code-02-data-races.cpp, which involves passing a data structure with a member variable that is a pointer.

*/

class Vehicle{
  private:
    int _id;
  public:
    Vehicle(): _id(0){}
    void setID(int id){ _id = id; }
    int getID(){ return _id; }
};

int main(){
  Vehicle v0;

  auto fn = [](Vehicle *v, bool sleep){
    if (sleep) this_thread::sleep_for(chrono::milliseconds(500));
    v->setID(5);
  };

  // EXAMPLE 1
  future<void> ftr0 = async(fn, &v0, true);
  // async doesn't accept fns with pass-by-reference params

  cout << "v0 id: " << v0.getID() << endl;
  v0.setID(33);
  cout << "v0 id: " << v0.getID() << endl;
  ftr0.wait();
  cout << "v0 id: " << v0.getID() << endl;

  // EXAMPLE 2
  cout << "\n";
  v0.setID(0);

  future<void> ftr1 = async(fn, &v0, false);
  this_thread::sleep_for(chrono::milliseconds(10));
  cout << "v0 id: " << v0.getID() << endl;
  v0.setID(33);
  cout << "v0 id: " << v0.getID() << endl;
  ftr1.wait();
  cout << "v0 id: " << v0.getID() << endl;
  return 0;
}