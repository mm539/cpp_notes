#include <cassert>
#include <iostream>
#include <string>

class Date {
public:
  Date(){}
  Date(int day, int month, int year);
  int Day() const { return day_; } // note: accessors should be const
  void Day(int day); 
  int Month() const { return month_; }
  void Month(int month);
  int Year() const { return year_; }
  void Year(int year);
  int DaysInMonth(int month, int year) const;
  std::string GetDate();

private:
  
  int day_{1};
  int month_{1};
  int year_{0};
};

// 1. this function doesn't need access to the members of the Data class, so we leave it outside.
bool LeapYear(int year){
    if( (year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
      //std::cout << "leap year!" << "\n";
      return true;
    }
    //std::cout << "NOT a leap year" << "\n";
    return false;
}

// 2. we make DaysInMonth a member function
// it needs access to Date's member variables, and is related to Date's invariants
int Date::DaysInMonth(const int month, const int year) const{
    if(month == 2) return LeapYear(year) ? 29 : 28;
    else if(month == 4 || month == 6 || month == 9 || month == 11) return 30;
    else return 31;
}

// 3. the Tomorrow function is not vital to the Date class, so we put it outside.
Date Tomorrow(Date const & date)
{
  int maxDays, day, month, year;
  year = date.Year();
  month = date.Month();
  day = date.Day();
  // because date is const, it can only call const member functions
  maxDays = date.DaysInMonth(month, year);

  {
    if (day + 1 > maxDays)
    {
      day = 1;
      if (month + 1 > 12)
      {
        month = 1;
        year++;
      }
      else month++;
    }
    else
    {
      day++;
    }
  }

  Date tomorrow(day, month, year);
  return tomorrow;
}

Date::Date(int day, int month, int year) {
  Year(year);
  Month(month);
  Day(day);
}

void Date::Day(int day) {
  if (day >= 1 && day <= DaysInMonth(Month(), Year()))
    day_ = day;
}

void Date::Month(int month) {
  if (month >= 1 && month <= 12)
    month_ = month;
}

void Date::Year(int year) {
  // 4. here, we need an invariant that makes sures that the rest of the date is still valid if we switched from a leap year to a non-leap year or vice versa
  // invariant logic
  year_ = year; 
}

std::string Date::GetDate()
{
  return std::to_string(Year()) + "/" + std::to_string(Month()) + "/" + std::to_string(Day());
}

// Test
int main() {
  std::cout << "starting program: " << "\n";
  Date date(29, 2, 1982);
  Date date2(29, 2, 1980); // leap year
  assert(date2.Day() == 29);
  assert(date.Month() == 2);
  assert(date.Year() == 1982);

  Date tomorrow = Tomorrow(date2);
  std::cout << tomorrow.GetDate() << std::endl;

}