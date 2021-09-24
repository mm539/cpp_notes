#include <iostream>
#include <cstdarg> // provides macros for accessing individual arguments
using namespace std;


// EXAMPLE 1
void PrintNums(int count, ...){
  va_list args;
  va_start(args, count);

  for (int i = 0; i < count; i++){
    cout << va_arg(args, int);
  }
  cout << endl;
  va_end(args);
}

// EXAMPLE 2
double findAverage(int count, ...){
  double sum{0};
  va_list list; // access the ellipsis
  va_start(list, count);

  for(int i{0}; i < count; i++){
    // We use va_arg to get parameters out of our ellipsis
    // The first parameter is the va_list we're using
    // The second parameter is the type of the parameter
    sum += va_arg(list, int);
  }
  va_end(list);
  return sum / count;
}

// EXAMPLE 3
void PrintChars(const char* fmt...){ // C-style "const char* fmt,..." is also valid
  va_list args;
  va_start(args, fmt);

  while (*fmt != '\0'){
    if (*fmt == 'd'){
      int i = va_arg(args, int);
      cout << i << endl;
    } else if (*fmt == 'c'){
      int c = va_arg(args, int); // automatic conversion to integral type
      cout << static_cast<char>(c) << endl;
    } else if (*fmt == 'f'){
      double d = va_arg(args, double);
      cout << d << endl;
    }
    ++fmt;
  }

  va_end(args);
}


int main(){
  PrintNums(5, 1, 2, 3, 4, 5);
  PrintChars("dfccc", 3, 3.2, 'a', 'b', 'c');

  return 0;
}
