#include <iostream>

using namespace std;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {  // Swap elements for descending order
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    int max_size = 100;  // Maximum array size
    int arr[max_size] ;

     // Initial array
     // Set the size of the array
    cout << "Enter the size of the array: ";
    cin >> max_size;

    cout << "Enter " << max_size << " elements: ";
    int n = sizeof(arr) / sizeof(arr[max_size]);

    bubbleSort(arr, n);

    cout << "Sorted array (descending): ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}
