#include <iostream>
#include <vector>

using namespace std;

class Stack {
private:
    vector<int> data; // Dynamic array to store stack elements
public:
    // Push element onto the stack
    void push(int value) {
        data.push_back(value);
    }

    // Pop element from the stack
    void pop() {
        if (!isEmpty()) {
            data.pop_back();
        }
    }

    // Return the top element of the stack
    int top() {
        if (!isEmpty()) {
            return data.back();
        }
        return -1; // Stack is empty
    }

    // Return the size of the stack
    int size() {
        return data.size();
    }

    // Check if the stack is empty
    bool isEmpty() {
        return data.empty();
    }

    // Check if the stack is full (always false for a dynamic array)
    bool isFull() {
        return false;
    }
};

int main() {
    Stack stack;
    
    // Push elements onto the stack
    stack.push(10);
    stack.push(20);
    stack.push(30);
    
    cout << "Top element: " << stack.top() << endl; // Output: 30
    
    stack.pop();
    
    cout << "Size of stack: " << stack.size() << endl; // Output: 2
    
    cout << "Is stack empty? " << (stack.isEmpty() ? "Yes" : "No") << endl; // Output: No
    
    cout << "Is stack full? " << (stack.isFull() ? "Yes" : "No") << endl; // Output: No

    return 0;
}
