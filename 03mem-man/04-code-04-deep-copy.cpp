#include <iostream>
using namespace std;


class DeepCopy{
  private:
    int * myInt_;
  public:
    DeepCopy(){ myInt_ = (int*)malloc(sizeof(int)); }
    DeepCopy(int val){
      cout << "constructor called" << endl;
      myInt_ = (int*)malloc(sizeof(int));
      *myInt_ = val;
      cout << "resource allocated at address: " << myInt_ << endl;
    }
    ~DeepCopy(){
      cout << "destructor called" << endl;
      free(myInt_);
      cout << "resource deallocated: " << myInt_ << endl;
    }
    DeepCopy(DeepCopy &source){
      cout << "copy constructor called" << endl;
      myInt_ = (int*)malloc(sizeof(int));
      cout << "resource allocated at address: " << myInt_ << endl;
      *myInt_ = *(source.myInt_);
    }
    DeepCopy& operator=(DeepCopy &source){
      cout << "copy assignment operator" << endl;
      myInt_ = (int*)malloc(sizeof(int));
      cout << "resource allocated at address: " << myInt_ << endl;
      *myInt_ = *(source.myInt_);
      return *this;
    }
};

int main(){
  DeepCopy source(42);
  DeepCopy dest1(source);

  DeepCopy dest2;
  dest2 = dest1;
  return 0;
}