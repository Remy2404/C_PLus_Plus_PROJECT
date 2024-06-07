#include <iostream>
using namespace std;
// Recursive function to calculate factorial
int powerIter(int a , int n ) {
    // Base case: powerIter of 0 or 1 is 1
    int res =1;
    for (int i =0 ; i < n ; i++) {
        res = res * a ;
    }
    return res;
}

int main() {
    int a = 4 , n =2 ;
    cout << " power " << a << "," << n << " Without recursion is " << powerIter(a , n) << endl;
    return 0;
}
