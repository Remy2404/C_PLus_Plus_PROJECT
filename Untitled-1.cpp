#include <iostream>
#include <unordered_map>
#include <string>
#include <limits>

struct BusTicket {
    std::string busType;
    int numberOfSeats;
    double costPerSeat;
    double totalLuggageLoad;
    int individualBagsAllowed;
};

// Define data structures to store information
std::unordered_map<int, double> availableSeats;
std::unordered_map<int, BusTicket> bookings;
double customerBalance = 1000.0; // Initial customer balance

// ... Rest of your code ...

int main() {
    // ... Rest of your code ...

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
                std::string action;
                std::cin.ignore();
                std::cout << "Enter Ticket ID: ";
                std::cin >> ticketID;
                std::cin.ignore();
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
