// enums
// enum is a type that lets you restrict the possible values of the variables

#include <iostream>
using std::cout;

int main(){
  enum class Color {white, black, blue, red};
  // what are the types of these "things" in the {}

  Color my_color = Color::blue;

  if (my_color == Color::red){
    cout << "the color of my car is red" << "\n";
  } else {
    cout << "the color of my car is not red" << "\n";
  }

  // enum + switch
  enum class Direction {kUp, kDown, kLeft, kRight};
  Direction dir = Direction::kUp;

  switch (dir) {
    case Direction::kUp : cout << "Going up" << "\n";
      break;
    case Direction::kDown : cout << "going down" << "\n";
      break;
    case Direction::kLeft : cout << "going left" << "\n";
      break;
    case Direction::kRight : cout << "going right" << "\n";
      break;
  }
}
