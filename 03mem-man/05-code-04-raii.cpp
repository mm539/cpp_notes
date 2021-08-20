#include <iostream>
using namespace std;

class MyInt{
    int *p_; // pointer to heap data
  public:
    MyInt(int*p = nullptr) { p_ = p; }
    ~MyInt(){
      cout << "resource " << *p_ << " deallocated" << endl;
      delete p_;
    }
    int& operator*(){ return *p_; } 
};

/*
  The bottom line:
    i. This type of construct spares us from having to call delete.

    ii. By creating the MyInt object on the stack, we ensure that the deallocation occurs as soon as the object goes out of scope. (when a variable on the stack goes out of scope the destructor is called)

    iii. this is essentially how smart pointers work

  Things to notice:
    
    i. The part new int(i) creates a new block of memory on the heap and initializes it with the value of i. The returned result is the address of the block of memory.
    ii. The part MyInt en(…)calls the constructor of class MyInt, passing the address of a valid memory block as a parameter.
    iii. overloaded dereference operator



*/

int main(){
  double den[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  for(size_t i = 0; i < 5; i++){
    MyInt en(new int(i));
    cout << *en << "/" << den[i] << " = " << *en / den[i] << endl;
  }

  return 0;
}

/*
  QUIZ : What would be the major difference of the following program compared to the last example?


int main()
{
    double den[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    for (size_t I = 0; I < 5; ++i)
    {
        // allocate the resource on the heap
        MyInt *en = new MyInt(new int(i));

        // use the resource
        std::cout << **en << "/" << den[i] << " = " << **en / den[i] << std::endl;

    return 0;
}

ANSWER: The destructor of MyInt would never be called, hence causing a memory leak with each loop iteration.

*/