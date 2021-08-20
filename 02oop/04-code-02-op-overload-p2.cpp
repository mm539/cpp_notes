
#include<iostream>

using namespace std;

/* 
how does friendship fit into all of this?
if we had put:
    ostream& operator<<(ostream &os,Complex const &c)
within class Complex, then we would have had to have added the friend keyword to the beginning of the signature
*/
class Complex
{
public:
    int a,b;
    void input(string s)
    {
        int v1=0;
        int i=0;
        while(s[i]!='+')
        {
            v1=v1*10+s[i]-'0';
            i++;
        }
        while(s[i]==' ' || s[i]=='+'||s[i]=='i')
        {
            i++;
        }
        int v2=0;
        while(i<s.length())
        {
            v2=v2*10+s[i]-'0';
            i++;
        }
        a=v1;
        b=v2;
    }
};


Complex operator+(Complex const &c1, Complex const &c2){
  Complex sum;
  sum.a = c1.a + c2.a;
  sum.b = c1.b + c2.b;
  return sum;
}

ostream& operator<<(ostream &os,Complex const &c){
  os << c.a << "+i" << c.b;
  return os;
}

int main()
{
  Complex c1;
  c1.a = 5;
  c1.b = 25;
  cout << c1 << endl;
  return 0;
}