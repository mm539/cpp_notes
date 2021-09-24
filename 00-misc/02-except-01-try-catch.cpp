#include <cassert>
#include <stdexcept>
#include <string>
#include <iostream>

// TODO: Define "Student" class
class Student {
 public:
  void Validate();
  // constructor
  Student(std::string name, int grade, float gpa);
  // accessors
  std::string Name() const { return name_; }
  int Grade() const { return grade_; }
  float GPA() const { return gpa_; }
  // mutators
  void Name(std::string name) { name_ = name; Validate(); }
  void Grade(int grade) { grade_ = grade; Validate(); }
  void GPA(float gpa) { gpa_ = gpa; Validate(); }

 private:
  std::string name_;
  int grade_;
  float gpa_;
};

Student::Student(std::string name, int grade, float gpa): name_(name), grade_(grade), gpa_(gpa) { Validate(); }

void Student::Validate()
{
  if (name_.length() == 0) throw std::invalid_argument("Name must be at least 1 character.");
  if (!((grade_ > 0) && (grade_ < 13))) throw std::invalid_argument("Grade must be 1-12. Grade is: " + std::to_string(grade_));
  if (!(gpa_ > 0 && gpa_ < 4.0 )) throw std::invalid_argument("GPA must be 0-4.0. GPA is: " + std::to_string(gpa_));
}

// TODO: Test
int main() {
  Student s1("bob", 2, 3.4);
  assert (s1.Name() == "bob");
  //try{ s1.Name("");}catch (std::invalid_argument& e){std::cout << "The error:\n" << e.what() << std::endl;}
  //try{ s1.GPA(5); } catch (std::invalid_argument& e) { std::cout << "The error:\n" << e.what() << std::endl; }
  //try{ s1.Grade(13); } catch (std::invalid_argument& e) { std::cout << "The error:\n" << e.what() << std::endl; }
}