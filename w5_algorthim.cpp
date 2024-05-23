#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

// Template class for an array
template<typename T>
class Array {
private:
    vector<T> arr; // Vector to store elements of type T

public:
    // Function to insert an element into the array
    void insertElement(T element) {
        arr.push_back(element); // Insert element at the end of the array
    }

    // Function to delete the first element from the array
    void deleteFirstElement() {
        if (!arr.empty()) { // Check if the array is not empty
            arr.erase(arr.begin()); // Erase the first element
        }
    }

    // Function to delete the last element from the array
    void deleteLastElement() {
        if (!arr.empty()) { // Check if the array is not empty
            arr.pop_back(); // Remove the last element
        }
    }

    // Function to display the elements of the array
    void displayArray() {
        if (arr.empty()) { // Check if the array is empty
            cout << "Array is empty. No element to display." << endl;
        } else {
            cout << "Array elements:" << endl;
            // Iterate through the array and print each element
            for (const auto& element : arr) {
                cout << "   " << element;
            }
            cout << endl;
        }
    }

    // Function to search for an element in the array
    int searchElement(T element) {
        // Iterate through the array to find the element
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == element) { // If element found
                return i; // Return the index of the element
            }
        }
        return -1; // Return -1 if element not found
    }
};

// Main function
int main() {
    Array<int> arr; // Create an instance of Array class with int type
    string input; // Variable to store user input

    while (true) { // Continuous loop until user chooses to exit
        // Display menu options
        cout << "Menu:" << endl;
        cout << "1. Insert elements" << endl;
        cout << "2. Delete the first element" << endl;
        cout << "3. Delete the last element" << endl;
        cout << "4. Search for an element" << endl;
        cout << "5. Display array" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter your choice: ";
        getline(cin, input); // Read user input
        istringstream iss(input); // Convert input string to stringstream
        int choice;
        iss >> choice; // Extract choice from stringstream

        switch (choice) { // Switch statement based on user choice
            case 1: {
                cout << "Enter elements separated by space: ";
                getline(cin, input); // Read elements from user
                istringstream elementStream(input); // Convert elements string to stringstream
                int element;
                while (elementStream >> element) { // Extract each element and insert into array
                    arr.insertElement(element);
                }
                cout << "Elements inserted into the array." << endl;
                break;
            }
            case 2: {
                arr.deleteFirstElement(); // Delete the first element from the array
                cout << "Deleted the first element." << endl;
                break;
            }
            case 3: {
                arr.deleteLastElement(); // Delete the last element from the array
                cout << "Deleted the last element." << endl;
                break;
            }
            case 4: {
                cout << "Enter the value to search for: ";
                getline(cin, input); // Read value to search from user
                istringstream elementStream(input); // Convert value string to stringstream
                int element;
                elementStream >> element; // Extract value from stringstream
                int position = arr.searchElement(element); // Search for element in array
                if (position != -1) {
                    cout << "Found " << element << " at position " << position << "." << endl;
                } else {
                    cout << "Element not found." << endl;
                }
                break;
            }
            case 5: {
                arr.displayArray(); // Display the elements of the array
                break;
            }
            case 0: {
                cout << "Exiting the program..." << endl; // Exit the program
                return 0;
            }
            default:
                cout << "Invalid choice. Please try again." << endl; // Invalid choice
        }

        cout << endl; // Add a newline for better readability
    }

    return 0;
}
