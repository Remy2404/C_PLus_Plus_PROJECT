#include <iostream>

using namespace std;

void printArray(int arr[], int arr_size) {
    for (int i = 0; i < arr_size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void insertionSort(int arr[], int arr_size) {
    for (int i = 1; i < arr_size; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
 
int main() {

    system("cls");
    int arr[] = {6, 2, 5, 9, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "The current size of the array: " << n << endl;

    cout << "The unsorted array is: ";
    printArray(arr, n);

    insertionSort(arr, n);

    cout << "The sorted array is: ";
    printArray(arr, n);

    return 0;
}
