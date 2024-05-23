#include <iostream>
#include<fstream>
using namespace std;

class Person {
protected:
    string id;
    string name;
    string dob;

public:
    Person() {
        id = "unknown";
        name = "unknown";
        dob = "unknown";
    }

    Person(string id, string name, string dob) {
        this->id = id;
        this->name = name;
        this->dob = dob;
    }

    void input() {
        cout << "Enter your id                           : "; fflush(stdin); getline(cin, id);
        cout << "Enter your name                         : "; fflush(stdin); getline(cin, name);
        cout << "Enter your date of birth (dd/month/year): "; fflush(stdin); getline(cin, dob);
    }

    void output() {
        cout << "Id  >_<      : " << id << endl;
        cout << "Name         : " << name << endl;
        cout << "Date of Birth: " << dob << endl;
    }
};

class Student : public Person {
public:
    Student() : Person() {}

    Student(string id, string name, string dob) : Person(id, name, dob) {}

    void input() {
        Person::input();
    }

    void output() {
        Person::output();
    }
};

int main() {
    Student stu;
    fstream f;
    int i,n;
    f.open("Etec.bin",ios::out|ios::binary);
    
    stu.input();
    f.write((char *)&stu,sizeof(stu));
    f.close();

    return 0;
}