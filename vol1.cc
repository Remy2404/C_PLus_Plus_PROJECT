#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>

using namespace std;

string generateRandomName() {
    // List of possible names
    vector<string> names = {"John", "Max", "Alice", "Bob", "Emma", "Charlie", "Olivia", "James", "Sophia", "Liam"};

    // Randomly select a name
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, names.size() - 1);

    return names[dis(gen)];
}

string generateRandomEmail(const string& name) {
    // Generating a simple email using the name
    return name + "@example.com";
}

string generateRandomPhoneNumber() {
    // Generating a random 10-digit phone number
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1000000000, 9999999999);

    return to_string(dis(gen));
}

void generateRandomData(const string& outputFileName, int numLines) {
    ofstream outputFile(outputFileName);

    if (!outputFile.is_open()) {
        cout << "Error opening file: " << outputFileName << endl;
        return;
    }

    outputFile << "ID,Name,Gender,Email,Phone" << endl;

    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    for (int i = 1; i <= numLines; ++i) {
        string name = generateRandomName();
        string gender = (rand() % 2 == 0) ? "M" : "F";
        string email = generateRandomEmail(name);
        string phone = generateRandomPhoneNumber();

        outputFile << i << ',' << name << ',' << gender << ',' << email << ',' << phone << endl;
    }

    outputFile.close();
}

int main() {
    int numLines = 50;
    string outputFileName = "random_data.csv";

    generateRandomData(outputFileName, numLines);

    cout << "CSV file created: " << outputFileName << endl;

    return 0;
}
