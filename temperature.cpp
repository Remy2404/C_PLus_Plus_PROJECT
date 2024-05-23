 #include <iostream>
#include <iomanip>

// Function to convert temperature units (Fahrenheit to Celsius)
double FahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

// Function to convert temperature units (Celsius to Fahrenheit)
double CelsiusToFahrenheit(double celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

// Function to convert distance units (Kilometers to Miles)
double KilometersToMiles(double kilometers) {
    return kilometers * 0.621371;
}

// Function to convert distance units (Miles to Kilometers)
double MilesToKilometers(double miles) {
    return miles / 0.621371;
}

// Function to convert time units (Hours to Minutes)
int HoursToMinutes(int hours) {
    return hours * 60;
}

// Function to convert time units (Minutes to Hours)
double MinutesToHours(double minutes) {
    return minutes / 60.0;
}

// Function to convert currency (using approximate rate)
double ConvertCurrency(double amount, double exchangeRate) {
    return amount * exchangeRate;
}

// Function to convert mass units (Kilograms to Pounds)
double KilogramsToPounds(double kilograms) {
    return kilograms * 2.20462;
}

// Function to convert mass units (Pounds to Kilograms)
double PoundsToKilograms(double pounds) {
    return pounds / 2.20462;
}

int main() {
    int choice;
    double value;

    while (true) {
        std::cout << "Unit Converter Menu:" << std::endl;
        std::cout << "1. Temperature (Fahrenheit to Celsius)" << std::endl;
        std::cout << "2. Temperature (Celsius to Fahrenheit)" << std::endl;
        std::cout << "3. Distance (Kilometers to Miles)" << std::endl;
        std::cout << "4. Distance (Miles to Kilometers)" << std::endl;
        std::cout << "5. Time (Hours to Minutes)" << std::endl;
        std::cout << "6. Time (Minutes to Hours)" << std::endl;
        std::cout << "7. Currency Conversion" << std::endl;
        std::cout << "8. Mass (Kilograms to Pounds)" << std::endl;
        std::cout << "9. Mass (Pounds to Kilograms)" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 0) {
            break;
        }

        std::cout << "Enter the value to convert: ";
        std::cin >> value;

        switch (choice) {
            case 1:
                std::cout << value << " Fahrenheit is " << FahrenheitToCelsius(value) << " Celsius" << std::endl;
                break;
            case 2:
                std::cout << value << " Celsius is " << CelsiusToFahrenheit(value) << " Fahrenheit" << std::endl;
                break;
            case 3:
                std::cout << value << " Kilometers is " << KilometersToMiles(value) << " Miles" << std::endl;
                break;
            case 4:
                std::cout << value << " Miles is " << MilesToKilometers(value) << " Kilometers" << std::endl;
                break;
            case 5:
                std::cout << value << " Hours is " << HoursToMinutes(value) << " Minutes" << std::endl;
                break;
            case 6:
                std::cout << value << " Minutes is " << MinutesToHours(value) << " Hours" << std::endl;
                break;
            case 7:
                double exchangeRate;
                std::cout << "Enter the exchange rate: ";
                std::cin >> exchangeRate;
                std::cout << value << " USD is " << ConvertCurrency(value, exchangeRate) << " Converted Currency" << std::endl;
                break;
            case 8:
                std::cout << value << " Kilograms is " << KilogramsToPounds(value) << " Pounds" << std::endl;
                break;
            case 9:
                std::cout << value << " Pounds is " << PoundsToKilograms(value) << " Kilograms" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        } 
    }

    return 0;
} 
