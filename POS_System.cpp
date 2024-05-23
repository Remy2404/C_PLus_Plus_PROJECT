#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>  // Added for rand()

// Console color escape codes
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"

struct Product {
    int id;
    std::string name;
    double price;
};

struct Transaction {
    int productId;
    int quantity;
    time_t timestamp;
};

class PosSystem {
private:
    std::vector<Product> products;
    std::vector<Transaction> transactions;
    const std::string dataFilePath = "pos_data.txt";

public:
    PosSystem() {
        readDataFromFile();
        std::time_t currentTime = std::time(nullptr);
        std::tm* localTime = std::localtime(&currentTime);
        std::cout << GREEN << "POS system Started On: " << RESET << std::put_time(localTime, "%c") << std::endl;
    }

    void addProduct(int id, const std::string& name, double price) {
        Product product = {id, name, price};
        products.push_back(product);
        writeDataToFile();
        std::cout << GREEN << "Product added successfully." << RESET << std::endl;
    }

    void displayProducts() const {
        std::cout << GREEN << "Product List:" << RESET << std::endl;
        std::cout << "+-----+----------------------+----------+\n";
        std::cout << "| " << GREEN << "ID" << RESET << "  | " << BLUE << "Name" << RESET << "                 | " << RED << "Price" << RESET << "    |\n";
        std::cout << "+-----+----------------------+----------+\n";
        for (const auto& product : products) {
            std::cout << "| " << std::setw(3) << product.id << " | " << std::setw(20) << product.name << " | " << std::setw(8) << product.price << " |\n";
        }
        std::cout << "+-----+----------------------+----------+\n";
    }

    void processTransaction(int productId, int quantity) {
        Transaction transaction = {productId, quantity, std::time(nullptr)};
        transactions.push_back(transaction);
        writeDataToFile();
        std::cout << GREEN << "Transaction processed successfully." << RESET << std::endl;
    }

    void generateReceipt() const {
        double totalAmount = 0.0;
        double totalWithDiscount = 0.0;

        std::cout << GREEN << "\nReceipt:" << RESET << std::endl;
        std::cout << "+----------------------+----------+------------+\n";
        std::cout << "| " << BLUE << "Product" << RESET << "                 | " << RED << "Quantity" << RESET << " | " << RED << "Price" << RESET << "      | " << YELLOW << "Total" << RESET << "      |\n";
        std::cout << "+----------------------+----------+------------+\n";

        for (const auto& transaction : transactions) {
            const Product& product = getProductById(transaction.productId);
            double subtotal = transaction.quantity * product.price;
            totalAmount += subtotal;

            std::cout << "| " << std::setw(20) << product.name << " | " << std::setw(8) << transaction.quantity << " | " << std::setw(10) << product.price << " | " << std::setw(12) << subtotal << " |\n";
        }

        totalWithDiscount = calculateTotalWithDiscount(totalAmount);

        std::cout << "+----------------------+----------+------------+\n";
        std::cout << GREEN << "\nTotal Amount: $" << RESET << totalAmount << "\n";
        std::cout << GREEN << "Total Amount with Discount: $" << RESET << totalWithDiscount << "\n";
    }

    void deleteProduct(int productId) {
        auto it = std::remove_if(products.begin(), products.end(),
                                 [productId](const Product& p) { return p.id == productId; });
        if (it != products.end()) {
            products.erase(it, products.end());
            writeDataToFile();
            std::cout << GREEN << "Product deleted successfully." << RESET << std::endl;
        } else {
            std::cout << GREEN << "Product not found." << RESET << std::endl;
        }
    }

    void updateProduct(int productId, const std::string& newName, double newPrice) {
        for (auto& product : products) {
            if (product.id == productId) {
                product.name = newName;
                product.price = newPrice;
                writeDataToFile();
                std::cout << GREEN << "Product updated successfully." << RESET << std::endl;
                return;
            }
        }
        std::cout << GREEN << "Product not found." << RESET << std::endl;
    }

    void readDataFromFile() {
        std::ifstream inputFile(dataFilePath);
        if (!inputFile.is_open()) {
            std::cout << GREEN << "File not found. Starting with an empty system." << RESET << std::endl;
            return;
        }

        products.clear();
        transactions.clear();

        int id;
        std::string name;
        double price;

        while (inputFile >> id >> name >> price) {
            Product product = {id, name, price};
            products.push_back(product);
        }

        inputFile.close();
    }

    void writeDataToFile() const {
        std::ofstream outputFile(dataFilePath);

        for (const auto& product : products) {
            outputFile << product.id << ' ' << product.name << ' ' << product.price << '\n';
        }

        outputFile.close();
    }

    void run() {
        char choice;

        do {
            std::cout << GREEN << "\nOptions:" << RESET << std::endl;
            std::cout << BLUE << "1. Add Product" << RESET << std::endl;
            std::cout << BLUE << "2. Display Products" << RESET << std::endl;
            std::cout << BLUE << "3. Process Transaction" << RESET << std::endl;
            std::cout << BLUE << "4. Generate Receipt" << RESET << std::endl;
            std::cout << BLUE << "5. Delete Product" << RESET << std::endl;
            std::cout << BLUE << "6. Update Product" << RESET << std::endl;
            std::cout << BLUE << "7. Exit" << RESET << std::endl;
            std::cout << YELLOW << "Enter your choice: " << RESET;
            std::cin >> choice;

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
                    std::cout << GREEN << "Exiting the POS system." << RESET << std::endl;
                    break;
                default:
                    std::cout << GREEN << "Invalid choice. Please try again." << RESET << std::endl;
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

        throw std::runtime_error("Product not found");
    }

    void addProductFromInput() {
        int id;
        std::string name;
        double price;

        std::cout << YELLOW << "Enter product ID: " << RESET;
        std::cin >> id;

        std::cout << YELLOW << "Enter product name: " << RESET;
        std::cin.ignore();
        std::getline(std::cin, name);

        std::cout << YELLOW << "Enter product price: " << RESET;
        std::cin >> price;

        addProduct(id, name, price);
    }

    void processTransactionFromInput() {
        int productId;
        int quantity;

        std::cout << YELLOW << "Enter product ID for the transaction: " << RESET;
        std::cin >> productId;

        std::cout << YELLOW << "Enter quantity for the transaction: " << RESET;
        std::cin >> quantity;

        processTransaction(productId, quantity);
    }

    void deleteProductFromInput() {
        int productId;

        std::cout << YELLOW << "Enter product ID to delete: " << RESET;
        std::cin >> productId;

        deleteProduct(productId);
    }

    void updateProductFromInput() {
        int productId;
        std::string newName;
        double newPrice;

        std::cout << YELLOW << "Enter product ID to update: " << RESET;
        std::cin >> productId;

        std::cout << YELLOW << "Enter new name for the product: " << RESET;
        std::cin.ignore();
        std::getline(std::cin, newName);

        std::cout << YELLOW << "Enter new price for the product: " << RESET;
        std::cin >> newPrice;

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
