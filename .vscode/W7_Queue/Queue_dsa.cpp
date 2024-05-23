#include <iostream>
using namespace std;

class Queue {
private:
    static const int MAX_SIZE = 100;
    int arr[MAX_SIZE];
    int frontIndex;
    int rearIndex;

public:
    Queue() {
        frontIndex = -1;
        rearIndex = -1;
    }

    void push(int newData) {
        if (rearIndex == MAX_SIZE - 1) {
            cout << "Queue is full. Cannot push." << endl;
            return;
        }
        arr[++rearIndex] = newData;
        if (frontIndex == -1) {
            frontIndex = 0;
        }
    }

    void pop() {
        if (frontIndex == -1) {
            cout << "Queue is empty. Cannot pop." << endl;
            return;
        }
        if (frontIndex == rearIndex) {
            frontIndex = -1;
            rearIndex = -1;
        } else {
            frontIndex++;
        }
    }

    int size() {
        if (frontIndex == -1) {
            return 0;
        }
        return rearIndex - frontIndex + 1;
    }

    int front() {
        if (frontIndex == -1) {
            cout << "Queue is empty." << endl;
            return -1;
        }
        return arr[frontIndex];
    }

    int back() {
        if (rearIndex == -1) {
            cout << "Queue is empty." << endl;
            return -1;
        }
        return arr[rearIndex];
    }

    void display() {
        if (frontIndex == -1) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Queue elements: ";
        for (int i = frontIndex; i <= rearIndex; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Queue q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    q.push(6);


    cout << "Front element: " << q.front() << endl;
    cout << "Back element: " << q.back() << endl;
    cout << "Size: " << q.size() << endl;

    q.pop();
    q.display();

    return 0;
}
