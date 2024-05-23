#include "University.h"
#include <iostream>

University::University() : name(""), foundationYear(0) {}

University::University(const std::string& name, int foundationYear)
    : name(name), foundationYear(foundationYear) {}

void University::DisplayInfo() const {
    std::cout << "University Name: " << name << ", Foundation Year: " << foundationYear << std::endl;
    std::cout << "DisplayInfo() was called" << std::endl;
}
