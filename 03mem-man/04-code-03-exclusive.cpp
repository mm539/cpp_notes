
#include <iostream>
using namespace std;

class ExclusiveCopy{
  private:
    int *myInt_;
  public:
    ExclusiveCopy(){
      cout << "constructor called: " << this << endl;
      myInt_ = (int*)malloc(sizeof(int));
      cout << "resource allocated" << endl;
    }
    ~ExclusiveCopy(){
      cout << "destructor called: " << this << endl;
      if (myInt_ != nullptr){
        free(myInt_);
        cout << "resource deallocated" << endl;
      }
    }
    ExclusiveCopy(ExclusiveCopy &ec){
      cout << "copy constructor called: " << this << endl;
      myInt_ = ec.myInt_;
      ec.myInt_ = nullptr;
    }
    ExclusiveCopy& operator=(ExclusiveCopy &source){ // copy assignment operator overload
      cout << "copy assignment operator called: " << this << endl;
      myInt_ = source.myInt_;
      source.myInt_ = nullptr;
      return *this;
    }
};

int main(){
  ExclusiveCopy source;
  ExclusiveCopy dest1(source); // calls copy constructor
  // ExclusiveCopy dest1 = dest2; // calls copy constructor
  
  ExclusiveCopy dest2; // calls constructor
  dest2 = dest1; // copy assignment operator

  return 0;
}