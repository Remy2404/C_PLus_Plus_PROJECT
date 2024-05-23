#include <iostream>
using namespace std;
/*
Draw diagram to point out the difference between reference
between Reference and Pointer with a brief explain and example.
*/
int main()
{
system("cls");
int value = 10; 
int &ref = value; // reference  
int *ptr = &value; // pointer of "value" holds the memory address 
int **dptr = &ptr; // pointer of "Pv" holds the memory address of "value"
int ***dptr2 = &dptr;
int ****dptr3 = &dptr2;
cout << "value = " << value << endl;
cout << "Reference : " << ref << endl;
cout << "Pointer : " << ptr << endl;
cout << "Double Pointer : " << dptr << endl;
cout << "Double Pointer2 : " << dptr2 << endl;
cout << "double Pointer 3 :" << dptr3 << endl;

return 0;
}

/*
Explain :
----------
- Reference : is a variable that holds the memory address of another variable.
- Pointer : is a variable that holds the memory address of another variable.
- Double Pointer : is a variable that holds the memory address of another variable.
----------
Draw diagram to point out the difference between reference
.........................
.........................
.........................
- Reference : is a variable*/