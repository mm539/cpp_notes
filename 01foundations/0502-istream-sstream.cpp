// STRING STREAMING
#include <iostream>
#include <sstream>
#include <string>
using std::string;
using std::cout;
using std::istringstream;

/*

In c++, strings can be streamed into temporary variables (similarly to how files can be streamed into strings). Streaming a string allows us to work with each character individually.

One way to stream a string is to use an input string stream object, istringstream from the <sstream> header.

Once an istringstream object has been created, parts of the string can be streamed and stored using the "extraction operator" >> .

The extraction operator is read until:
  i. whitespace is reached
  OR
  ii. until the stream fails.


*/

int main(){
  // PART 1
  string a("1 2 34");
  istringstream my_stream(a);
  int n;

  while(my_stream) {
      my_stream >> n;
      if (my_stream){
          cout << "success!\n" << n << "\n";
      }
      else{
          cout << "unsuccesful shoveling.\n";
          // this gets executed because my_stream("") evaluates to true
          // but after the >>, the stream is destroyed?
      }
  }

  cout << std::endl;

  // PART 2
  string b("1 2 3");
  istringstream my_second_stream(b);
  char c;
  int g;

    while (my_second_stream >> g >> c){
        cout << "that stream was successful: " << g << c << "\n";
    }
    cout << "that stream has failed" << "\n";

  cout << std::endl;
  // PART 3
  string x(" 11 2 3");
  istringstream StreamX(x);
  char c2;
  StreamX >> c2;
  cout << c2 << std::endl;

  cout << std::endl;
  // PART 4
  string y(" 11 2 3");
  istringstream StreamY(y);
  int i2;
  StreamY >> i2;
  cout << i2 << std::endl;

  cout << std::endl;
  // PART 5
  string z(" 11 2 3");
  istringstream StreamZ(z);
  string s2;
  StreamZ >> s2;
  cout << s2 << std::endl;
}

/*
The extraction operator >> writes the stream to the variable on the right of
the operator and returns the istringstream object, so the entire expression
my_stream >> n is an istringstream object and can be used as a boolean!
Because of this, a common way to use istringstream is to use the entire
extraction expression in a while loop.
*/