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

*/

class Vehicle{
  private:
    int _id = 0;
  public:
    Vehicle(){}
    Vehicle(int id): _id(id){}
    void operator()() //<---- this class has an overloaded function call() operator
    {
      if (_id != 0){
        printf("Vehicle object with id %i created!\n", _id);
        return; 
      }
      std::cout << "Vehicle object has been created\n";
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
  
  a function declaration for a funcion t0 that returns an object of type std::thread and has a single unnamed parameter that is a pointer to a function returning an object of type Vehicle. 

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