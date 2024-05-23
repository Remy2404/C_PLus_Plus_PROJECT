#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <array>
#include <chrono>

using namespace std;

struct Product {
    int id;
    string name;
    double price;
};

struct Transaction {
    int productId;
    int quantity;
    time_t timestamp;
};

class PosSystem {
private:
    vector<Product> products;
    vector<Transaction> transactions;
    const string dataFilePath = "pos_data.txt";

public:
    PosSystem() {
        readDataFromFile();
        time_t currentTime = time(nullptr);
        tm* localTime = localtime(&currentTime);
        cout << "POS system Started On: " << put_time(localTime, "%c") << endl;
    }

    void addProduct(int id, const string& name, double price) {
        Product product = {id, name, price};
        products.push_back(product);
        writeDataToFile();
        cout << "Product added successfully." << endl;
    }

    void displayProducts() const {
        cout << "Product List:" << endl;
        cout << "+-----+----------------------+----------+\n";
        cout << "| " << "ID" << "  | " << "Name" << "                 | " << "Price" << "    |\n";
        cout << "+-----+----------------------+----------+\n";
        for (const auto& product : products) {
            cout << "| " << setw(3) << product.id << " | " << setw(20) << product.name << " | " << setw(8) << product.price << " |\n";
        }
        cout << "+-----+----------------------+----------+\n";
    }

    void processTransaction(int productId, int quantity) {
        Transaction transaction = {productId, quantity, time(nullptr)};
        transactions.push_back(transaction);
        writeDataToFile();
        cout << "Transaction processed successfully." << endl;
    }

    void generateReceipt() const {
        double totalAmount = 0.0;
        double totalWithDiscount = 0.0;

        cout << "\nReceipt:" << endl;
        cout << "+----------------------+----------+------------+\n";
        cout << "| " << "Product" << "                 | " << "Quantity" << " | " << "Price" << "      | " << "Total" << "      |\n";
        cout << "+----------------------+----------+------------+\n";

        for (const auto& transaction : transactions) {
            const Product& product = getProductById(transaction.productId);
            double subtotal = transaction.quantity * product.price;
            totalAmount += subtotal;

            cout << "| " << setw(20) << product.name << " | " << setw(8) << transaction.quantity << " | " << setw(10) << product.price << " | " << setw(12) << subtotal << " |\n";
        }

        totalWithDiscount = calculateTotalWithDiscount(totalAmount);

        cout << "+----------------------+----------+------------+\n";
        cout << "\nTotal Amount: $" << totalAmount << "\n";
        cout << "Total Amount with Discount: $" << totalWithDiscount << "\n";
    }

    void deleteProduct(int productId) {
        auto it = remove_if(products.begin(), products.end(),
                                 [productId](const Product& p) { return p.id == productId; });
        if (it != products.end()) {
            products.erase(it, products.end());
            writeDataToFile();
            cout << "Product deleted successfully." << endl;
        } else {
            cout << "Product not found." << endl;
        }
    }

    void updateProduct(int productId, const string& newName, double newPrice) {
        for (auto& product : products) {
            if (product.id == productId) {
                product.name = newName;
                product.price = newPrice;
                writeDataToFile();
                cout << "Product updated successfully." << endl;
                return;
            }
        }
        cout << "Product not found." << endl;
    }

    void readDataFromFile() {
        ifstream inputFile(dataFilePath);
        if (!inputFile.is_open()) {
            cout << "File not found. Starting with an empty system." << endl;
            return;
        }

        products.clear();
        transactions.clear();

        int id;
        string name;
        double price;

        while (inputFile >> id >> name >> price) {
            Product product = {id, name, price};
            products.push_back(product);
        }

        inputFile.close();
    }

    void writeDataToFile() const {
        ofstream outputFile(dataFilePath);

        for (const auto& product : products) {
            outputFile << product.id << ' ' << product.name << ' ' << product.price << '\n';
        }

        outputFile.close();
    }

    void run() {
        char choice;

        do {
            cout << "\nOptions:" << endl;
            cout << "1. Add Product" << endl;
            cout << "2. Display Products" << endl;
            cout << "3. Process Transaction" << endl;
            cout << "4. Generate Receipt" << endl;
            cout << "5. Delete Product" << endl;
            cout << "6. Update Product" << endl;
            cout << "7. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case '1':
                    addProductFromInput();
                    break;
                case '2':
                    displayProducts();
                    break;
                case '3':
                    processTransactionFromInput();
                    break;
                case '4':
                    generateReceipt();
                    break;
                case '5':
                    deleteProductFromInput();
                    break;
                case '6':
                    updateProductFromInput();
                    break;
                case '7':
                    cout << "Exiting the POS system." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }

        } while (choice != '7');
    }

private:
    const Product& getProductById(int productId) const {
        for (const auto& product : products) {
            if (product.id == productId) {
                return product;
            }
        }

        throw runtime_error("Product not found");
    }

    void addProductFromInput() {
        int id;
        string name;
        double price;

        cout << "Enter product ID: ";
        cin >> id;

        cout << "Enter product name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter product price: ";
        cin >> price;

        addProduct(id, name, price);
    }

    void processTransactionFromInput() {
        int productId;
        int quantity;

        cout << "Enter product ID for the transaction: ";
        cin >> productId;

        cout << "Enter quantity for the transaction: ";
        cin >> quantity;

        processTransaction(productId, quantity);
    }

    void deleteProductFromInput() {
        int productId;

        cout << "Enter product ID to delete: ";
        cin >> productId;

        deleteProduct(productId);
    }

    void updateProductFromInput() {
        int productId;
        string newName;
        double newPrice;

        cout << "Enter product ID to update: ";
        cin >> productId;

        cout << "Enter new name for the product: ";
        cin.ignore();
        getline(cin, newName);

        cout << "Enter new price for the product: ";
        cin >> newPrice;

        updateProduct(productId, newName, newPrice);
    }

    double calculateTotalWithDiscount(double totalAmount) const {
        if (totalAmount >= 100.0) {
            return totalAmount - (totalAmount * 0.25);
        } else if (totalAmount >= 50.0) {
            return totalAmount - (totalAmount * 0.15);
        } else {
            return totalAmount;
        }
    }
};

int main() {
    PosSystem posSystem;
    posSystem.run();
    return 0;
}
