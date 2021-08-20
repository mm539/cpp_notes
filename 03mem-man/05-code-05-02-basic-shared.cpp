#include <iostream>
#include <memory>
using namespace std;

class MyClass{
  public:
    ~MyClass() { cout << "Destructor of MyClass called\n";}
};

class MyClassProb{
public:
    std::shared_ptr<MyClassProb> _member;
    ~MyClassProb() { std::cout << "Destructor of MyClassProb called" << std::endl; }
};

int main(){
  // PART 1 : MAKING A SHARED POINTER
  cout << "PART 1\n";
  // std::shared_ptr<int> shared1(new int); // alternative way. this way is bad for concurrency.
  shared_ptr<int> shared1 = make_shared<int>();
  cout << "shared pointer count : " << shared1.use_count() << endl;
  {
    shared_ptr<int> shared2 = shared1;
    cout << "shared pointer count : " << shared1.use_count() << endl;
  }
  cout << "shared pointer count : " << shared1.use_count() << "\n\n";

  // PART 2 : RESET
  cout << "PART 2\n";
  shared_ptr<MyClass> myclass1 = make_shared<MyClass>();
  cout << "shared pointer count : " << myclass1.use_count() << "\n";
  
  myclass1.reset(new MyClass); // reset calls the destructor of the managed resource
  cout << "shared pointer count : " << myclass1.use_count() << "\n";

  // PART 3 : PROBLEMS WITH SHARED POINTER MEM MANAGEMENT
  shared_ptr<MyClassProb> mcp1(new MyClassProb);
  shared_ptr<MyClassProb> mcp2(new MyClassProb);

  // ciruclar references are possible with shared pointers.
  // this is a problem that will cause a memory leak because the resources cannot be deallocated
  mcp1->_member = mcp2;
  mcp2->_member = mcp1;

  return 0;
}
