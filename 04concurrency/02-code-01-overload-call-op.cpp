#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <cstdio>
using namespace std;

/*
  There are 2 things to be aware of in this example:
    1. how to pass data to a thread with a class that has an overloaded function call operator
    2. "the most vexing parse"

  But what is the purpose of function call operator overloading?
    1. if a class doesn't have an overloaded function call operator, it is not a callable object and CANNOT be passed to a thread
        i. note: if an object with an overloaded function call operator is instantiated prior to the creation of a thread, it can still be passed to the thread, however, the overloaded behavior won't occur.
        ii. I don't see any purpose for point i, but it's interesting
    2. will the function call operator be called even if an object is not created within a thread? -> No.
    3. also, see 02-notes-01-callable-objects.cpp
*/

class Vehicle{
  private:
    int _id = 0;
  public:
    Vehicle(){ cout << "default constructor called\n";}
    Vehicle(int id): _id(id){ cout << "single param constructor called\n";}
    void operator()() //<---- this class has an overloaded function call() operator
    {
      cout << "function call operator called\n";
    }
};

int main()
{
  // 1. passing data
  thread t0 = thread( Vehicle(1)) ;
  t0.join();


  /* 
  2. C++ MOST VEXING PARSE

  std::thread t0(Vehicle());

  compiler interprets this as:
    a function declaration for a funcion t0 that returns an object of type std::thread and has a single UNNAMED parameter that is a pointer to a function returning an object of type Vehicle. 

  HOWEVER, we want to be interpreted as a variable definition for variable t of class std::thread, that is initialized with an anonymous instance of class Vehicle

  - why would Vehicle() be a function pointer?!?!
  - I didn't know variables could be initialized with parentheses!
  MyClass class(); ... int a(5);

  there are 3 ways to force the compiler to do our bidding:
  */

  std::thread t1( (Vehicle()) ); // add an extra parenthesis
  std::thread t2 = std::thread( Vehicle() ); // use copy initialization
  std::thread t3{ Vehicle() }; // use uniform initialization with braces


  t1.join();
  t2.join();
  t3.join();

  std::cout << "Finished work in main\n";
  return 0;
}