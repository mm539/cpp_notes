#include <iostream>
#include <string>
#include <vector>
#include "0403-h-header.h"
using std::vector;
using std::string;
using std::vector;

void Car::PrintCarData(){
  std::cout << "color: " << color << "\tnumber: " << number << "\n";
}

// interestingly, I didn't have to define IncrementDistance()

int main(){
  vector<Car*> car_vect; 
  Car* cp = nullptr; // null pointer to a car
  vector<string> colors {"red", "blue", "green"};

  for (int i = 0; i < 20; i++){
    cp = new Car(colors[i%3], i+1); 
    // 'new' allocates memory on the 'heap'
    // heap vs stack
    car_vect.push_back(cp);
  }

  for (Car* cp: car_vect){
    cp->PrintCarData();
  }

}
