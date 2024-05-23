#include <iostream>
using namespace std;
class Circle {
public:
    double radius;
    Circle(double r){
        this->radius = r;
    }
    double calculateArea() {
        return 3.14 * radius * radius;
    }
    double calculateCircumference() {
        return 2 * 3.14 * radius;
    }
};

int main() {
    double radius;
    cout << "Enter the radius of the circle: ";
    cin >> radius;
    Circle myCircle(radius);
    cout << "Area of the circle: " << myCircle.calculateArea() <<endl;
    cout << "Circumference of the circle: " << myCircle.calculateCircumference() <<endl;
    return 0;
}