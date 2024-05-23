#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>  // Added for rand()
#include <map>

using namespace std;

// Console color escape codes
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"

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
    map<string, map<string, string>> languageTranslations;

public:
    PosSystem() {
        initializeLanguageTranslations();
        readDataFromFile();
        time_t currentTime = time(nullptr);
        tm* localTime = localtime(&currentTime);
        cout << getTranslation("POS_SYSTEM_STARTED_ON") << put_time(localTime, "%c") << endl;
    }

    void addProduct(int id, const string& name, double price) {
        Product product = {id, name, price};
        products.push_back(product);
        writeDataToFile();
        cout << GREEN << getTranslation("PRODUCT_ADDED_SUCCESSFULLY") << RESET << endl;
    }

  void displayProducts() const {
    cout << "Product List:" << endl;
    cout << "+-----+----------------------+-----------+\n";
    cout << "| " << "ID" << "  | " << "Name" << "                 | " << "Price" << "      |\n";
    cout << "+-----+----------------------+-----------+\n";
    for (const auto& product : products) {
        cout << "| " << setw(3) << product.id << " | " << setw(20) << product.name << " | $" << setw(7) << fixed << setprecision(2) << product.price << "   |\n";
    }
    cout << "+-----+----------------------+-----------+\n";
}


    void processTransaction(int productId, int quantity) {
        Transaction transaction = {productId, quantity, time(nullptr)};
        transactions.push_back(transaction);
        writeDataToFile();
        cout << GREEN << "Transaction processed successfully." << RESET << endl;
    }

    void generateReceipt() const {
        double totalAmount = 0.0;
        double totalWithDiscount = 0.0;

        cout << GREEN << "\nReceipt:" << RESET << endl;
        cout << "+----------------------+----------+------------+\n";
        cout << "| " << BLUE << "Product" << RESET << "                 | " << RED << "Quantity" << RESET << " | " << RED << "Price" << RESET << "      | " << YELLOW << "Total" << RESET << "      |\n";
        cout << "+----------------------+----------+------------+\n";

        for (const auto& transaction : transactions) {
            const Product& product = getProductById(transaction.productId);
            double subtotal = transaction.quantity * product.price;
            totalAmount += subtotal;

            cout << "| " << setw(20) << product.name << " | " << setw(8) << transaction.quantity << " | " << setw(10) << product.price << " | " << setw(12) << subtotal << " |\n";
        }

        totalWithDiscount = calculateTotalWithDiscount(totalAmount);

        cout << "+----------------------+----------+------------+\n";
        cout << GREEN << "\nTotal Amount: $" << RESET << totalAmount << "\n";
        cout << GREEN << "Total Amount with Discount: $" << RESET << totalWithDiscount << "\n";
    }

    void deleteProduct(int productId) {
        auto it = remove_if(products.begin(), products.end(),
                                 [productId](const Product& p) { return p.id == productId; });
        if (it != products.end()) {
            products.erase(it, products.end());
            writeDataToFile();
            cout << GREEN << "Product deleted successfully." << RESET << endl;
        } else {
            cout << GREEN << "Product not found." << RESET << endl;
        }
    }

    void updateProduct(int productId, const string& newName, double newPrice) {
        for (auto& product : products) {
            if (product.id == productId) {
                product.name = newName;
                product.price = newPrice;
                writeDataToFile();
                cout << GREEN << "Product updated successfully." << RESET << endl;
                return;
            }
        }
        cout << GREEN << "Product not found." << RESET << endl;
    }

    void readDataFromFile() {
        ifstream inputFile(dataFilePath);
        if (!inputFile.is_open()) {
            cout << GREEN << "File not found. Starting with an empty system." << RESET << endl;
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
            displayOptions();

            cout << YELLOW << getTranslation("ENTER_YOUR_CHOICE") << RESET;
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
                    cout << GREEN << getTranslation("EXITING_POS_SYSTEM") << RESET << endl;
                    break;
                case 'L':
                case 'l':
                    selectLanguage();
                    break;
                default:
                    cout << GREEN << getTranslation("INVALID_CHOICE") << RESET << endl;
            }

        } while (choice != '7');
    }

const Product& getProductById(int productId) const;
    double calculateTotalWithDiscount(double totalAmount) const;
