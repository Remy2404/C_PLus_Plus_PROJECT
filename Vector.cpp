#include <iostream>
#include <vector>

int main() {
    // Declare a vector of integers
    std::vector<int> myVector;

    // Add elements to the vector
    myVector.push_back(10);
    myVector.push_back(20);
    myVector.push_back(30);

    // Access elements using index
    std::cout << "First element: " << myVector[0] << std::endl;

    // Access elements using iterator
    std::cout << "Elements:";
    for (std::vector<int>::iterator it = myVector.begin(); it != myVector.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;

    // Size of the vector
    std::cout << "Vector size: " << myVector.size() << std::endl;

    // Modify elements
    myVector[1] = 50;

    // Remove the last element
    myVector.pop_back();

    return 0;
}
