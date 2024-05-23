#include <iostream>

using namespace std;

class Circle {
private:
  double radius;
  
public:
  Circle(double r) {
   radius = r;
  }

  double calculateArea() {
    return 3.14 * radius * radius;
  }

  double calculateCircumference() {
    return 2 * 3.14 * radius;
  }
};

int main() {
  double radius_main;
  
  cout << "Enter radius: ";
  cin >> radius_main;
  
  Circle c(radius_main);
  
  cout << "Area: " << c.calculateArea() << endl;
  cout << "Circumference: " << c.calculateCircumference() << endl;
  
  return 0;
}
