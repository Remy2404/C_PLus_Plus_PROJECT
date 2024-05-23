#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib> // Added for remove and rename functions

using namespace std;

int main() {
    // Read file
    ifstream fin("reportcard.csv"); // Updated the input file name
    // Create a new file to store updated data
    ofstream fout("reportcardnew.csv"); // Updated the output file name
    int rollnum, roll1, marks, count = 0, i;
    char sub;
    int index, newmarks;
    string line, word;
    vector<string> row;

    // Get roll number from the user
    cout << "Enter the roll number of the record to update: ";
    cin >> rollnum;
    // Get data to update
    cout << "Enter index of subject to update (M/P/C/B): ";
    cin >> sub;

    // Determine the index of the subject
    if (sub == 'm' || sub == 'M')
        index = 2;
    else if (sub == 'p' || sub == 'P')
        index = 3;
    else if (sub == 'c' || sub == 'C')
        index = 4;
    else if (sub == 'b' || sub == 'B')
        index = 5;
    else {
        cout << "Wrong choice.\n";
        return 1; // Exiting the program since an invalid subject index was chosen
    }

    // Get the new mark
    cout << "Enter new mark: ";
    cin >> newmarks;

    // Traverse the file
    while (getline(fin, line)) { // Use getline directly
        row.clear();
        stringstream s(line);

        while (getline(s, word, ',')) { // Use ',' as the delimiter
            row.push_back(word);
        }

        roll1 = stoi(row[0]);
        int row_size = row.size();
        if (roll1 == rollnum) {
            count = 1;
            row[index] = to_string(newmarks); // Update the mark
            // Write the updated or existing data to the new file
            for (i = 0; i < row_size - 1; i++) { // Corrected the loop condition
                fout << row[i] << ",";
            }
            fout << row[row_size - 1] << endl;
        } else {
            for (i = 0; i < row_size - 1; i++) { // Corrected the loop condition
                fout << row[i] << ",";
            }
            fout << row[row_size - 1] << endl;
        }
    }

    // Close files
    if (count == 0) {
        cout << "Record not found!" << endl;
    }
    fin.close();
    fout.close();

    // Rename the new file to the original file
    remove("reportcard.csv"); // Updated the input file name
    rename("reportcardnew.csv", "reportcard.csv"); // Updated the file names
    return 0;
}
