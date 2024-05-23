#include <iostream>
using namespace std;

void swap_func(int array[], int position_1, int position_2)
{
    int temp = array[position_1];
    array[position_1] = array[position_2];
    array[position_2] = temp;
}

int main()
{
    system("cls");
    int max_size = 20;
    int i, j, temp, arr_size;
    int array[max_size];

    // Set the size of the array
    cout << "Enter the size of the array: ";
    cin >> arr_size;

    cout << "Enter " << arr_size << " elements: ";
    for (i = 0; i < arr_size; i++)
    {
        cin >> array[i];
    }

    cout << "Array before sorting: ";
    for (i = 0; i < arr_size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;

    // Algorithm for bubble sort in descending order
    for (i = 0; i < arr_size; i++)
    {
        for (j = 0; j < arr_size - 1; j++)
        {
            if (array[j] < array[j + 1])
            {
                swap_func(array, j, j + 1);

                cout << "Swapping (" << j << ", " << j + 1 << "): ";
                for (int k = 0; k < arr_size; k++)
                {
                    cout << array[k] << " ";
                }
                cout << endl;
            }
        }
    }

    // Display array after applying Bubble Sort in descending order
    cout << "Array after sorting: ";
    for (i = 0; i < arr_size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;

    return 0;
}
