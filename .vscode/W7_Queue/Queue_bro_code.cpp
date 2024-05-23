#include<iostream>
#include <queue>

 using namespace std;

 void PrintmyQueue(queue<int> queue)
 {
    while (!queue.empty()){
        cout << queue.front() << " ";
        queue.pop();

    }
    cout << endl;
 }
void Check_Queue(queue <int> em_t){
    if(em_t.empty()==0){
        cout << "My Queue is Empty " << endl;
    }else {
            cout << "There is some elmemet in my Queue ";
        }
}

 int main(){
    system("cls");
    int n , element;

queue<int> myQueue;
myQueue.push(1);
myQueue.push(3);
myQueue.push(3);
myQueue.push(5);
myQueue.push(6);
cout << "Enter the numebr of element :";
cin >> n;
cout << "Enter the element : " << endl;
for (int i=0 ; i< n ; i++) {
    cin >> element;
    myQueue.push(element);
}
cout << "Element in the queue are : " << endl;
PrintmyQueue(myQueue);


cout << "My size Queue is : " << myQueue.size() << endl;
cout << "My first Queue is : " << myQueue.front() << endl;
cout << "My Last Queue is : " << myQueue.back() << endl;
cout << "My Empty : " << myQueue.empty() << endl;



cout << "My current queue : " << endl;
PrintmyQueue(myQueue);
cout << "My emply : ";
Check_Queue(myQueue);

    system("pause>0)");
 }