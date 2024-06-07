#include <iostream>
using namespace std;

void func(int x ) {
    if (x > 0 ) {
        func(x-1);
        cout << x << " ";
    }
}
 int main() {
    system("cls");
    func(5);
    return 0;
 }