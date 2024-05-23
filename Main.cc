#include <iostream>
#include <fstream>
using namespace std;

int main () {
  const int size = 8;
  double x[] = {1,2,3,4,5,6,7,8}; 

  ofstream myfile ("example.txt");
  if (myfile.is_open())
  {
    myfile << "This is a line.\n";
    myfile << "This is another line.\n";
    for(int count = 0; count < size; count ++){
        myfile << x[count] << " " ;
    }
    myfile.close();
  }
  else cout << "Unable to open file";
  return 0;
}