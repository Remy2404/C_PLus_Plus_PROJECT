#include <iostream>
#include <string>

class University
{
public:
  University(std::string name, std::string location, int year_founded)
  {
    this->name = name;
    this->location = location;
    this->year_founded = year_founded;
  }

  std::string get_name() { return name; }

  std::string get_location() { return location; }

  int get_year_founded() { return year_founded; }

private:
  std::string name;
  std::string location;
  int year_founded;
};

class Dog
{
public:
  Dog(std::string name, std::string breed, int age)
  {
    this->name = name;
    this->breed = breed;
    this->age = age;
  }

  std::string get_name() { return name; }

  std::string get_breed() { return breed; }

  int get_age() { return age; }

private:
  std::string name;
  std::string breed;
  int age;
};
