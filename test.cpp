#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Function to convert Fahrenheit to Celsius
double fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32) * 5.0 / 9.0;
}

// Function to convert Celsius to Fahrenheit
double celsiusToFahrenheit(double celsius) {
    return (celsius * 9.0 / 5.0) + 32;
}

// Function to save conversion records to a text file
void saveRecord(const std::string& filename, const std::string& fromUnit, const std::string& toUnit, double value, double result) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << fromUnit << " to " << toUnit << ": " << value << " -> " << result << std::endl;
        file.close();
    }
}

int main() {
    std::string filename = "conversion_records.txt";
    int choice;
    double value;

    while (true) {
        std::cout << "Temperature Converter:\n";
        std::cout << "1. Fahrenheit to Celsius\n";
        std::cout << "2. Celsius to Fahrenheit\n";
        std::cout << "3. Show Conversion Records\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 4) {
            break;  // Exit the program
        }

        if (choice == 1 || choice == 2) {
            std::string fromUnit, toUnit;
            double result;

            if (choice == 1) {
                fromUnit = "Fahrenheit";
                toUnit = "Celsius";
                std::cout << "Enter the temperature in Fahrenheit: ";
                std::cin >> value;
                result = fahrenheitToCelsius(value);
            } else if (choice == 2) {
                fromUnit = "Celsius";
                toUnit = "Fahrenheit";
                std::cout << "Enter the temperature in Celsius: ";
                std::cin >> value;
                result = celsiusToFahrenheit(value);
            }

            std::cout << "Result: " << value << " " << fromUnit << " is " << result << " " << toUnit << std::endl;

            // Save the conversion record to the text file
            saveRecord(filename, fromUnit, toUnit, value, result);
        } else if (choice == 3) {
            // Display conversion records from the text file
            std::ifstream file(filename);
            std::string line;
            std::cout << "Conversion Records:\n";
            while (std::getline(file, line)) {
                std::cout << line << std::endl;
            }
            file.close();
        } else {
            std::cout << "Invalid choice. Try again." << std::endl;
        }
    }

    return 0;
}