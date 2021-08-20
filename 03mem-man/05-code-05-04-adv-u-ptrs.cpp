#include <iostream>
#include <memory>
#include <assert.h>
using namespace std;

class MyClass{
  public:
    unique_ptr<int> data_ = nullptr;
    MyClass(){}
    MyClass(int* data){ data_.reset(data); }

    void Print(){ cout << *data_.get() << endl;}
    //void SetData(unique_ptr<int>&& uptr){ cout << uptr.get() << "&&\n"; }
    void SetData(unique_ptr<int> uptr);

};

void MyClass::SetData(unique_ptr<int> uptr){
  data_.reset(uptr.release());
}

int main(){

  MyClass c1;
  assert(c1.data_ == nullptr);
  assert(c1.data_.get() == nullptr);

  unique_ptr<int> ui = make_unique<int>(25);
  assert( *ui == 25);
  MyClass c2(ui.release());
  c2.Print();

  ui.reset(new int(50));
  c1.SetData(move(ui));
  c1.Print();

  return 0;
}

/*
  ** std::unique_ptr.reset
      void reset (pointer p = pointer()) noexcept;

      Destroys the object currently managed by the unique_ptr (if any) and takes ownership of p.

      If p is a null pointer (such as a default-initialized pointer), the unique_ptr becomes empty, managing no object after the call.

  ** std::unique_ptr.release
      pointer release() noexcept;

      Releases ownership of its stored pointer, by returning its value and replacing it with a null pointer.

      This call does not destroy the managed object, but the unique_ptr object is released from the responsibility of deleting the object. Some other entity must take responsibility for deleting the object at some point.

      To force the destruction of the object pointed, either use member function reset or perform an assignment operation on it.




*/