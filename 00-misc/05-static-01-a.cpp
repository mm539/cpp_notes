#include <iostream>
#include "05-static-01-b.cpp"
using namespace std;

/*
  This file is meant to be compiled with one other file:
    05-static-01-b.cpp

  observations:
    i. global vars from other files must use the static specifier (otherwise there will be a compilation error)
    ii. zero initialization for un-initialized vars

*/
int x;
static int z;

int main(){
  cout << "from file a, x: " << x << endl;
  cout << "from file a, z: " << z << endl;
  cout << "from file b, static y: " << y << endl;
  cout << "from file b, static yy: " << yy << endl;
  return 0;
}