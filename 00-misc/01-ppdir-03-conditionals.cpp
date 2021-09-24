#include <iostream>
using namespace std;

#define sweet "baby"
#define money 100000
#define honey 'h'

/*
  PART 1 : conditionals
    #ifdef, #ifndef, #if, #endif, #else and #elif
*/
#ifdef derp
int i = 5;
#elif money == 5 // note: cannot do variable-length string comparisons
int i = 10;
#elif honey == 'h'
int i = 15;
#endif



int main(){

  cout << i << endl;

  return 0;
}
