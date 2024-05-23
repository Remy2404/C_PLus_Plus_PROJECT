#include <iostream>
#include <iomanip>
using namespace std;
/*
Write a fuction code in C++ to implcement on time complexity
a) constand time n(1)
b) logarithmic time O(log n)
c) linear time O(n)
d) quadratic time O(n^2)
e ) linear time O(n+m)
*/

int main () {
    system("cls");
 // a constand time O(1)
 cout << setw(10) << "constand time O(1)" << endl;
 cout << "----------------------------------" << endl;

 // b logarithmic time O(log n)
 int n =0 , element=8 , d_value =4;
for (int i = 1; i <=element; i=i*2)
{
    cout  << setw(10) << "logaritthimc time O(log(n))" << endl;
}
cout << "----------------------------------" << endl;
// c linear time O(n)
for (int i = 0; i <= element; i++)
{
    cout  << setw(10) << "linear time O(n)" << endl;
}
// d quadratic time O(n^2)
for (int i = 0; i < d_value; i++)
{
    for (int j = 0; j < d_value; j++)
    {
        n+=1;
        cout << setw(10)  << "quadratic time n(n)" << n << endl;
    }
    cout << "----------------------------------" << endl;
}
// e Linear time n(n+m)
for (int i = 0; i < d_value; i++)
{
    for (int j = 0; j < element; j++)
    {
        n+=1;
        cout  << setw(10) << "linear time n(n+m)" << n << endl;
    }

}
system("pause>0");

}