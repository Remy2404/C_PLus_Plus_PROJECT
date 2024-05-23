#include <iostream>
#include <iomanip> // Include header for setw manipulator

using namespace std;

class Employee {
private:
  string name;
  int yearOfJoining;
  string address;

public:
  Employee(string name, int yearOfJoining, string address) {
    this->name = name;
    this->yearOfJoining = yearOfJoining;
    this->address = address;
  }

  string getName() const {
    return name;
  }

  int getYearOfJoining() const {
    return yearOfJoining;
  }

  string getAddress() const {
    return address;
  }

  void printInfo() const {
    cout << setw(15) << name << "\t\t" << setw(15) << yearOfJoining << "\t\t\t" << address << endl;
  }
};

int main() {
  Employee emp1("Robert", 1994, "64C- WallsStreet");
  Employee emp2("Sam", 2000, "68D- WallsStreet");
  Employee emp3("John", 1999, "26B- WallsStreet");

  cout << setw(15) << "Name" << "\t\t" << setw(15) << "Year of joining" << "\t\t\t" << "Address" << endl;
  cout << "-------------------------------------------------------------------" << endl;

  emp1.printInfo();
  emp2.printInfo();
  emp3.printInfo();

  return 0;
}
