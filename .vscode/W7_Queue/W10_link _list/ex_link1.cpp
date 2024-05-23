#include <iostream>
using namespace std;

class Node 
{
public:
    int data;
    Node* next;
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};

class Linkedlist 
{
    Node* head;
public:
    Linkedlist()
    {
        head = NULL;
    }
    void insert_end(int data)
    {
        Node* newNode = new Node(data); 
        if (head == NULL) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    void insert_begin(int data) {
        Node* newNode = new Node(data);
        if (head == NULL){
            head = newNode;
            return;
        }
        else{
            newNode->next = head;
            head = newNode;
        }
    }
    void remove_front() {
        if (head == NULL || head->next == NULL){
            head = NULL;
            return;
        }
        head = head->next;
    }
    void remove_end(){
        if (head == NULL){
            cout << "This list is empty!";
            return;
        }
        if (head->next == NULL){
            delete head;
            head = NULL;
            return;
        }
        Node* temp = head;
        Node* prev = NULL;
        while (temp->next != NULL){
            prev = temp;
            temp = temp->next;
        }
        delete temp;
        prev->next = NULL;
    } 
    void printlist(){
        Node* temp = head;
        if (head == NULL) {
            cout << "List empty" << endl;
            return;
        }
        cout << "Elements of the list are: ";
        while (temp != NULL){
           cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    void search_elm(int item)
    {
        int count = 0;
        Node* temp = head;
        while (temp != NULL)
        {
            if (temp->data == item)
            {
                count++;
            }
            temp = temp->next;
        }
        if (count == 0)
        {
            cout << "Cannot find " << item << " in the list!" << endl;
        }
        else if (count == 1)
        {
            cout << item << " found: non-duplicated element in list!" << endl;
        }
        else
        {
            cout << item << " found: duplicated in list" << endl;
        }
    }
};

int main()
{
    Linkedlist list;
    list.insert_end(64);
    list.insert_end(33);
    list.insert_begin(10);
    list.insert_begin(77);
    list.printlist();

    list.remove_front();
    list.printlist();

    list.remove_end();
    list.printlist();

    return 0;
}