#include <iostream>
using namespace std;

int max_two(int num1, int num2) {
  if (num1 > num2) {
    return num1;
  } else {
    return num2;
  }
}

int main() {
int num1 , num2 ;
  cout << "Enter first number: ";
  cin >> num1;

  cout << "Enter second number: ";
  cin >> num2;

  int maximum = max_two(num1, num2);

  cout << "Maximum is: " << maximum << endl;

  return 0;
}
