#include "Cup.h"
#include <iostream>

Cup::Cup() : name(""), material("") {}

Cup::Cup(const std::string& name, const std::string& material) : name(name), material(material) {}

void Cup::ShowInfo() const {
    std::cout << "Cup Name: " << name << ", Material: " << material << std::endl;
}
