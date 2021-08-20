#include <iostream>
#include <thread>
using namespace std;

/*
  1. Passing a member function to a thread - basic format:
    thread t(&class::memberFn, obj, memberFnArgs...)

  2.Observe:
    For pointers-to-fns pass-by-ref, std::ref(varName) is required.
    For member functions pass-by-ref, &obj works fine (as does std::ref).

  3. How can we ensure that the objects v1,v2 will exist throughout the lifetime of the threads?

    see 02-code-04-memb-fn-shared-ptr.cpp

*/

class Vehicle{
  private:
    size_t _id;
  public:
    Vehicle(): _id(0) {}
    void setID(size_t id) { _id = id;}
    void printID(){ cout << "id: " << _id << endl; }
    void test(int &x){ x+= 25; }
};

int main(){
  Vehicle v1, v2;
  thread t1(&Vehicle::setID, v1, 50);
  thread t2(&Vehicle::setID, &v2, 100);

  t1.join();
  t2.join();

  v1.printID();
  v2.printID();

  int x = 25;
  thread t3(&Vehicle::test, &v2, std::ref(x));
  t3.join();
  cout << "x: " << x << endl;

  return 0;
}