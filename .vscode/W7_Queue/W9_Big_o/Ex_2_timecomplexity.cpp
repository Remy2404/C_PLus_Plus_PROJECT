#include <iostream>
using namespace std;
/*
You are given an integer n
count the total 1+2+....+ n
Now try to write the fuction in C++ with could meet 2-time complexity
a) Slow solution time complexity O(n^2)
b) faat solution time complexity O(n)
*/
int main(){
    system("cls");
// a ) slow solution time complexity O(n^2)
/*
int n;
for (int i = 1; i <= n; i++)
{
    int sum = 0;
    for (int j = 1; j <= i; j++)
    {
        sum += j;
    }
    cout << sum << endl;
}

*/

// b ) faat solution time complexity O(n)

int sum = 0;
int n;
for (int i = 1; i <= n; i++)
{
    sum+=1;
}
cout << sum << endl;


    system("pause>0");
}