#include <iostream>
using namespace std;

/*
  This file is meant to be compiled with two other files:
    05-static-01-a.cpp

*/

// declaring a global var here without the static specifier led to a compilation error
// int y = 5;
static int y = 5;
static int yy;
