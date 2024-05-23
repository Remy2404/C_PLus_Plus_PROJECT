#include <iostream>
using namespace std;
int main() {
    int month;
    cout<<"Enter the month (1-12): ";	
    cin>>month;

 switch (month)
 {
 case 1: cout<<"it is january";
    break;
 case 2: cout<<"it is february";
 break;
 case 3: cout<<"it is march";
 break;
 case 4: cout<<"it is april";
 break;
 case 5: cout<<"it is may";
 break;
 case 6: cout<<"it is june";
 break;
 case 7: cout<<"it is july";
 break;
 case 8: cout<<"it is august";
 break;
 case 9: cout<<"it is september";
 break;
 case 10: cout<<"it is october";
 break;
 case 11: cout<<"it is november";
 break;
 case 12: cout<<"it is december";
 break;
 default: cout<<"it is an invalid month";
    break;
 }
  return 0;
}
