#include "Dog.h"
#include <iostream>

Dog::Dog() : name(""), age(0) {}

Dog::Dog(const std::string& name, int age) : name(name), age(age) {}

void Dog::Bark() const {
    std::cout << name << " is barking! Woof woof!" << std::endl;
}
