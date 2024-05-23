#ifndef DOG_H
#define DOG_H

#include <string>

class Dog {
public:
    Dog(); // Constructor
    Dog(const std::string& name, int age);

    void Bark() const;

private:
    std::string name;
    int age;
};

#endif
