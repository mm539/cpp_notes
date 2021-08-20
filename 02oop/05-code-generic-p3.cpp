
#include <cstdio>
#include <iostream>
#include <sstream>

using namespace std;

// here is a class template
template<typename T>
class AddElements{};

// TEMPLATE SPECIALIZATION
// int, double, float
template <>
class AddElements<int>{
    public:
        AddElements(int arg1){ elem1= arg1;}
        int elem1;

        int add(int elem2){ return (elem1 + elem2); }
};

template <>
class AddElements<double>{
    public:
        AddElements(double arg1){ elem1= arg1;}
        double elem1;
        double add(double elem2){ return (elem1 + elem2); }
};

template <>
class AddElements<string>{
    public:
        AddElements(string arg1){ elem1= arg1;}
        string elem1;
        string concatenate(string elem2){ return (elem1 + elem2); }
};

int main () {
  int n,i;
  string lines;
  lines += "3 ";
  lines += "string John Doe ";
  lines += "int 1 2 ";
  lines += "float 4.0 1.5 ";
  istringstream ss(lines);

  ss >> n;
  for(i=0;i<n;i++) {
    string type;
    ss >> type;
    if(type=="float") {
        double element1,element2;
        ss >> element1 >> element2;
        AddElements<double> myfloat (element1);
        cout << myfloat.add(element2) << endl;
    }
    else if(type == "int") {
        int element1, element2;
        ss >> element1 >> element2;
        AddElements<int> myint (element1);
        cout << myint.add(element2) << endl;
    }
    else if(type == "string") {
        string element1, element2;
        ss >> element1 >> element2;
        AddElements<string> mystring (element1);
        cout << mystring.concatenate(element2) << endl;
    }
  }
  return 0;
}