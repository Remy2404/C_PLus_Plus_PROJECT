#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

int main() {
  // Read file
  ifstream fin("reportcard_updated.csv");

  // Create a vector to store the updated row
  vector<string> row;

  // Get roll number from the user
  cout << "Enter the roll number of the record to update: ";
  int rollnum;
  cin >> rollnum;

  // Get data to update
  cout << "Enter index of subject to update (M/P/C/B): ";
  char sub;
  cin >> sub;

  // Determine the index of the subject
  int index;
  switch (sub) {
    case 'M':
    case 'm':
      index = 2;
      break;
    case 'P':
    case 'p':
      index = 3;
      break;
    case 'C':
    case 'c':
      index = 4;
      break;
    case 'B':
    case 'b':
      index = 5;
      break;
    default:
      cout << "Wrong choice.\n";
      return 1;
  }

  // Get the new mark
  int newmarks;
  cout << "Enter new mark: ";
  cin >> newmarks;

  // Traverse the file
  string line;
  while (getline(fin, line)) {
    row.clear();

    // Split the line into a vector of strings
    stringstream s(line);
    string word;
    while (getline(s, word, ',')) {
      row.push_back(word);
    }

    // Check if the roll number matches
    int roll1 = stoi(row[0]);
    if (roll1 == rollnum) {
      // Update the mark
      row[index] = to_string(newmarks);

      // Write the updated row to the file
      for (int i = 0; i < row.size() - 1; i++) {
        cout << row[i] << ",";
      }
      cout << row[row.size() - 1] << endl;
    }
  }

  // Close the file
  fin.close();

  return 0;
}
