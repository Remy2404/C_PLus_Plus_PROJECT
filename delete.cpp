#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib> // Added for remove and rename functions

using namespace std;

int main() {
    // Open the existing file for reading
    ifstream fin("reportcard.csv");
    // Create a new file to store the non-deleted data
    ofstream fout("reportcardnew.csv");

    int rollnum, roll1, count = 0;
    string line;
    vector<string> row;

    // Get the roll number to decide the data to be deleted
    cout << "Enter the roll number of the record to be deleted: ";
    cin >> rollnum;

    // Check if this record exists. If it exists, skip it and copy the rest of the data.
    while (getline(fin, line)) {
        row.clear();
        stringstream s(line);
        string word;

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        roll1 = stoi(row[0]);

        // Write all records, except the one to be deleted, to the new file.
        if (roll1 != rollnum) {
            for (size_t i = 0; i < row.size() - 1; i++) {
                fout << row[i] << ", ";
            }
            fout << row.back() << "\n";
        } else {
            count = 1;
        }
    }

    if (count == 1) {
        cout << "Record deleted" << endl;
    } else {
        cout << "Record not found" << endl;
    }

    // Close the files
    fin.close();
    fout.close();

    // Remove the existing file
    remove("reportcard.csv");
    // Rename the new file with the existing file name
    rename("reportcardnew.csv", "reportcard.csv");

    return 0;
}
