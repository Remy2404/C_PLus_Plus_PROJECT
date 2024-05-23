#include<iostream>
using namespace std;

class Phone{
  public:
    int code;
    int price;
    
    //----------Default Constructors-------
    
    Phone(){
      code=1001;
      price=1000;
    }
    
    //---------Parameterize Constructors--------
    
    Phone(int code,int price){
      this->code = code;
      this->price = price;
    }
    
    //-------------Copy constructor-----------
    Phone(Phone &ph){
      code = ph.code;
      price = ph.price;
    }
    
    void Output(){
      cout<<"\n\t Code is   : "<<code;
      cout<<"\n\t Price is  : "<<price;
    }
    
};

int main(){
  
  Phone p1;
  p1.Output();
  cout<<"\n\t ---------------------------";
  Phone p2(1001,2000);
  p2.Output();
  cout<<"\n\t ---------------------------";
  Phone p3 = p1;
  p3.Output();
  
  return 0;
}