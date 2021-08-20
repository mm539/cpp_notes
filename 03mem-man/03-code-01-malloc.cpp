#include <stdio.h>
#include <stdlib.h>

struct MyStruct {int i; double d; char a[5];};

int main(){

  // PART 1: CASTING

  // error!
  //void *i = malloc(sizeof(int));
  //printf("address=%p, value=%d\n", i, *i);

  int *p = (int*)malloc(sizeof(int));
  printf("address=%p, value=%d\n", p, *p);
  // what will the value of p be? you should not rely on pre-initialization as this depends on the data type as well as on the compiler you are using. 

  // PART 2: MEMORY FOR ARRAYS
  int *parr = (int*)malloc(3*sizeof(int));
  printf("address=%p, value=%d\n", parr, *parr);
  parr[0] = 1; p[1] = 2; p[2] = 3;

  // PART 3: MEMORY FOR AN ARRAY OF STRUCTS
  MyStruct *ms = (MyStruct*) calloc(4, sizeof(MyStruct));

  // PART 4: FREEING UP MEMORY
  int *k = (int*)malloc(sizeof(int));
  free(k);

  return 0;
}