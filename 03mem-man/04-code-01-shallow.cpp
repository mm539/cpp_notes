#include <iostream>
#include <stdlib.h>

using namespace std;

// default copy aka shallow copy

class MyClass{
  private:
    int *myInt_;
  public:
    MyClass(){
      myInt_ = (int*)malloc(sizeof(int));
    }
    ~MyClass(){
      free(myInt_);
    }
    void printOwnAddress(){ cout << "Own address on the stack: " << this << endl; }
    void printMemberAddress(){ cout << "Managing memory block on the heap: " << myInt_ << endl; }
};

int main(){

  MyClass myClass1;
  myClass1.printOwnAddress();
  myClass1.printMemberAddress();

  MyClass myclass2(myClass1); // copy constructor
  myclass2.printOwnAddress();
  myclass2.printMemberAddress();

  // what will the addresses be?

  return 0;
}