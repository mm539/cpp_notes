#include <iostream>
#include <memory>
#include <string>
using namespace std;

class MyClass{
    string text_;
  public:
    MyClass(){}
    MyClass(string text){ text_ = text; }
    MyClass& operator=(MyClass &source){ 
      cout << "copy assignment operator used\n";
      text_ = source.text_;
      return *this;
    }
    ~MyClass(){ cout << this << " " << text_ << " destructor called\n";}
    void setText(string text){ text_ = text; }
};

int main(){
  unique_ptr<MyClass> unique1(new MyClass());
  unique_ptr<MyClass> unique2(new MyClass("string 2"));
  // a better way to make unique pointers is with the function std::make_unique
  // unique_ptr<MyClass> bob = make_unique<MyClass>(55);
  // When instantiated with make_shared or make_unique, smart pointer resource acquisition occurs at the same time that the object is initialized.

  unique1->setText("string 1");
  *unique1 = *unique2;

  cout << "objects have stack addresses at " << unique1.get() << " and " << unique2.get() << endl;
  cout << "testing" << endl;

  return 0;
}