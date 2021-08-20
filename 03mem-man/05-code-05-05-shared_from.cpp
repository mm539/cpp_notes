#include <iostream>
#include <memory>
using namespace std;

/*
  This example shows how to pass "this" as a pointer for a class managed my a shared_ptr.

  Steps:
    1. add inhertitance from:
        std::enable_shared_from_this<ClassName>
    2. make a function that returns shared_from_this()

Utility? look at line 24

*/
class MyClass;
void Send(shared_ptr<MyClass> src){ cout << src.use_count() << endl; }

class MyClass: public enable_shared_from_this<MyClass>{
  private:
    int _id;
  public:
    shared_ptr<MyClass> get_shared_this(){ return shared_from_this(); }
    void DummyFunction(){ Send( get_shared_this() ); }
    // void invalidPassing(){ Send( this ); } // <---- no suitable constructor exists to convert from MyClass* to shared_ptr<MyClass>
};


int main(){
  //shared_ptr<MyClass> c1;
  shared_ptr<MyClass> c1 = make_shared<MyClass>();

  shared_ptr<MyClass> c2 = c1->get_shared_this();
  shared_ptr<MyClass> c3 = c1;
  cout << c1.use_count() << endl;

  c1->DummyFunction();

  return 0;
}
