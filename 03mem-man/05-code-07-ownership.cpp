#include <iostream>
#include <memory>
using namespace std;

class MyClass{
    int member_;
  public:
    MyClass(int val){ member_ = val; }
    void printVal(){ cout << ", managed object at " << this << " with val = " << member_ << endl; }
};

void f(unique_ptr<MyClass> ptr){
  cout << "unique_ptr " << &ptr;
  ptr->printVal();
}

int main(){
  unique_ptr<MyClass> uniquePtr = make_unique<MyClass>(555);
  cout << "unique_ptr " << &uniquePtr;
  uniquePtr->printVal();

  f(move(uniquePtr));

  if (uniquePtr) cout << "hells yeah, still valid!\n";
  // pointer is no longer valid. it is an empty shells

  return 0;
}