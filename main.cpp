#include <iostream>
#include "University.h"
#include "Dog.h"
#include "Cup.h"

int main() {
    // Create arrays of objects
    University universities[5];
    Dog dogs[5];
    Cup cups[5];

    // Initialize objects and display information
    for (int i = 0; i < 5; ++i) {
        universities[i] = University("University " + std::to_string(i + 1), 2000 + i);
        dogs[i] = Dog("Dog " + std::to_string(i + 1), 2 * i + 1);
        cups[i] = Cup("Cup " + std::to_string(i + 1), "Material " + std::to_string(i + 1));
    }

    // Display information for each object
    for (int i = 0; i < 5; ++i) {
        std::cout << "University " << i + 1 << " Info:" << std::endl;
        universities[i].DisplayInfo();
        std::cout << "--------------------------" << std::endl;
        std::cout << "Dog " << i + 1 << " Info:" << std::endl;
        dogs[i].Bark();
        std::cout << "--------------------------" << std::endl;
        std::cout << "Cup " << i + 1 << " Info:" << std::endl;
        cups[i].ShowInfo();
        std::cout << "--------------------------" << std::endl;
    }

    return 0;
}
