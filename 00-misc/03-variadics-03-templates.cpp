#include <iostream>
#include <vector>
#include <cstdarg>
using namespace std;

/*
I want this section to cover variadic template CLASSES


  Here are some more examples:
    1. variadic class template

    2. makeVector functions?

*/

// 1. variadic class template
template<typename... Args>
class VTClass{
    int size = sizeof...(Args); // note: the "sizeof..." operator is different than the "sizeof" operator
  public:
    VTClass(){}
    void PrintSize(){ cout << size << endl; }
};

// method definition
// template<typename T>


int main(){

  return 0;
}
