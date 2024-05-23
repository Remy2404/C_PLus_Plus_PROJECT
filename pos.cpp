#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include <map>

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"

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

    // Map for multi-language support
    map<string, map<string, string>> languageTranslations;

public:
    PosSystem() {
        initializeLanguageTranslations();
        readDataFromFile();
        time_t currentTime = time(nullptr);
        tm* localTime = localtime(&currentTime);
        displayMessage("POS_SYSTEM_STARTED_ON", put_time(localTime, "%c"));
    }

    void addProduct(int id, const string& name, double price) {
        Product product = {id, name, price};
        products.push_back(product);
        writeDataToFile();
        displayMessage("PRODUCT_ADDED_SUCCESSFULLY");
    }

    void displayProducts() const {
        displayMessage("PRODUCT_LIST_HEADER");
        for (const auto& product : products) {
            cout << "| " << setw(3) << product.id << " | " << setw(20) << product.name << " | $" << setw(7) << fixed << setprecision(2) << product.price << "   |\n";
        }
        displayMessage("PRODUCT_LIST_FOOTER");
    }

    void processTransaction(int productId, int quantity) {
        Transaction transaction = {productId, quantity, time(nullptr)};
        transactions.push_back(transaction);
        writeDataToFile();
        displayMessage("TRANSACTION_PROCESSED_SUCCESSFULLY");
    }

    void generateReceipt() const {
        double totalAmount = 0.0;
        double totalWithDiscount = 0.0;

        displayMessage("RECEIPT_HEADER");
        for (const auto& transaction : transactions) {
            const Product& product = getProductById(transaction.productId);
            double subtotal = transaction.quantity * product.price;
            totalAmount += subtotal;

            cout << "| " << setw(20) << product.name << " | " << setw(8) << transaction.quantity << " | " << setw(10) << product.price << " | " << setw(12) << subtotal << " |\n";
        }

        totalWithDiscount = calculateTotalWithDiscount(totalAmount);

        displayMessage("RECEIPT_FOOTER_TOTAL_AMOUNT", to_string(totalAmount));
        displayMessage("RECEIPT_FOOTER_TOTAL_WITH_DISCOUNT", to_string(totalWithDiscount));
    }

    void deleteProduct(int productId) {
        auto it = remove_if(products.begin(), products.end(),
                            [productId](const Product& p) { return p.id == productId; });
        if (it != products.end()) {
            products.erase(it, products.end());
            writeDataToFile();
            displayMessage("PRODUCT_DELETED_SUCCESSFULLY");
        } else {
            displayMessage("PRODUCT_NOT_FOUND");
        }
    }

    void updateProduct(int productId, const string& newName, double newPrice) {
        for (auto& product : products) {
            if (product.id == productId) {
                product.name = newName;
                product.price = newPrice;
                writeDataToFile();
                displayMessage("PRODUCT_UPDATED_SUCCESSFULLY");
                return;
            }
        }
        displayMessage("PRODUCT_NOT_FOUND");
    }

    void viewTransactionHistory() const {
        displayMessage("TRANSACTION_HISTORY_HEADER");
        for (const auto& transaction : transactions) {
            const Product& product = getProductById(transaction.productId);
            tm* transactionTime = localtime(&transaction.timestamp);
            cout << "| " << setw(20) << product.name << " | " << setw(8) << transaction.quantity << " | " << put_time(transactionTime, "%c") << " |\n";
        }
        displayMessage("TRANSACTION_HISTORY_FOOTER");
    }

    void viewSalesReport() const {
        displayMessage("SALES_REPORT_HEADER");
        double totalSales = 0.0;

        for (const auto& transaction : transactions) {
            const Product& product = getProductById(transaction.productId);
            double salesAmount = transaction.quantity * product.price;
            totalSales += salesAmount;
        }

        displayMessage("SALES_REPORT_TOTAL_SALES", to_string(totalSales));
        displayMessage("SALES_REPORT_FOOTER");
    }

    void printReceiptToFile() const {
        ofstream receiptFile("receipt.txt");
        if (receiptFile.is_open()) {
            displayMessage("RECEIPT_HEADER_FILE");

            for (const auto& transaction : transactions) {
                const Product& product = getProductById(transaction.productId);
                double subtotal = transaction.quantity * product.price;

                receiptFile << "| " << setw(20) << product.name << " | " << setw(8) << transaction.quantity << " | " << setw(10) << product.price
                            << " | " << setw(12) << subtotal << " |\n";
            }

            double totalAmount = 0.0;
            double totalWithDiscount = calculateTotalWithDiscount(totalAmount);

            receiptFile << "+----------------------+----------+------------+\n";
            receiptFile << "\n" << getTranslatedMessage("TOTAL_AMOUNT") << ": $" << totalAmount << "\n";
            receiptFile << getTranslatedMessage("TOTAL_WITH_DISCOUNT") << ": $" << totalWithDiscount << "\n";

            displayMessage("RECEIPT_FOOTER_FILE");
            receiptFile.close();
            displayMessage("RECEIPT_PRINTED_TO_FILE");
        } else {
            cout << RED << "Error: Unable to open 'receipt.txt' for printing receipt." << RESET << endl;
        }
    }

    void searchProducts(const string& keyword) const {
        displayMessage("SEARCH_RESULTS_HEADER");
        for (const auto& product : products) {
            if (product.name.find(keyword) != string::npos) {
                cout << "| " << setw(3) << product.id << " | " << setw(20) << product.name << " | $" << setw(7) << fixed << setprecision(2) << product.price << "   |\n";
            }
        }
        displayMessage("SEARCH_RESULTS_FOOTER");
    }

    void multiLanguageSupport() {
        cout << YELLOW << "Select Language (EN/KH/TH/ZH): " << RESET;
        string language;
        cin >> language;

        transform(language.begin(), language.end(), language.begin(), ::toupper);

        if (languageTranslations.find(language) == languageTranslations.end()) {
            cout << RED << "Invalid language code. Using English." << RESET << endl;
            language = "EN";
        }

        displayMessage("LANGUAGE_SELECTED", language);
    }

    void run() {
        char choice;

        do {
            displayOptions();
            cout << YELLOW << getTranslatedMessage("ENTER_YOUR_CHOICE") << RESET;
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
                    viewTransactionHistory();
                    break;
                case '8':
                    viewSalesReport();
                    break;
                case '9':
                    printReceiptToFile();
                    break;
                case '10':
                    searchProductsFromInput();
                    break;
                case '11':
                    viewProductStatistics();
                    break;
                case '12':
                    setCurrencyFormat();
                    break;
                case '13':
                    setTaxRate();
                    break;
                case '14':
                    multiLanguageSupport();
                    break;
                case '15':
                    cout << GREEN << getTranslatedMessage("EXITING_POS_SYSTEM") << RESET << endl;
                    break;
                default:
                    cout << RED << getTranslatedMessage("INVALID_CHOICE") << RESET << endl;
            }

        } while (choice != '15');
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

        cout << YELLOW << getTranslatedMessage("ENTER_PRODUCT_ID") << RESET;
        cin >> id;

        cout << YELLOW << getTranslatedMessage("ENTER_PRODUCT_NAME") << RESET;
        cin.ignore();
        getline(cin, name);

        cout << YELLOW << getTranslatedMessage("ENTER_PRODUCT_PRICE") << RESET;
        cin >> price;

        addProduct(id, name, price);
    }

    void processTransactionFromInput() {
        int productId;
        int quantity;

        cout << YELLOW << getTranslatedMessage("ENTER_PRODUCT_ID_FOR_TRANSACTION") << RESET;
        cin >> productId;

        cout << YELLOW << getTranslatedMessage("ENTER_QUANTITY_FOR_TRANSACTION") << RESET;
        cin >> quantity;

        processTransaction(productId, quantity);
    }

    void deleteProductFromInput() {
        int productId;

        cout << YELLOW << getTranslatedMessage("ENTER_PRODUCT_ID_TO_DELETE") << RESET;
        cin >> productId;

        deleteProduct(productId);
    }

    void updateProductFromInput() {
        int productId;
        string newName;
        double newPrice;

        cout << YELLOW << getTranslatedMessage("ENTER_PRODUCT_ID_TO_UPDATE") << RESET;
        cin >> productId;

        cout << YELLOW << getTranslatedMessage("ENTER_NEW_NAME_FOR_PRODUCT") << RESET;
        cin.ignore();
        getline(cin, newName);

        cout << YELLOW << getTranslatedMessage("ENTER_NEW_PRICE_FOR_PRODUCT") << RESET;
        cin >> newPrice;

        updateProduct(productId, newName, newPrice);
    }

    void searchProductsFromInput() {
        string keyword;

        cout << YELLOW << getTranslatedMessage("ENTER_KEYWORD_FOR_SEARCH") << RESET;
        cin.ignore();
        getline(cin, keyword);

        searchProducts(keyword);
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

    void displayOptions() const {
        displayMessage("OPTIONS");
    }

    void readDataFromFile() {
        ifstream inputFile(dataFilePath);
        if (!inputFile.is_open()) {
            cout << GREEN << getTranslatedMessage("FILE_NOT_FOUND_STARTING_EMPTY_SYSTEM") << RESET << endl;
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

    // Function to get translated message for a given key
    string getTranslatedMessage(const string& key) const {
        // Default language is English
        string language = "EN";

        // Check if a different language is selected
        if (!languageTranslations.empty()) {
            cout << YELLOW << getTranslatedMessage("SELECT_LANGUAGE") << RESET;
            cin >> language;

            // Convert to uppercase for consistency
            transform(language.begin(), language.end(), language.begin(), ::toupper);

            // Validate language selection
            if (languageTranslations.find(language) == languageTranslations.end()) {
                cout << RED << getTranslatedMessage("INVALID_LANGUAGE_USING_ENGLISH") << RESET << endl;
                language = "EN";
            }
        }

        // Check if the key exists in the selected language
        if (languageTranslations[language].find(key) != languageTranslations[language].end()) {
            return languageTranslations[language][key];
        } else {
            return "Translation not available for key: " + key;
        }
    }

    // Function to display translated message
    void displayMessage(const string& key, const string& additionalText = "") const {
        cout << getTranslatedMessage(key) << additionalText << endl;
    }

    // Function to initialize language translations
    void initializeLanguageTranslations() {
        // English translations
        languageTranslations["EN"] = {
            {"POS_SYSTEM_STARTED_ON", "POS system Started On: "},
            {"PRODUCT_ADDED_SUCCESSFULLY", "Product added successfully."},
            {"OPTIONS", "\nOptions:"},
            {"ENTER_YOUR_CHOICE", "Enter your choice: "},
            {"INVALID_CHOICE", "Invalid choice. Please try again."},
            {"EXITING_POS_SYSTEM", "Exiting the POS system."},
            {"FILE_NOT_FOUND_STARTING_EMPTY_SYSTEM", "File not found. Starting with an empty system."},
            {"PRODUCT_DELETED_SUCCESSFULLY", "Product deleted successfully."},
            {"PRODUCT_UPDATED_SUCCESSFULLY", "Product updated successfully."},
            {"TRANSACTION_PROCESSED_SUCCESSFULLY", "Transaction processed successfully."},
            {"PRODUCT_NOT_FOUND", "Product not found."},
            {"TOTAL_AMOUNT", "Total Amount"},
            {"TOTAL_WITH_DISCOUNT", "Total Amount with Discount"},
            {"RECEIPT_HEADER", "\nReceipt:"},
            {"RECEIPT_FOOTER_TOTAL_AMOUNT", "\nTotal Amount: $"},
            {"RECEIPT_FOOTER_TOTAL_WITH_DISCOUNT", "Total Amount with Discount: $"},
            {"SEARCH_RESULTS_HEADER", "\nSearch Results:"},
            {"SEARCH_RESULTS_FOOTER", "Search completed."},
            {"TRANSACTION_HISTORY_HEADER", "\nTransaction History:"},
            {"TRANSACTION_HISTORY_FOOTER", "End of Transaction History."},
            {"SALES_REPORT_HEADER", "\nSales Report:"},
            {"SALES_REPORT_TOTAL_SALES", "Total Sales: $"},
            {"SALES_REPORT_FOOTER", "End of Sales Report."},
            {"RECEIPT_HEADER_FILE", "Receipt (Printed to 'receipt.txt'):"},
            {"RECEIPT_FOOTER_FILE", "\nEnd of Receipt (Printed to 'receipt.txt')."},
            {"RECEIPT_PRINTED_TO_FILE", "Receipt printed to 'receipt.txt'."},
            {"SEARCH_RESULTS_PLACEHOLDER", "Search results placeholder."},
            {"PRODUCT_STATISTICS_PLACEHOLDER", "Product statistics placeholder."},
            {"CURRENCY_FORMAT_PLACEHOLDER", "Currency format placeholder."},
            {"TAX_RATE_PLACEHOLDER", "Tax rate placeholder."},
            {"LANGUAGE_SELECTED", "Language selected: "},
            {"SELECT_LANGUAGE", "Select Language (EN/KH/TH/ZH): "},
            {"INVALID_LANGUAGE_USING_ENGLISH", "Invalid language code. Using English."},
            {"ENTER_PRODUCT_ID", "Enter product ID: "},
            {"ENTER_PRODUCT_NAME", "Enter product name: "},
            {"ENTER_PRODUCT_PRICE", "Enter product price: "},
            {"ENTER_PRODUCT_ID_FOR_TRANSACTION", "Enter product ID for the transaction: "},
            {"ENTER_QUANTITY_FOR_TRANSACTION", "Enter quantity for the transaction: "},
            {"ENTER_PRODUCT_ID_TO_DELETE", "Enter product ID to delete: "},
            {"ENTER_PRODUCT_ID_TO_UPDATE", "Enter product ID to update: "},
            {"ENTER_NEW_NAME_FOR_PRODUCT", "Enter new name for the product: "},
            {"ENTER_NEW_PRICE_FOR_PRODUCT", "Enter new price for the product: "},
            {"ENTER_KEYWORD_FOR_SEARCH", "Enter keyword for search: "},
            {"OPTIONS", "\nOptions:"},
            {"OPTIONS", "\nOptions:"},
            {"OPTIONS", "\nOptions:"},
            {"OPTIONS", "\nOptions:"},
            {"OPTIONS", "\nOptions:"}
            // ... Add more translations as needed
        };

        // Khmer translations
        languageTranslations["KH"] = {
            {"POS_SYSTEM_STARTED_ON", "ប្រព័ន្ធ POS ត្រូវបានចាត់ថ្នាក់ថ្ងៃនៅ: "},
            {"PRODUCT_ADDED_SUCCESSFULLY", "បន្ថែមផលិតផលដោយជោគជ័យ។"},
            {"OPTIONS", "\nជម្រើស:"},
            {"ENTER_YOUR_CHOICE", "បញ្ចូលការជ្រើសរើសរបស់អ្នក: "},
            {"INVALID_CHOICE", "ជ្រើសរើសមិនត្រឹមត្រូវ។ សូមព្យាយាមម្តិត។"},
            {"EXITING_POS_SYSTEM", "ចាកចេញពីប្រព័ន្ធ POS។"},
            {"FILE_NOT_FOUND_STARTING_EMPTY_SYSTEM", "រូបស័ព្ទរកឃាត់។ កំពុងចាប់ផ្តើមជាប្រព័ន្ធទទេ។"},
            {"PRODUCT_DELETED_SUCCESSFULLY", "បានលុបផលិតផលដោយជោគជ័យ។"},
            {"PRODUCT_UPDATED_SUCCESSFULLY", "បានធ្វើបច្ចុប្បន្នភាពផលិតផលដោយជោគជ័យ។"},
            {"TRANSACTION_PROCESSED_SUCCESSFULLY", "បានដោះស្រាយប្រវត្តិដោយជោគជ័យ។"},
            {"PRODUCT_NOT_FOUND", "រកមិនឃើញផលិតផល។"},
            {"TOTAL_AMOUNT", "ទឹកប្រាក់សរុប"},
            {"TOTAL_WITH_DISCOUNT", "ទឹកប្រាក់សរុបដោយការបញ្ចុះតម្លៃ"},
            {"RECEIPT_HEADER", "\nវិក្កយបត្រ:"},
            {"RECEIPT_FOOTER_TOTAL_AMOUNT", "\nទឹកប្រាក់សរុប: $"},
            {"RECEIPT_FOOTER_TOTAL_WITH_DISCOUNT", "ទឹកប្រាក់សរុបដោយការបញ្ចុះតម្លៃ: $"},
            {"SEARCH_RESULTS_HEADER", "\nលទ្ធផលស្វែងរក:"},
            {"SEARCH_RESULTS_FOOTER", "ស្វែងរកបានបញ្ចប់។"},
            {"TRANSACTION_HISTORY_HEADER", "\nប្រវត្តិរបាយកម្រិត:"},
            {"TRANSACTION_HISTORY_FOOTER", "ចុងក្រោយនៃប្រវត្តិរបាយ។"},
            {"SALES_REPORT_HEADER", "\nរបាយការលក់:"},
            {"SALES_REPORT_TOTAL_SALES", "ប្រាក់លក់សរុប: $"},
            {"SALES_REPORT_FOOTER", "ចុងក្រោយនៃរបាយការលក់។"},
            {"RECEIPT_HEADER_FILE", "វិក្កយបត្រ (បានបោះពុម្ពទៅ 'receipt.txt'):"},
            {"RECEIPT_FOOTER_FILE", "\nចុងក្រោយនៃវិក្កយបត្រ (បានបោះពុម្ពទៅ 'receipt.txt')។"},
            {"RECEIPT_PRINTED_TO_FILE", "វិក្កយបត្របានបោះពុម្ពទៅ 'receipt.txt'។"},
            {"SEARCH_RESULTS_PLACEHOLDER", "កម្មវិធីដែលមិនមានស្វែងរកបាន។"},
            {"PRODUCT_STATISTICS_PLACEHOLDER", "កម្មវិធីស្ថិតិនៃផលិតផល។"},
            {"CURRENCY_FORMAT_PLACEHOLDER", "កម្មវិធីស្ថិតិនៃទំនិញរូបិយប័ណ្ណ។"},
            {"TAX_RATE_PLACEHOLDER", "កម្មវិធីស្ថិតិនៃអត្រា​ពន្ធ។"},
            {"LANGUAGE_SELECTED", "បានជ្រើសរើសភាសា: "},
            {"SELECT_LANGUAGE", "ជ្រើសរើសភាសា (EN/KH/TH/ZH): "},
            {"INVALID_LANGUAGE_USING_ENGLISH", "លោកអ្នកបានបញ្ចូលកូដភាសាមិនត្រឹមត្រូវ។ កំពុងប្រើភាសាអង់គ្លេស។"},
            {"ENTER_PRODUCT_ID", "បញ្ចូលលេខសម្គាល់ផលិតផល: "},
            {"ENTER_PRODUCT_NAME", "បញ្ចូលឈ្មោះផលិតផល: "},
            {"ENTER_PRODUCT_PRICE", "បញ្ចូលតម្លៃផលិតផល: "},
            {"ENTER_PRODUCT_ID_FOR_TRANSACTION", "បញ្ចូលលេខសម្គាល់ផលិតផលសម្រាប់ប្រវត្តិ: "},
            {"ENTER_QUANTITY_FOR_TRANSACTION", "បញ្ចូលចំនួនសម្រាប់ប្រវត្តិ: "},
            {"ENTER_PRODUCT_ID_TO_DELETE", "បញ្ចូលលេខសម្គាល់ផលិតផលសម្រាប់លុប: "},
                       {"ENTER_PRODUCT_ID_TO_UPDATE", "បញ្ចូលលេខសម្គាល់ផលិតផលសម្រាប់ធ្វើបច្ចុប្បន្នភាព: "},
            {"ENTER_NEW_NAME_FOR_PRODUCT", "បញ្ចូលឈ្មោះថ្មីសម្រាប់ផលិតផល: "},
            {"ENTER_NEW_PRICE_FOR_PRODUCT", "បញ្ចូលតម្លៃថ្មីសម្រាប់ផលិតផល: "},
            {"ENTER_KEYWORD_FOR_SEARCH", "បញ្ចូលពាក្យគន្លឹះសម្រាប់ស្វែងរក: "},
            {"OPTIONS", "\nជម្រើស:"},
            {"OPTIONS", "\nជម្រើស:"},
            {"OPTIONS", "\nជម្រើស:"},
            {"OPTIONS", "\nជម្រើស:"},
            {"OPTIONS", "\nជម្រើស:"}
            // ... Add more translations as needed
        };

 // Thai translations
languageTranslations["TH"] = {
    {"POS_SYSTEM_STARTED_ON", "ระบบ POS ได้เริ่มทำงานเมื่อ: "},
    // ... Add Thai translations similar to other languages
    {"OPTIONS", "\nตัวเลือก:"},
    {"ENTER_YOUR_CHOICE", "กรุณาป้อนตัวเลือกของคุณ: "},
    {"INVALID_CHOICE", "ตัวเลือกไม่ถูกต้อง กรุณาลองอีกครั้ง."},
    {"EXITING_POS_SYSTEM", "กำลังออกจากระบบ POS."},
    {"FILE_NOT_FOUND_STARTING_EMPTY_SYSTEM", "ไม่พบไฟล์ กำลังเริ่มต้นด้วยระบบที่ว่างเปล่า."},
    {"PRODUCT_DELETED_SUCCESSFULLY", "ลบสินค้าเรียบร้อยแล้ว."},
    {"PRODUCT_UPDATED_SUCCESSFULLY", "อัปเดตสินค้าเรียบร้อยแล้ว."},
    {"TRANSACTION_PROCESSED_SUCCESSFULLY", "ทำรายการสำเร็จแล้ว."},
    {"PRODUCT_NOT_FOUND", "ไม่พบสินค้า."},
    {"TOTAL_AMOUNT", "ยอดรวม"},
    {"TOTAL_WITH_DISCOUNT", "ยอดรวมราคาส่วนลด"},
    {"RECEIPT_HEADER", "\nใบเสร็จ:"},
    {"RECEIPT_FOOTER_TOTAL_AMOUNT", "\nยอดรวม: $"},
    {"RECEIPT_FOOTER_TOTAL_WITH_DISCOUNT", "ยอดรวมราคาส่วนลด: $"},
    {"SEARCH_RESULTS_HEADER", "\nผลลัพธ์การค้นหา:"},
    {"SEARCH_RESULTS_FOOTER", "การค้นหาเสร็จสมบูรณ์."},
    {"TRANSACTION_HISTORY_HEADER", "\nประวัติการทำรายการ:"},
    {"TRANSACTION_HISTORY_FOOTER", "สิ้นสุดประวัติการทำรายการ."},
    {"SALES_REPORT_HEADER", "\nรายงานการขาย:"},
    {"SALES_REPORT_TOTAL_SALES", "ยอดขายรวม: $"},
    {"SALES_REPORT_FOOTER", "สิ้นสุดรายงานการขาย."},
    {"RECEIPT_HEADER_FILE", "ใบเสร็จ (ถูกพิมพ์ที่ 'receipt.txt'):"},
    {"RECEIPT_FOOTER_FILE", "\nสิ้นสุดใบเสร็จ (ถูกพิมพ์ที่ 'receipt.txt')."},
    {"RECEIPT_PRINTED_TO_FILE", "ได้ทำการพิมพ์ใบเสร็จที่ 'receipt.txt'."},
    {"SEARCH_RESULTS_PLACEHOLDER", "ผลลัพธ์ค้นหา (ที่มีข้อมูล):"},
    {"PRODUCT_STATISTICS_PLACEHOLDER", "ข้อมูลสถิติสินค้า (ที่มีข้อมูล):"},
    {"CURRENCY_FORMAT_PLACEHOLDER", "รูปแบบสกุลเงิน (ที่มีข้อมูล):"},
    {"TAX_RATE_PLACEHOLDER", "อัตราภาษี (ที่มีข้อมูล):"},
    {"LANGUAGE_SELECTED", "เลือกภาษา: "},
    {"SELECT_LANGUAGE", "เลือกภาษา (EN/KH/TH/ZH): "},
    {"INVALID_LANGUAGE_USING_ENGLISH", "รหัสภาษาไม่ถูกต้อง ใช้ภาษาอังกฤษแทน."},
    {"ENTER_PRODUCT_ID", "ป้อนรหัสสินค้า: "},
    {"ENTER_PRODUCT_NAME", "ป้อนชื่อสินค้า: "},
    {"ENTER_PRODUCT_PRICE", "ป้อนราคาสินค้า: "},
    {"ENTER_PRODUCT_ID_FOR_TRANSACTION", "ป้อนรหัสสินค้าสำหรับการทำรายการ: "},
    {"ENTER_QUANTITY_FOR_TRANSACTION", "ป้อนปริมาณสำหรับการทำรายการ: "},
    {"ENTER_PRODUCT_ID_TO_DELETE", "ป้อนรหัสสินค้าที่จะลบ: "},
    {"ENTER_PRODUCT_ID_TO_UPDATE", "ป้อนรหัสสินค้าที่จะอัปเดต: "},
    {"ENTER_NEW_NAME_FOR_PRODUCT", "ป้อนชื่อใหม่สำหรับสินค้า: "},
    {"ENTER_NEW_PRICE_FOR_PRODUCT", "ป้อนราคาใหม่สำหรับสินค้า: "},
    {"ENTER_KEYWORD_FOR_SEARCH", "ป้อนคำสำหรับการค้นหา: "},
    {"OPTIONS", "\nตัวเลือก:"},
    {"OPTIONS", "\nตัวเลือก:"},
    {"OPTIONS", "\nตัวเลือก:"},
    {"OPTIONS", "\nตัวเลือก:"},
    {"OPTIONS", "\nตัวเลือก:"}
    // ... Add more translations as needed
};

// Chinese translations
languageTranslations["ZH"] = {
    {"POS_SYSTEM_STARTED_ON", "POS系统开始于: "},
    // ... Add Chinese translations similar to other languages
    {"OPTIONS", "\n选项:"},
    {"ENTER_YOUR_CHOICE", "输入您的选择: "},
    {"INVALID_CHOICE", "无效选择。请重试."},
    {"EXITING_POS_SYSTEM", "退出POS系统."},
    {"FILE_NOT_FOUND_STARTING_EMPTY_SYSTEM", "找不到文件。将以空系统开始."},
    {"PRODUCT_DELETED_SUCCESSFULLY", "产品删除成功."},
    {"PRODUCT_UPDATED_SUCCESSFULLY", "产品更新成功."},
    {"TRANSACTION_PROCESSED_SUCCESSFULLY", "交易成功处理."},
    {"PRODUCT_NOT_FOUND", "找不到产品."},
    {"TOTAL_AMOUNT", "总金额"},
    {"TOTAL_WITH_DISCOUNT", "总折扣金额"},
    {"RECEIPT_HEADER", "\n收据:"},
    {"RECEIPT_FOOTER_TOTAL_AMOUNT", "\n总金额: $"},
    {"RECEIPT_FOOTER_TOTAL_WITH_DISCOUNT", "总折扣金额: $"},
    {"SEARCH_RESULTS_HEADER", "\n搜索结果:"},
    {"SEARCH_RESULTS_FOOTER", "搜索完成."},
    {"TRANSACTION_HISTORY_HEADER", "\n交易历史记录:"},
    {"TRANSACTION_HISTORY_FOOTER", "交易历史记录结束."},
    {"SALES_REPORT_HEADER", "\n销售报告:"},
    {"SALES_REPORT_TOTAL_SALES", "总销售额: $"},
    {"SALES_REPORT_FOOTER", "销售报告结束."},
    {"RECEIPT_HEADER_FILE", "收据 (打印到 'receipt.txt'):"},
    {"RECEIPT_FOOTER_FILE", "\n收据结束 (打印到 'receipt.txt')."},
    {"RECEIPT_PRINTED_TO_FILE", "已打印到 'receipt.txt'."},
    {"SEARCH_RESULTS_PLACEHOLDER", "搜索结果 (有数据):"},
    {"PRODUCT_STATISTICS_PLACEHOLDER", "产品统计信息 (有数据):"},
    {"CURRENCY_FORMAT_PLACEHOLDER", "货币格式 (有数据):"},
    {"TAX_RATE_PLACEHOLDER", "税率 (有数据):"},
    {"LANGUAGE_SELECTED", "选择的语言: "},
    {"SELECT_LANGUAGE", "选择语言 (EN/KH/TH/ZH): "},
    {"INVALID_LANGUAGE_USING_ENGLISH", "无效的语言代码。将使用英语."},
    {"ENTER_PRODUCT_ID", "输入产品ID: "},
    {"ENTER_PRODUCT_NAME", "输入产品名称: "},
    {"ENTER_PRODUCT_PRICE", "输入产品价格: "},
    {"ENTER_PRODUCT_ID_FOR_TRANSACTION", "输入交易的产品ID: "},
    {"ENTER_QUANTITY_FOR_TRANSACTION", "输入交易的数量: "},
    {"ENTER_PRODUCT_ID_TO_DELETE", "输入要删除的产品ID: "},
    {"ENTER_PRODUCT_ID_TO_UPDATE", "输入要更新的产品ID: "},
    {"ENTER_NEW_NAME_FOR_PRODUCT", "输入产品的新名称: "},
    {"ENTER_NEW_PRICE_FOR_PRODUCT", "输入产品的新价格: "},
    {"ENTER_KEYWORD_FOR_SEARCH", "输入搜索的关键字: "},
    {"OPTIONS", "\n选项:"},
    {"OPTIONS", "\n选项:"},
    {"OPTIONS", "\n选项:"},
    {"OPTIONS", "\n选项:"},
    {"OPTIONS", "\n选项:"}
    // ... Add more translations as needed
};
    
}
};
// Add more translations as needed for Khmer, Thai, and Chinese

int main() {
    PosSystem pos;
    pos.run();

    return 0;
}



