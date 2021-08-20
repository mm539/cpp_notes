#include <stdio.h> 
#include <stdlib.h> 

/*
QUESTION 1
Match the code snippets to the respective comments
  Comments:
    1. uses a dangling pointer -> a pointer that points to invalid data 
    2. uses an uninitialized pointer -> a pointer that ?
    3. generates a memory leak -> memory is not deallocated

QUESTION 2
Which of the functions below is likely to cause pointer-related problems?

*/


// QUESTION 2
int *f1(void){ int x = 10; return (&x); }
int *f2(void){ int *px; *px = 10; return px; }
int *f3(void){ int *px; px = (int *)malloc(sizeof(int)); *px = 10; return px; }


int main()
{
  // QUESTION 1
    // (X)
    int *m = (int*)malloc(sizeof(int)); 
    m = NULL; 

    // (Y)
    int *n = (int*)malloc(sizeof(int)); 
    free(n);
    *n = 23;

    // (Z)
    char *o;
    *o = 'a';

    return 0;
}




// answer 1: 3 - 2 - 1
// answer 2: f1 and f2
/*
In f1, the pointer variable x is a local variable to f1, and f1 returns the pointer to that variable. x can disappear after f1() is returned if x exists on the stack. So &x can become invalid.

In f2, the pointer variable px is assigned a value without allocating its space.

f3 works fine. Memory is allocated to the pointer variable px using malloc(). So, px exists on the heap, its existence will remain in memory even after the return of f3() as it is on the heap.

*/