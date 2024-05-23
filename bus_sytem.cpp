#include <iostream>
#include <unordered_map>
#include <string>
#include <limits>
#include <opencv2/opencv.hpp> 
// Include OpenCV headers

// Structure for a bus ticket
struct BusTicket {
    std::string busType;
    int numberOfSeats;
    double costPerSeat;
    double totalLuggageLoad;
    int individualBagsAllowed;
};

// Function to retrieve available seats and their prices from a database or file
std::unordered_map<int, double> getAvailableSeats(const std::string& busType, int totalSeats) {
    // Simulating available seats in the database/file (seat number as key and price as value)
    std::unordered_map<int, double> availableSeats;

    for (int i = 1; i <= totalSeats; ++i) {
        availableSeats[i] = 50.0; // Assigning a default price
    }
    return availableSeats;
}

// Function to process reservations, cancellations, and refunds
bool processReservation(std::unordered_map<int, double>& availableSeats, std::unordered_map<int, BusTicket>& bookings, int ticketID, const std::string& action, double& customerBalance) {
    if (bookings.find(ticketID) == bookings.end()) {
        std::cout << "Invalid Ticket ID." << std::endl;
        return false;
    }

    if (action == "reserve") {
        if (availableSeats.find(ticketID) != availableSeats.end()) {
            if (customerBalance >= availableSeats[ticketID]) {
                customerBalance -= availableSeats[ticketID]; // Subtract ticket price from customer balance
                availableSeats.erase(ticketID); // Reserve the seat
                std::cout << "Seat reserved successfully!" << std::endl;
                return true;
            } else {
                std::cout << "Insufficient balance to reserve the seat." << std::endl;
            }
        } else {
            std::cout << "Seat is already reserved." << std::endl;
        }
    } else if (action == "cancel" || action == "refund") {
        if (availableSeats.find(ticketID) == availableSeats.end()) {
            customerBalance += bookings[ticketID].costPerSeat; // Refund the customer
            availableSeats[ticketID] = bookings[ticketID].costPerSeat; // Make the seat available again
            std::cout << "Seat cancellation or refund processed successfully!" << std::endl;
            return true;
        } else {
            std::cout << "Ticket ID not found or already canceled/refunded." << std::endl;
        }
    } else {
        std::cout << "Invalid action specified." << std::endl;
    }

    return false;
}

// Function for the user interface to book tickets
void bookTickets(std::unordered_map<int, double>& availableSeats, std::unordered_map<int, BusTicket>& bookings, double& customerBalance) {
    std::string busType;
    int numberOfSeats;

    std::cout << "Enter Bus Type: ";
    std::cin.ignore(); // Clear the newline character from the previous input
    std::getline(std::cin, busType);

    do {
        std::cout << "Enter Number of Seats: ";
        if (!(std::cin >> numberOfSeats) || numberOfSeats <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number of seats." << std::endl;
        }
    } while (numberOfSeats <= 0);

    std::unordered_map<int, double> available = getAvailableSeats(busType, numberOfSeats);

    std::cout << "Available Seats and Prices:" << std::endl;
    for (const auto& seat : available) {
        std::cout << "Seat " << seat.first << " - Price: $" << seat.second << std::endl;
    }

    // Simulation of selecting a seat for booking (assuming seat number is used as the ticket ID)
    int selectedSeat;
    std::cout << "Enter Seat Number to Book: ";
    std::cin >> selectedSeat;

    processReservation(availableSeats, bookings, selectedSeat, "reserve", customerBalance);

    // Load and display an image using OpenCV
    cv::Mat image = cv::imread("path_to_image.jpg");
    if (!image.empty()) {
        cv::imshow("Image", image);
        cv::waitKey(0);
    } else {
        std::cerr << "Error: Unable to load the image." << std::endl;
    }
}

// Function to display booking information
void displayBookingInfo(const std::unordered_map<int, BusTicket>& bookings) {
    std::cout << "Booking Information:" << std::endl;
    for (const auto& booking : bookings) {
        std::cout << "Ticket ID: " << booking.first << " - Bus Type: " << booking.second.busType
                  << " - Cost Per Seat: $" << booking.second.costPerSeat << std::endl;
    }
}

int main() {
    std::unordered_map<int, double> availableSeats;
    std::unordered_map<int, BusTicket> bookings;
    double customerBalance = 1000.0; // Assuming initial balance
    std::string action; // Declare 'action' here

    while (true) {
        int choice;
        std::cout << "1. Book Tickets\n2. View Booking Information\n3. Cancel/Refund Tickets\n4. Exit\nEnter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                bookTickets(availableSeats, bookings, customerBalance);
                break;
            case 2:
                displayBookingInfo(bookings);
                break;
            case 3:
                int ticketID;
                std::cin.ignore(); // Clear the newline character
                std::cout << "Enter Ticket ID: ";
                std::cin >> ticketID;
                std::cin.ignore(); // Clear the newline character
                std::cout << "Enter Action (reserve/cancel/refund): ";
                std::cin >> action;
                processReservation(availableSeats, bookings, ticketID, action, customerBalance);
                break;
            case 4:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
