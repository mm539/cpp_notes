#include <iostream>
#include <thread>
#include <string>

/*
  This document DOES NOT cover variadic templates. Rather, it shows how variadic templates are used in thread creation.

  To see an explanation of variadic templates, go to:
    ../00-misc/03-variadics-02-templates.cpp
    ../00-misc/03-variadics-03-templates.cpp

  Things to keep in mind:
    1. thread constructors use variadic templates
    2. when passing a function to a thread, function parameters that take references REQUIRE that arguments be wrapped by std::ref when passed to the thread constructor

*/

void printName(std::string name, int waitTime)
{
  name += "!";
  std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
  std::cout << "Name (from Thread) = " << name << std::endl;
}

void printName2(std::string &name, int waitTime)
{
  name += "!";
  std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
  std::cout << "Name (from Thread) = " << name << std::endl;
}

int main(){
  
  std::string name1 = "MyThread1";
  std::string name2 = "MyThread2";
  std::string name3 = "MyThread3";

  std::thread t1(printName, name1, 100);
  std::thread t2(printName, std::move(name2), 300);
  std::thread t3(printName, std::ref(name3), 500);

  t1.join();
  t2.join();
  t3.join();

  std::cout << "Name (from Main) = " << name1 << std::endl;
  std::cout << "Name (from Main) = " << name2 << std::endl;
  std::cout << "Name (from Main) = " << name3 << std::endl;

  std::cout << "\nTo instatiate a thread using a pointer-to-a-function and references, you must:\n\t1. in the function signature, mark the parameters as references\n\t2. in the instatiation, wrap the variables with std::ref\n";
  std::thread t4(printName2, std::ref(name3), 50);
  t4.join();
  std::cout << "Name (from Main) = " << name3 << std::endl;

  return 0;
}