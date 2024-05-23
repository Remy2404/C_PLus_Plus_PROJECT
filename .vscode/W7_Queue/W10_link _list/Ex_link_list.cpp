#include <iostream>
using namespace std;

class Node {
public:
    string data;
    Node *next;

    Node(string value) {
        data = value;
        next = nullptr;
    }
};

class GroceryList {
private:
    Node *head;
    int size;

public:
    GroceryList() {
        head = nullptr;
        size = 0;
    }
// fuction insertAtBegin
    void insertAtBegin(string item) {
        Node *newNode = new Node(item);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void insertAtEnd(string item) {
        Node *newNode = new Node(item);

        if (head == nullptr) {
            head = newNode;
        } else {
            Node *current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    void insertAtIndex(string item, int index) {
        if (index < 0 || index > size) {
            cout << "Invalid index!" << endl;
            return;
        }

        if (index == 0) {
            insertAtBegin(item);
        } else if (index == size) {
            insertAtEnd(item);
        } else {
            Node *newNode = new Node(item);
            Node *current = head;
            for (int i = 0; i < (index - 1); i++) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            size++;
        }
    }

    void removeFromBegin() {
        if (head == nullptr) {
            cout << "The list is already empty!" << endl;
            return;
        }

        Node *temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    void removeFromEnd() {
        if (head == nullptr) {
            cout << "The list is already empty!" << endl;
            return;
        }

        Node *current = head;
        Node *previous = nullptr;
        while (current->next != nullptr) {
            previous = current;
            current = current->next;
        }

        if (previous == nullptr) {
            // Only one node in the list to delete
            head = nullptr;
        } else {
            previous->next = nullptr;
        }

        delete current;
        size--;
    }

    void removeAtIndex(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index!" << endl;
            return;
        }

        if (index == 0) {
            removeFromBegin();
        } else if (index == size - 1) {
            removeFromEnd();
        } else {
            Node *current = head;
            for (int i = 0; i < (index - 1); i++) {
                current = current->next;
            }
            Node *temp = current->next;
            current->next = temp->next;
            delete temp;
            size--;
        }
    }

    void display() {
        if (head == nullptr) {
            cout << "The list is empty!" << endl;
            return;
        }

        Node *current = head;
        while (current != nullptr) {
            cout << current->data << " - ";
            current = current->next;
        }
        cout << endl;
    }

    int getSize() {
        return size;
    }

    bool search(string item) {
        Node *current = head;
        while (current != nullptr) {
            if (current->data == item) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

int main() {
    system("cls");
    GroceryList list;
    cout << "Grocery Shopping List Application" << endl << endl;

    list.insertAtBegin("Eggs");
    list.insertAtBegin("Milk");
    list.insertAtEnd("Bread");
    list.insertAtIndex("Chicken", 2);

    cout << "Current shopping list: ";
    list.display();

    cout << "Size of the list: " << list.getSize() << endl;

    string searchItem = "Milk";
    if (list.search(searchItem)) {
        cout << searchItem << " is found in the shopping list." << endl;
    } else {
        cout << searchItem << " is not found in the shopping list." << endl;
    }

    list.removeFromEnd();
    cout << "Shopping list after removing the last item: ";
    list.display();

    list.removeAtIndex(1);
    cout << "Shopping list after removing item at index 1: ";
    list.display();

    return 0;
}