#include <iostream>

template <typename T>
class Array {
private:
    T* arr;
    int capacity;
    int size;

public:
    // Constructor with initial capacity
    Array(int capacity = 10) {
        this->capacity = capacity;
        this->size = 0;
        arr = new T[capacity];
    }

    // Destructor
    ~Array() {
        delete[] arr;
    }

    // Insert an element at the end
    void insert(T data) {
        if (size == capacity) {
            expandCapacity();
        }
        arr[size++] = data;
    }

    // Insert an element at a specific position
    void insertAt(T data, int index) {
        if (index < 0 || index > size) {
            std::cout << "Invalid index!\n";
            return;
        }
        if (size == capacity) {
            expandCapacity();
        }
        for (int i = size; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = data;
        size++;
    }

    // Display array elements
    void display() const {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    // Delete an element from a specific position
    void deleteAt(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Invalid index!\n";
            return;
        }
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }

    // Search for a non-duplicate element
    bool searchNonDuplicate(T data) const {
        for (int i = 0; i < size; i++) {
            if (arr[i] == data) {
                return true;
            }
        }
        return false;
    }

    // Search for a duplicate element
    bool searchDuplicate(T data) const {
        int count = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i] == data) {
                count++;
                if (count > 1) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    // Expand the capacity of the array
    void expandCapacity() {
        capacity *= 2;
        T* newArr = new T[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
};
