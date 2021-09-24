#include <iostream>
using namespace std;

/*
  source:
    https://eli.thegreenplace.net/2011/04/22/c-template-syntax-patterns
*/

// EXAMPLE 1: Class template that has an array
template <typename T>
class MyPair{
    T values_ [2]; // private member
  public:
    MyPair (T first, T second){
      values_[0] = first;
      values_[1] = second;
    }
    T getmax();
};

// method definition
template <typename T>
T MyPair<T>::getmax(){
  return ( values_[0] > values_[1] ? values_[0] : values_[1] );
}

int main ()
{
  MyPair<int> myints (22, 34);
  MyPair<double> mydoubles (3.5, 52.5);
  
  std::cout << myints.getmax() << std::endl;
}