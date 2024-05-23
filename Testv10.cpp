#include <iostream>
#include <string>

using namespace std;

class infomRUPP {
  private:
    int numFaculty;
    string facultyNames[3];
    string feDeptName;

  public:
      infomRUPP() {
      numFaculty = 150;
      facultyNames[0] = "Sok Chan"; 
      facultyNames[1] = "Vathana Khun";
      facultyNames[2] = "Sopheaktra Poan";
      feDeptName = "Faculty of Engineering";
    }

    void printInfo() {
      cout << "Number of Faculty: " << numFaculty << endl;
      cout << "Faculty Names: ";
      for (string name : facultyNames) {
        cout << name << ", ";
      }
      cout << endl;
      cout << "FE Department Name: " << feDeptName << endl;
    }
};

int main() {
  infomRUPP rupp;
  rupp.printInfo();

  return 0;
}
