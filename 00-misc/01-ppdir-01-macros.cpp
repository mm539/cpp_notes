#include <iostream>
using namespace std;

/*
  1. PART 1 : basic macro definitions
    macro definitions return the text exactly as it is
*/
#define sweet "baby"
#define money 100000
#define honey 'h'

// PART 2: function macros
#define add(a, b) a + b
#define myprint(word) cout<<word<<endl;
int x = add(2,3); // the preprocessor replaces add with the text of the function definition


// PART 3 : function macros with # and ##
// the preprocessor will find&replace any definitions in the code according to which operator is used:
// # - replacement with string literal
// ## - replacement with code-text and concatenation
#define hi(x) #x
#define hello(x,y) #x #y

#define glue(a,b) a ## b
#define reverse_glue(a,b) b ## a

int main(){
  // PART 1
  cout << sweet << endl;
  cout << money * 5 << endl;
  #undef money
  // cout << money << endl; // this line will cause an error

  // PART 2
  cout << x << endl;
  myprint("hello");

  // PART 3 
  cout << hi(testing); // hi(...) will be replaced by "testing"
  cout << hello( dang,it); // <- observe the space
  cout << endl;

  glue(c,out) << "yeeehaw\n";

  string birds = "birds";
  cout << glue(b,irds) << endl;
  cout << reverse_glue(irds,b) << endl;

  return 0;
}
