#include <iostream>
#include <cstdlib> // for srand() and rand()
#include <ctime> // for time()
using namespace std;

int main()
{
    // initialize random number generator with current time as seed
    srand(time(NULL));

    // generate and print 10 random numbers between 0 and 99
    for (int i = 0; i < 10; i++)
    {
        int num = rand() % 100; // get a random number from 0 to 99
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
