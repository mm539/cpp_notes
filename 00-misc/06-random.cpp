#include <iostream>
#include <time.h>

/*
  Key parts:
    i. srand
    ii. dividing by modulo <- determines the magnitude of the range

*/

int main()
{
  srand( time(NULL) ); // <-- make a new random seed, so that we get different numbers every time

  for (int i = 0; i < 10; i++)
  {
    int x = rand() % 100;
    std::cout << "x: " << x << std::endl;
  }

}