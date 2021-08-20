#include <iostream>
#include <memory>
using namespace std;

int main(){
  unique_ptr<int> uniquePtr(new int);
  *uniquePtr = 5;

  shared_ptr<int> sharedPtr1 = move(uniquePtr); // 1 : convert to shared from unique

  weak_ptr<int> weakPtr(sharedPtr1);
  shared_ptr<int> sharedPtr2 = weakPtr.lock(); // 2 : convert to shared from weak

  int *rawPtr = sharedPtr2.get(); // 3 : extract raw pointer from shared
  cout << rawPtr << " " << *rawPtr <<endl;
  cout << sharedPtr2 << " " << *sharedPtr2 << endl;
  delete rawPtr;// according to udacity, this line should generate an error. it doesn't.
  /*
    In (3), a raw pointer is extracted from a shared pointer. 
    
    However, this operation does not decrease the reference count within sharedPtr2. This means that calling delete on rawPtr in the last line before main returns will generate a runtime error as a resource is trying to be deleted which is managed by sharedPtr2 and has already been removed. 
    
    The output of the program when compiled with g++ thus is: 
      malloc: *** error for object 0x1003001f0: pointer being freed was not allocated

  */
  

  return 0;
}