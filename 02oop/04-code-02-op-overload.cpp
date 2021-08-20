#include <iostream>
#include <vector>


/* 
EXAMPLE #1
plus (+) operator overload

    i. default arguments
    ii. const
      - not required, but good/safe programming practice
    iii. reference (Point&)
      - good for memory management

*/ 

class Point
{
public:
  Point(int x = 0, int y = 0): x_(x), y_(y){}
  Point operator+(const Point& addend);
  void Print() { std::cout << "(" << x_ << "," << y_ << ")" << std::endl;}
  int x_, y_;
};

Point Point::operator+(const Point& addend)
{
  Point sum;
  sum.x_ = x_ + addend.x_;
  sum.y_ = y_ + addend.y_;
  return sum;
}

/* EXAMPLE #2 */
class Matrix
{
 public:
  Matrix( int rows, int cols ) : _rows( rows ), _cols( cols ), _values( rows * cols ) {};

  void printValues()
  {
    for( int i = 0; i < _cols * _rows; i++ )
    {
      std::cout << _values[i] << ", ";
    }
    std::cout << std::endl;
  }

  std::vector<int> getValues() const { return _values; }
  void setValues( std::vector<int> values)
  {
    _values = values;
  }

  // overloaded operator that returns the location
  // setter
  int& operator()( int row, int col )
  {
    return _values[ row * _cols + col ];
  }

  // overloaded operator that returns the value
  // getter
  int operator()( int row, int col ) const // <--- this const is very important. without it, the compiler doesn't know if this function is a setter or getter (and we get an error msg)
  {
    return _values[ row * _cols + col ];
  }

  // Matrix Addition!
  Matrix operator+( Matrix m )
  {
    Matrix newMatrix( _rows, _cols );
    std::vector<int> newValues( _rows * _cols );
    std::vector<int> mValues = m.getValues();

    for( int i = 0; i < _values.size(); i++ )
    {
      newValues[i] = _values[i] + mValues[i];
    }

    newMatrix.setValues( newValues );

    return newMatrix;
  }

 private:
  int _rows;
  int _cols;
  std::vector<int> _values;
};


/* 
EXAMPLE #3 
insertion (<<) operator overload
*/

class Complex
{
public:
  Complex(float x = 0, float y = 0): r(x), i(y){}
  Complex operator+(Complex addend);

  /* RE the code below:
    There are two different ways to overload the << operator.
      i. overload it within the Complex class AND declare it a friend
  
      ii. overload it outside of the Complex class
  */
  friend std::ostream& operator<<(std::ostream& os, Complex& c)
  {
    os << c.r << '+' << c.i << 'i';
    return os;
  }

  float r, i;
};

Complex Complex::operator+(Complex addend)
{
  Complex sum;
  sum.r = r + addend.r;
  sum.i = i + addend.i;
  return sum;
}

int main()
{
  Point p1(5, 10);
  Point p2(22, 22);
  Point p3 = p1 + p2;
  p3.Print();

  Complex c1(5, 2);
  Complex c2(1, 4);
  Complex c3 = c1 + c2;
  std::cout << c3 << std::endl;
}
