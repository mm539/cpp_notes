#include <iostream>

/* EXAMPLE #1 - MULTIPLE INHERITANCE */
class Car
{
 public:
  void drive()
  {
    std::cout << "I am driving\n";
  }
};

class Boat
{
 public:
  void cruise()
  {
    std::cout << "I am crusing\n";
  }
};

class BoatCar: public Car, public Boat {};

/* EXAMPLE #2 DIAMOND PROBLEM */

class Vehicle
{
  public:
    virtual void Move() = 0;
};

class Tank: Vehicle
{
  public:
    void Move() { std::cout << "vrroom" << std::endl; }
};

class Tricycle: Vehicle
{
  public:
    void Move() { std::cout << "squeeak squeak" << std::endl; }
};

class TricycleTank: Tank, Tricycle
{
  // what will Move() do?
};

int main()
{
  BoatCar boatcar;
  boatcar.cruise();
  boatcar.drive();
  TricycleTank tritank;
  // tritank.Move(); // compiler error! diamond problem
}