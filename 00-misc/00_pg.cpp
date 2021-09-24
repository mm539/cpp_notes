#include <iostream>
#include <cstdarg>
using namespace std;


// variadic template class
template<typename... Args>
class VariadicTemplate {
    int size = sizeof...(Args);
  public:
    void PrintSize() { cout << size << endl; }
};

// variadic template function
template<typename ... Args>
void VFunction(Args... Pargs){
  auto expanded = (Pargs == ...);
}


int main(){
  cout << "executing\n";
  //VariadicTemplate<int, int, int, string> bob;
  //bob.PrintSize();

  return 0;
}
