#include <iostream>
#include <vector>
#include <iomanip>
#include <conio.h>

using namespace std;

class Product {
public:
    string name;
    int qty;
    float price, discount;
};

class Customer {
protected:
    int id;
    string name, tell;
    vector<Product> products;

public:
    Customer() : id(0) {}

    int get_id() {
        return id;
    }

    void input1() {
        cout << "      Customer Information" << endl;

        cout << "Enter Name               :";
        cin >> name;
        cout << "Enter number phone       :";
        cin >> tell;
    }

    void input2() {
        cout << "          Product " << endl;
        cout << "Enter number of products :";
        int n;
        cin >> n;

        for (int i = 0; i < n; i++) {
            Product product;
            cout << "\t\tProduct " << i + 1 << endl;
            cout << "Enter Name           :";
            cin >> product.name;
            cout << "Enter Quantity       :";
            cin >> product.qty;
            cout << "Enter Price          :";
            cin >> product.price;
            cout << "Enter Discount       :";
            cin >> product.discount;

            products.push_back(product);
        }
        id++;
    }

    float findTotal(const Product& product) {
        return product.price * product.qty;
    }

    float findPayment(const Product& product) {
        return findTotal(product) - (findTotal(product) * product.discount) / 100;
    }

    void output1() {
        cout << "       RECEIPT" << endl;
        cout << "Name          :" << name << endl;
        cout << "Tell          :" << tell << endl;
        cout << "ID            :" << id << endl;
    }

    void output2() {
        for (size_t i = 0; i < products.size(); i++) {
            cout << left << setw(5) << i + 1
                 << left << setw(20) << products[i].name
                 << left << setw(10) << products[i].qty
                 << left << setw(10) << products[i].price << "$"
                 << left << setw(10) << findTotal(products[i]) << "$"
                 << left << setw(10) << products[i].discount << "%"
                 << left << setw(10) << findPayment(products[i]) << "$" << endl;
        }
    }
};

void head() {
    cout << left << setw(5) << "ItemNo:"
         << left << setw(20) << "Name"
         << left << setw(10) << "QTY"
         << left << setw(10) << "Price"
         << left << setw(10) << "Total Price"
         << left << setw(10) << "Discount"
         << left << setw(10) << "Payment" << endl;
}

int main() {
    int op;
    Customer cus;
    do {
        cout << "1. Enter Information" << endl;
        cout << "2. Show Information" << endl;
        cout << "3. Search Information" << endl;
        cout << "Please choose one option: ";
        cin >> op;
        switch (op) {
            case 1: {
                cus.input1();
                cus.input2();
            } break;
            case 2: {
                cus.output1();
                head();
                cus.output2();
            } break;
            case 3: {
                int search;
                cout << "Enter ID to search: ";
                cin >> search;
                if (search == cus.get_id()) {
                    cus.output1();
                    head();
                    cus.output2();
                }
            } break;
        }
        cout << "Press Enter to get back" << endl;
    } while (_getch() == 13);
    return 0;
}
