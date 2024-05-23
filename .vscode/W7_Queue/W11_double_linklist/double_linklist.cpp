#include <iostream>
using namespace std;
class Node {
public:
    int data;
    Node* prev;
    Node* next;
    Node(int data){
        this->data=data;
        this->next=nullptr;
        this->prev=nullptr;
    }
};

class DoublyLinkedList {
private:
    Node* head;

public:
    DoublyLinkedList()
    {
        head =nullptr;
    }
    

    // Insertion at the beginning
    void insertAtBeginning(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Insertion at the end
    void insertAtEnd(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current;
        }
    }

    // Insertion at a specific position
    void insertAtPosition(int data, int position) {
        if (position <= 0) {
            insertAtBeginning(data);
            return;
        }
        Node* newNode = new Node(data);
        Node* current = head;
        for (int i = 0; i < position - 1 && current; ++i) {
            current = current->next;
        }
        if (!current) {
          cout << "Invalid position. Insertion not possible." <<endl;
            return;
        }
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next) {
            current->next->prev = newNode;
        }
        current->next = newNode;
    }

    // Deletion at the beginning
    void deleteAtBeginning() {
        if (head) {
            Node* temp = head;
            head = head->next;
            if (head) {
                head->prev = nullptr;
            }
            delete temp;
        }
    }

    // Deletion at the end
    void deleteAtEnd() {
        if (head) {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            if (current->prev) {
                current->prev->next = nullptr;
            } else {
                head = nullptr;
            }
            delete current;
        }
    }

    // Deletion at a specific position
    void deleteAtPosition(int position) {
        if (position <= 0) {
            deleteAtBeginning();
            return;
        }
        Node* current = head;
        for (int i = 0; i < position && current; ++i) {
            current = current->next;
        }
        if (!current) {
            cout << "Invalid position. Deletion not possible." <<endl;
            return;
        }
        if (current->prev) {
            current->prev->next = current->next;
        } else {
            head = current->next;
        }
        if (current->next) {
            current->next->prev = current->prev;
        }
        delete current;
    }

    // Reverse the doubly linked list
    void reverse() {
        Node* current = head;
        Node* temp = nullptr;
        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if (temp) {
            head = temp->prev;
        }
    }

    // Search for a value and return its position (0-based index)
    int search(int data) {
        Node* current = head;
        int position = 0;
        while (current) {
            if (current->data == data) {
                return position;
            }
            current = current->next;
            ++position;
        }
        return -1; // Not found
    }

    // Display the doubly linked list
    void display() {
        Node* current = head;
        while (current) {
           cout << current->data << " ";
            current = current->next;
        }
       cout <<endl;
    }
    // check size of dubly link list
    int size(){
        Node* current = head;
        int count=0;
        while (current) {
           count++;
            current = current->next;
        }
        cout<< "The size of the dubly link list : "<<count<<endl;
        return count;
    }
};

int main() {
    system("cls");  
    // call the function : 
    DoublyLinkedList dll;
    cout <<"--------------------------------------------"<< endl;
    dll.insertAtBeginning(10);
    dll.insertAtEnd(20);
    dll.insertAtEnd(30);
    dll.insertAtPosition(15, 1);
    dll.display(); // Output: 10 15 20 30
    dll.size();
    dll.deleteAtPosition(7);
    dll.reverse();
    dll.display(); // Output: 30  15 10

    int searchValue = 10;// set value to search : 
    int position = dll.search(searchValue);
    if (position != -1) {
        cout << "Value " << searchValue << " found at position " << position << endl;
    } else {
        cout << "Value " << searchValue << " not found." << endl;
    }
    cout <<"--------------------------------------------"<< endl;

    return 0;
}