private:
    void addProductFromInput() {
        int id;
        string name;
        double price;

        cout << YELLOW << getTranslation("ENTER_PRODUCT_ID") << RESET;
        cin >> id;

        cout << YELLOW << getTranslation("ENTER_PRODUCT_NAME") << RESET;
        cin.ignore();
        getline(cin, name);

        cout << YELLOW << getTranslation("ENTER_PRODUCT_PRICE") << RESET;
        cin >> price;

        addProduct(id, name, price);
    }

    void processTransactionFromInput() {
        int productId;
        int quantity;

        cout << YELLOW << getTranslation("ENTER_PRODUCT_ID_TRANSACTION") << RESET;
        cin >> productId;

        cout << YELLOW << getTranslation("ENTER_QUANTITY_TRANSACTION") << RESET;
        cin >> quantity;

        processTransaction(productId, quantity);
    }

    void deleteProductFromInput() {
        int productId;

        cout << YELLOW << getTranslation("ENTER_PRODUCT_ID_DELETE") << RESET;
        cin >> productId;

        deleteProduct(productId);
    }

    void updateProductFromInput() {
        int productId;
        string newName;
        double newPrice;

        cout << YELLOW << getTranslation("ENTER_PRODUCT_ID_UPDATE") << RESET;
        cin >> productId;

        cout << YELLOW << getTranslation("ENTER_NEW_NAME") << RESET;
        cin.ignore();
        getline(cin, newName);

        cout << YELLOW << getTranslation("ENTER_NEW_PRICE") << RESET;
        cin >> newPrice;

        updateProduct(productId, newName, newPrice);
    }

    void selectLanguage() {
        string languageCode;
        cout << GREEN << "Available Languages:" << RESET << endl;
        cout << "1. EN - English\n2. KH - Khmer\n3. TH - Thai\n4. ZH - Chinese\n";
        cout << YELLOW << "Enter language code (e.g., EN, KH, TH, ZH): " << RESET;
        cin >> languageCode;

        auto it = languageTranslations.find(languageCode);
        if (it != languageTranslations.end()) {
            cout << GREEN << "Selected Language: " << languageCode << RESET << endl;
            cout << getTranslation("LANGUAGE_SELECTED") << languageCode << endl;
        } else {
            cout << GREEN << "Invalid language code. Defaulting to English." << RESET << endl;
        }
    }

    string getTranslation(const string& key) const {
        string languageCode = "EN";  // Default to English
        auto it = languageTranslations.find(languageCode);
        if (it != languageTranslations.end()) {
            auto translations = it->second;
            auto translationIt = translations.find(key);
            if (translationIt != translations.end()) {
                return translationIt->second;
            }
        }
        return "Translation not found";
    }

    void displayOptions() const {
        cout << GREEN << getTranslation("OPTIONS") << RESET << endl;
        cout << BLUE << "1. " << getTranslation("ADD_PRODUCT") << RESET << endl;
        cout << BLUE << "2. " << getTranslation("DISPLAY_PRODUCTS") << RESET << endl;
        cout << BLUE << "3. " << getTranslation("PROCESS_TRANSACTION") << RESET << endl;
        cout << BLUE << "4. " << getTranslation("GENERATE_RECEIPT") << RESET << endl;
        cout << BLUE << "5. " << getTranslation("DELETE_PRODUCT") << RESET << endl;
        cout << BLUE << "6. " << getTranslation("UPDATE_PRODUCT") << RESET << endl;
        cout << BLUE << "7. " << getTranslation("EXIT") << RESET << endl;
        cout << YELLOW << "L. " << getTranslation("SELECT_LANGUAGE") << RESET << endl;
    }

    void initializeLanguageTranslations() {
       map<string, string> enTranslations{
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
            {"LANGUAGE_SELECTED", "- Selected Language: EN"},
            {"AVAILABLE_LANGUAGES", "Available Languages:"},
            {"ENTER_LANGUAGE_CODE", "Enter language code (e.g., EN, KH, TH, ZH): "},
            {"SELECTED_LANGUAGE", "Selected Language: "},
            {"INVALID_LANGUAGE_CODE", "Invalid language code. Defaulting to English."},
           
        };
         map<string, string> khTranslations{
            {"POS_SYSTEM_STARTED_ON", "ប្រព័ន្ធ POS ចាប់ផ្តើមនៅលើ: "},
            {"PRODUCT_ADDED_SUCCESSFULLY", "បាន​បន្ថែមផលិតផល​ដែល​មានជោគជ័យ។"},
            {"OPTIONS", "\nជម្រើស:"},
            {"ENTER_YOUR_CHOICE", "បញ្ចូលការជ្រើសរើស: "},
            {"INVALID_CHOICE", "ការជ្រើើសរើសមិនត្រឹមត្រូវ។ សូមព្យាយាមម្តងទៀត។"},
            {"EXITING_POS_SYSTEM", "កំពុងចេញពីប្រព័ន្ធ POS។"},
            {"FILE_NOT_FOUND_STARTING_EMPTY_SYSTEM", "រកមិនឃើញឯកសារ។ ចាប់ផ្តើមជាប្រព័ន្ធទទេ។"},
            {"PRODUCT_DELETED_SUCCESSFULLY", "ផលិតផលត្រូវបានលុបចោលដោយជោគជ័យ។"},
            {"PRODUCT_UPDATED_SUCCESSFULLY", "ផលិតផលត្រូវបានធ្វើបច្ចុប្បន្នភាពដោយជោគជ័យ។"},
            {"TRANSACTION_PROCESSED_SUCCESSFULLY", "បានដោះស្រាយប្រតិបត្តិការបានជោគជ័យ។"},
            {"PRODUCT_NOT_FOUND", "រកមិនឃើញផលិតផល។"},
            {"TOTAL_AMOUNT", "សរុបចំណាយ"},
             {"TOTAL_WITH_DISCOUNT", "សរុបចំណាយដោយការបញ្ចុះតម្លៃ"},
            {"RECEIPT_HEADER", "\nបង្កាន់ដៃ:"},
            {"LANGUAGE_SELECTED", "- ភាសាដែលបានជ្រើស: KH"},
            {"AVAILABLE_LANGUAGES", "ភាសាដែលមាន:"},
            {"ENTER_LANGUAGE_CODE", "បញ្ចូលលេខកូដភាសា (ឧ: EN, KH, TH, ZH): "},
            {"SELECTED_LANGUAGE", "ភាសាដែលបានជ្រើស: "},
            {"INVALID_LANGUAGE_CODE", "លេខកូដភាសា​មិនត្រឹមត្រូវ។ ជ្រើសរើសភាសាលោកអ្នកទៅជាភាសាអង់គ្លេស។"},
            // Add more Khmer translations as needed
        };

        // Thai translations
        map<string, string> thTranslations{
            {"POS_SYSTEM_STARTED_ON", "ระบบ POS เริ่มทำงานเมื่อ: "},
            {"PRODUCT_ADDED_SUCCESSFULLY", "เพิ่มสินค้าเรียบร้อยแล้ว"},
            {"OPTIONS", "\nตัวเลือก:"},
            {"ENTER_YOUR_CHOICE", "กรุณาป้อนตัวเลือกของคุณ: "},
            {"INVALID_CHOICE", "ตัวเลือกไม่ถูกต้อง กรุณาลองอีกครั้ง."},
            {"EXITING_POS_SYSTEM", "กำลังออกจากระบบ POS."},
            {"FILE_NOT_FOUND_STARTING_EMPTY_SYSTEM", "ไม่พบไฟล์ กำลังเริ่มต้นด้วยระบบที่ว่างเปล่า."},
            {"PRODUCT_DELETED_SUCCESSFULLY", "ลบสินค้าเรียบร้อยแล้ว."},
            {"PRODUCT_UPDATED_SUCCESSFULLY", "อัปเดตสินค้าเรียบร้อยแล้ว."},
            {"TRANSACTION_PROCESSED_SUCCESSFULLY", "ดำเนินการธุรกรรมเรียบร้อยแล้ว."},
            {"PRODUCT_NOT_FOUND", "ไม่พบสินค้า."},
            {"TOTAL_AMOUNT", "ยอดรวม"},
            {"TOTAL_WITH_DISCOUNT", "ยอดรวมด้วยส่วนลด"},
            {"RECEIPT_HEADER", "\nใบเสร็จ:"},
            {"LANGUAGE_SELECTED", "- เลือกภาษา: TH"},
            {"AVAILABLE_LANGUAGES", "ภาษาที่มี:"},
            {"ENTER_LANGUAGE_CODE", "กรุณาป้อนรหัสภาษา (เช่น EN, KH, TH, ZH): "},
            {"SELECTED_LANGUAGE", "ภาษาที่เลือก: "},
            {"INVALID_LANGUAGE_CODE", "รหัสภาษาไม่ถูกต้อง กำลังเลือกภาษาอังกฤษ."},
            // Add more Thai translations as needed
        };

        // Chinese translations
        map<string, string> zhTranslations{
            {"POS_SYSTEM_STARTED_ON", "POS 系统启动于: "},
            {"PRODUCT_ADDED_SUCCESSFULLY", "成功添加产品。"},
            {"OPTIONS", "\n选项:"},
            {"ENTER_YOUR_CHOICE", "请输入您的选择: "},
            {"INVALID_CHOICE", "无效的选择，请重试。"},
            {"EXITING_POS_SYSTEM", "退出 POS 系统。"},
            {"FILE_NOT_FOUND_STARTING_EMPTY_SYSTEM", "找不到文件。以空系统开始。"},
            {"PRODUCT_DELETED_SUCCESSFULLY", "成功删除产品。"},
            {"PRODUCT_UPDATED_SUCCESSFULLY", "成功更新产品。"},
            {"TRANSACTION_PROCESSED_SUCCESSFULLY", "成功处理交易。"},
            {"PRODUCT_NOT_FOUND", "未找到产品。"},
            {"TOTAL_AMOUNT", "总金额"},
            {"TOTAL_WITH_DISCOUNT", "折扣后总金额"},
            {"RECEIPT_HEADER", "\n收据:"},
            {"LANGUAGE_SELECTED", "- 选择的语言: ZH"},
            {"AVAILABLE_LANGUAGES", "可用语言:"},
            {"ENTER_LANGUAGE_CODE", "请输入语言代码 (例如：EN、KH、TH、ZH): "},
            {"SELECTED_LANGUAGE", "选择的语言: "},
            {"INVALID_LANGUAGE_CODE", "无效的语言代码。默认为中文。"},
            // Add more Chinese translations as needed
        };

        languageTranslations["EN"] = enTranslations;
        languageTranslations["KH"] = khTranslations;
        languageTranslations["TH"] = thTranslations;
        languageTranslations["ZH"] = zhTranslations;
    }

    }

   const Product& PosSystem::getProductById(int productId) const {
    for (const auto& product : products) {
        if (product.id == productId) {
            return product;
        }
    }
    return products[0];
}

double PosSystem::calculateTotalWithDiscount(double totalAmount) const {
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
