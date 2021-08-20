#include <iostream>
using namespace std;

class SharedCopy{
  private:
    int * myInt_;
    static int cnt_;
  public:
    SharedCopy(int val);
    ~SharedCopy();
    SharedCopy(SharedCopy &source);
    // the copy assigment operator is missing!
    // this is a violation of the rule of 3
    // it should be created here!
};

int SharedCopy::cnt_ = 0;

SharedCopy::SharedCopy(int val){
  cout << "constructor called\n";
  myInt_ = (int*)malloc(sizeof(int));
  *myInt_ = val;
  ++ cnt_;
  cout << "resource allocated at address: " << myInt_ << endl;
}

SharedCopy::~SharedCopy(){
  cout << "destructor called\n";
  -- cnt_;
  if (cnt_ == 0){
    free(myInt_);
    cout << "resource deallocated at address: " << myInt_ << endl;
  }
}

SharedCopy::SharedCopy(SharedCopy &source){
  cout << "copy operator called\n";
  myInt_ = source.myInt_;
  cout << "myInt_ address: " << myInt_ << endl;
  ++ cnt_;
}

int main(){

  SharedCopy source(42);
  SharedCopy destination1(source);
  SharedCopy destination2(source);
  SharedCopy destination3(source);
  return 0;
}