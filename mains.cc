#include <iostream>


using namespace std;

class MyArray
{
private:
    int Array_size;
    int arr[20]{};
    int elements;
    int position;

public:
    // Array Operation Insertion
    explicit MyArray(int size)
    {
        Array_size = size;
        elements = 0;
        position = 0;
    }

    // create a function to insert a value into the array
    void insert()
    {
        cout << "Enter the size for Array \U0001F607: ";
        cin >> Array_size;

        cout << "Enter " << Array_size << " elements: ";
        for (int i = 0; i < Array_size; i++) // insert the elements
        {
            cin >> arr[i];
            elements++;
        }

        // ask what element to insert
        cout << "Enter the element to insert \U0001F91E: ";
        int element;
        cin >> element;
        arr[elements] = element;
        elements++;

        // ask what position to insert in index  of array
        cout << "Enter the position to insert 🤞: ";
        cin >> position;
        if (position > elements)
        {
            cout << "Invalid position 😒" << endl;
            return;
        }
        // add a new element regarding the position
        for (int i = Array_size; i >= position; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[position - 1] = element;
        Array_size++;
        cout << "Element inserted successfully \U0001F60E" << endl;
   }

    // create a function to display the array that user input element
    void display()
    {
        cout << "Elements of Array: ";
        for (int i = 0; i < Array_size; i++)
        {
            cout << arr[i] << ", ";
        }
        cout << endl;
   }

    // create a function to delete the element of array
    void delete_element()
    {
        cout << "Enter the element to delete \U0001F607: ";
        int element;
        cin >> element;
        for (int i = 0; i < elements; i++)
        {
            if (arr[i] == element)
            {
                for (int j = i; j < elements - 1; j++)
                {
                    arr[j] = arr[j + 1];
                }
                elements--;
                cout << "Element deleted successfully 😀" << endl;
                return;
            }
        }
        cout << "Element not found 😒" << endl;
   }

    // create a function to search the element of array
    void search_element()
    {
        cout << "Enter the element to search 🤞: ";
        int element;
        cin >> element;
        for (int i = 0; i < elements; i++)
        {
            if (arr[i] == element)
            {
                cout << "Element found at index: " << i << endl;
                return;
            }
        }
        cout << "Element not found 😒" << endl;
   }
};

int main()
{
    MyArray array(20);
    int choice; // get the choice of user
    do
    {
        cout << "1. Insert element at the beginning of the array \U0001F91E" << endl;
        cout << "2. Display the array" << endl;
        cout << "3. Delete the element of array" << endl;
        cout << "4. Search the element of array" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            array.insert();
            break;
        case 2:
            array.display();
            break;
        case 3:
            array.delete_element();
            break;
        case 4:
            array.search_element();
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    } while (choice != 5);

    cout << "Program terminated successfully" << endl;
    cout << "Press any key to continue..." << endl;
    //--- End of the program ---//
    cin.ignore(); // ignore the enter key
    cin.get();    // get the next character

    return 0;
}
