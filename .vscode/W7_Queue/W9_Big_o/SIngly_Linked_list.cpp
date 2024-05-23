#include <iostream>
using namespace std;

class node {
public:
    int data;
    node *link;
    node(int data){
        this->data;
        this-link;
    }
 
};

int main() {
    system("cls");

    node *head = nullptr;
    node *tail = nullptr;
    node *second = nullptr;
    node *third = nullptr;
    node *fourth = nullptr;

    // Create the nodes
    head = new node();
    tail = new node();
    second = new node();
    third = new node();
    fourth = new node();
// insertion 
    head->data = 35;
    head->link = second;

    second->data = 43;
    second->link = third;

    third->data = 19;
    third->link = fourth;

    fourth->data = 65;
    fourth->link = tail;

    tail->data = 38;
    tail->link = nullptr;
// Display node :
    node* temp_node = head;
    cout << "The data in linked list: ";
    while (temp_node != nullptr) {
        cout << temp_node->data << " ";
        temp_node = temp_node->link;
    }
    cout << endl;

    // remove first node
    temp_node = head;
    head = head->link;
    delete temp_node;

// display after removeing first node 
    node* temp_node2 = head;
    cout << "The data in linked list after removing first node: ";
    while (temp_node2 != nullptr) {
        cout << temp_node2->data << " ";
        temp_node2 = temp_node2->link;
    }
    cout << endl;

    // clean up memory
    delete head;
    delete second;
    delete third;
    delete fourth;
    delete tail;

    return 0;
}