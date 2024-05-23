#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main() {
    system("cls");
    vector <int> v1{5,2};
    vector <int> v2(5,2);	
    vector <int> v(5);
    int n_v1 = v1.size();
    int n_v2 = v2.size();
    cout << "Vector v: " << v.size() << endl;
    cout << "Vector v1: " << n_v1 << endl;
    cout << "Vector v2: " << n_v2 << endl;
    // check element in v1
    cout << "Check element in v1: " << endl;
    for (int i = 0; i < n_v1; i++) {
        cout << v1[i] << " ";
    }
    cout << endl;
    // check element in v2
    cout << "Check element in v2: " << endl;
    for (int i = 0; i < n_v2; i++) {
        cout << v2[i] << " ";
        }
    return 0;
}