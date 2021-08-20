#include <iostream>

void AddTwo(int val){ val += 2;}
void AddFour(int &val){ val += 4;}
void AddSix(int *val){*val += 6;}

void CallByValue(int i){
    int j = 1; 
    printf ("call-by-value: %p\n",&j);
}

void CallByPointer(int *i){
    int j = 1; 
    printf ("call-by-pointer: %p\n",&j);
}

void CallByReference(int &i){
    int j = 1; 
    printf ("call-by-reference: %p\n",&j);
}

int main()
{
  // PART 1: DIFFERENT CALLING METHODS
    int val = 0;
    AddTwo(val);
    AddFour(val);
    AddSix(&val);

    std::cout << "val = " << val << std::endl;

  // PART 2: MEMORY ANALYSIS
  // recall: upon function termination, memory is deallocated
  // the location of the local variable j can tell us how much memory is being addressed by the different calling methods.

    int i = 0;
    printf ("stack bottom: %p\n",&i);
    
    CallByValue(i);
    CallByPointer(&i);
    CallByReference(i);
    /*
      stack bottom: 0061FF08
      call-by-value: 0061FEDC
      call-by-pointer: 0061FEDC
      call-by-reference: 0061FEDC

      Depending on your system, the compiler you use and the compiler optimization techniques, you man not always see this result
    */
 
    return 0;
}
