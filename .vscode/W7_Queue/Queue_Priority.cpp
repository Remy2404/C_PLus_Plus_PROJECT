#include <iostream>
using namespace std;

int main() {
    int value = 10;
    int & ref = value;
    int *ptr1 = &value;
    int **ptr2 = &ptr1;
    // pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer to pointer 

    cout << "Value: " << value << endl;
    cout << "Reference: " << ref << endl;
    cout << "Value (through ptr1): " << *ptr1 << endl;
    cout << "Value (through ptr2): " << **ptr2 << endl; 
    cout << "Address of value: " << &value << endl;

    return 0;
}
