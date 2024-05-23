#include <iostream>
#include <string>

using namespace std;

struct Car {
    int id;
    string make;
    string model;
    string type;
    int year;
    double price;
    Car* prev;
    Car* next;

    Car(int id, const string& make, const string& model, const string& type, int year, double price) :
        id(id), make(make), model(model), type(type), year(year), price(price), prev(nullptr), next(nullptr) {}
};

class CarShop {
private:
    Car* head;
    Car* tail;

public:
    CarShop() : head(nullptr), tail(nullptr) {}

    ~CarShop() {
        // Destructor to clear the linked list (optional)
        Car* current = head;
        while (current) {
            Car* temp = current->next;
            delete current;
            current = temp;
        }
    }

    void addCar(int id, const string& make, const string& model, const string& type, int year, double price) {
        Car* newCar = new Car(id, make, model, type, year, price);
        if (head == nullptr) {
            head = tail = newCar;
        } else {
            tail->next = newCar;
            newCar->prev = tail;
            tail = newCar;
        }
    }

    void displayCars() {
        if (head == nullptr) {
            cout << "No cars in the shop." << endl;
            return;
        }

        Car* current = head;
        cout << "Car List:\n";
        while (current) {
            cout << "ID: " << current->id << endl;
            cout << "Make: " << current->make << endl;
            cout << "Model: " << current->model << endl;
            cout << "Type: " << current->type << endl;
            cout << "Year: " << current->year << endl;
            cout << "Price: $" << current->price << endl;
            cout << "---------\n";
            current = current->next;
        }
    }

    bool removeCar(int id) {
        if (head == nullptr) {
            return false;
        }

        Car* current = head;
        while (current && current->id != id) {
            current = current->next;
        }

        if (current == nullptr) {
            return false; // Car not found
        }

        if (current == head) {
            head = head->next;
        } else {
            current->prev->next = current->next;
        }

        if (current == tail) {
            tail = tail->prev;
        } else {
            current->next->prev = current->prev;
        }

        delete current;
        return true;
    }

    bool findCarByModel(const string& model, Car*& foundCar) {
        if (head == nullptr) {
            return false;
        }

        Car* current = head;
        while (current) {
            if (current->model == model) {
                foundCar = current;
                return true;
            }
            current = current->next;
        }

        return false;
    }

    Car* findMostExpensiveCar() {
        if (head == nullptr) {
            return nullptr;
        }

        Car* mostExpensive = head;
        Car* current = head->next;
        while (current) {
            if (current->price > mostExpensive->price) {
                mostExpensive = current;
            }
            current = current->next;
        }

        return mostExpensive;
    }

    Car* findLeastExpensiveCar() {
        if (head == nullptr) {
            return nullptr;
        }

        Car* leastExpensive = head;
        Car* current = head->next;
        while (current) {
            if (current->price < leastExpensive->price) {
                leastExpensive = current;
            }
            current = current->next;
        }

        return leastExpensive;
    }
};

int main() {
    system("cls");
    CarShop shop;
        // Add initial cars (from your table)
    shop.addCar(1, "Toyota", "Camry", "sedan", 2015, 9800);
    shop.addCar(2, "Ford", "Escape", "crossover", 2015, 15900);
    shop.addCar(3, "Honda", "Civic", "sedan", 2016, 10200);
    shop.addCar(4, "Volkswagen", "Golf", "compact", 2014, 8800);
    shop.addCar(5, "Toyota", "RAV4", "crossover", 2016, 12800);

    // 1. Display initial car list
    cout << "\n** Initial Car List **\n";
    shop.displayCars();

    // 2. Add new cars
    shop.addCar(6, "Toyota", "Camry", "sedan", 2020, 15000);
    shop.addCar(7, "Honda", "Civic", "sedan", 2021, 25000);

    cout << "\n** Car List After Adding New Cars **\n";
    shop.displayCars();

    // 3. Remove sold-out cars (IDs 3 and 7)
    shop.removeCar(3);
    shop.removeCar(7); // Assuming car with ID 7 was also sold

    cout << "\n** Car List After Removing Sold Cars **\n";
    shop.displayCars();

    // 4. Check for car availability by model (Camry)
    Car* camryCar;
    if (shop.findCarByModel("Camry", camryCar)) {
        cout << "\n** Car Available with Model 'Camry': **\n";
        cout << "ID: " << camryCar->id << endl;
        cout << "Make: " << camryCar->make << endl;
        cout << "Model: " << camryCar->model << endl;
        // ... (display other car details)
    } else {
        cout << "\nNo car available with model 'Camry'." << endl;
    }

    // 5. Find most expensive and least expensive cars
    Car* mostExpensive = shop.findMostExpensiveCar();
    Car* leastExpensive = shop.findLeastExpensiveCar();

    if (mostExpensive) {
        cout << "\n** Most Expensive Car: **\n";
        cout << "ID: " << mostExpensive->id << endl;
        cout << "Make: " << mostExpensive->make << endl;
        cout << "Model: " << mostExpensive->model << endl;
        // ... (display other car details)
    } else {
        cout << "\nNo cars found in the shop." << endl;
    }

    if (leastExpensive) {
        cout << "\n** Least Expensive Car: **\n";
        cout << "ID: " << leastExpensive->id << endl;
        cout << "Make: " << leastExpensive->make << endl;
        cout << "Model: " << leastExpensive->model << endl;
        // ... (display other car details)
    } else {
        cout << "\nNo cars found in the shop." << endl;
    }

    return 0;
}

