#include <iostream>

using namespace std;

class MyClass{
  private:
    int *number_;
  public:
    MyClass(){
      cout << "Constructor is called\n";
      cout << "Allocate memory for member number_\n";
      number_ = (int*)malloc(sizeof(int));
    }
    ~MyClass(){
      cout << "Destructor is called\n";
      cout << "Delete memory for member number_\n";
      free(number_);
    }
    void setNumber(int number){
      *number_ = number;
      cout << "Number: " << *number_ << "\n";
    }
    /* commented out because it breaks point#3
    // 4. OVERLOAD
    void *operator new(size_t size){
      cout << "new: Allocating " << size << " bytes of memory" << endl;
      void *p = malloc(size);

      return p;
    }

    // overloaded delete
    void operator delete(void *p){
      cout << "delete: memory is freed again\n";
      free(p);
    }
    //*/
    // 5. arrayS
    void* operator new[](size_t size){
      cout << "new: Allocating " << size << " bytes of memory" << std::endl;
      void *p = malloc(size);
    }
    void operator delete[](void* p){
      cout << "delete: Memory is freed again " << std::endl;
      free(p);
    }
};

int main(){
  // 1. allocate memory using malloc
  MyClass *myclass = (MyClass*)malloc(sizeof(MyClass));
  myclass->setNumber(43);
  free(myclass);

  /*
  UDACITY NOTES - With malloc, the program crashes on calling the method setNumber, as no memory has been allocated for _number - because the constructor has not been called. Hence, an EXC_BAD_ACCESS error occurs, when trying to access the memory location to which _number is pointing. 
  HOWEVER

  Although it's true that the constructor and destructor weren't called, my program didn't crash.

  */

  // 2. allocate memory using new
  MyClass *myclass2 = new MyClass();
  myclass2->setNumber(43);
  delete myclass2;

  // 3. placement new
  void *memory = malloc(sizeof(MyClass)); // mem allocation

  MyClass *object = new(memory) MyClass;
  object->~MyClass();

  MyClass *object = new(memory) MyClass;
  object->~MyClass();

  free(memory); // mem deallocation

  // 4. operator () overload
  // see method definitions in class
  // i really have no idea why you'd want to do this.
  MyClass *p = new MyClass(); // observe: we are not passing the argument to the parameter size to this function; the system deduces it 
  delete p;

  // 5. arrays
  MyClass *p = new MyClass[3]();
  delete[] p;
  /*
  In main, we are now creating an array of three objects of MyClass. Also, the overloaded new and delete operators have been changed to accept arrays. Let us take a look at the console output:

new: Allocating 20 bytes of memory
Constructor is called
Constructor is called
Constructor is called
Destructor is called
Destructor is called
Destructor is called
delete: Memory is freed again 

Interestingly, the memory requirement is larger than expected: With new, the block size was 4 bytes, which is exactly the space required for a single integer. Thus, with three integers, it should now be 12 bytes instead of 20 bytes. The reason for this is the memory allocation overhead that the compiler needs to keep track of the allocated blocks of memory - which in itself consumes memory. If we change the above call to e.g. new MyClass[100](), we will see that the overhead of 8 bytes does not change:

new: Allocating 408 bytes of memory
Constructor is called
…
Destructor is called
delete: Memory is freed again 

  */

  return 0;
}