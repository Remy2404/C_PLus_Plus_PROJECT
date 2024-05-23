#include <iostream>
#include <string>

class University {
public:
  University(std::string name, std::string location, int year_founded) {
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

class Dog {
public:
  Dog(std::string name, std::string breed, int age) {
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

class Cup {
public:
  Cup(std::string material, std::string color, int capacity) {
    this->material = material;
    this->color = color;
    this->capacity = capacity;
  }

  std::string get_material() { return material; }
  std::string get_color() { return color; }
  int get_capacity() const { return capacity; }

private:
  std::string material;
  std::string color;
  int capacity;
};

int main() {
  // Create an array of 5 University objects with specific arguments
  University universities[5] = {
    {"University 1", "Location 1", 1800},
    {"University 2", "Location 2", 1801},
    {"University 3", "Location 3", 1802},
    {"University 4", "Location 4", 1803},
    {"University 5", "Location 5", 1804}
  };

  // Print the name of each university
  for (int i = 0; i < 5; i++) {
    std::cout << universities[i].get_name() << std::endl;
  }

  // Create an array of 5 Dog objects with specific arguments
  Dog dogs[5] = {
    {"Dog 1", "Breed 1", 1},
    {"Dog 2", "Breed 2", 2},
    {"Dog 3", "Breed 3", 3},
    {"Dog 4", "Breed 4", 4},
    {"Dog 5", "Breed 5", 5}
  };

  // Print the name and breed of each dog
  for (int i = 0; i < 5; i++) {
    std::cout << dogs[i].get_name() << ": " << dogs[i].get_breed() << std::endl;
  }

  // Create an array of 5 Cup objects with specific arguments
  Cup cups[5] = {
    {"Material 1", "Color 1", 10},
    {"Material 2", "Color 2", 12},
    {"Material 3", "Color 3", 14},
    {"Material 4", "Color 4", 16},
    {"Material 5", "Color 5", 18}
  };

  // Print the material and color of each cup
  for (int i = 0; i < 5; i++) {
    std::cout << cups[i].get_material() << ": " << cups[i].get_color() << std::endl;
  }

  return 0;
}
