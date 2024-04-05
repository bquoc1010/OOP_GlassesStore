#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "constants.h"
#include "utils.h"

using namespace std;

class Product {
   friend class Calculator;
   private:
    string productId, STT;
    string name;
    float price;
    string createDate;
    bool deleted;
    int amount;
    static int cnt;


   public:
    Product() {
        productId , STT, name = "";
        price = 0.0;
        amount = 0;
        this->createDate = getCurrentDate();
    }


    Product(string ma,string STT, string ten, float gia, int sl) {
        productId = ma;
        STT = STT;
        name = ten;
        price = gia;
        amount = sl;
        
    }

    Product(string productId, string name, float price, int amount, string createDate, bool deleted) {
        this->productId = productId;
        this->name = name;
        this->price = price;
        this->amount = amount;
        this->createDate = createDate;
        this->deleted = deleted;
    }

    void xuatfile(ofstream& file);
    
    string getProductId();    
    
    string getName();
    
    float getPrice();
    
    int getAmount();

    void setProductId(const string& productId); 

    void WriteProducts();
    
    void ReadData();  

    int getCount();

    string getCreateDate();

    bool getDeleted();

    void setDeleted(bool deleted);

    bool isEmpty();

    void show();

    static Product readLine(string line);

    static Product findByProductId(string targetId);

    static void save(Product& product);

    static void update(string productId);

    static void remove(string productId);

    static vector<Product> getAllProducts();

    static void showTableHeader();

    static void showAllProducts();


    friend istream& operator >>(istream& is, Product& sp);

    friend ostream& operator <<(ostream& os, Product& sp);
};

void Product::xuatfile(ofstream& file) {
        file << productId << "\n";
        file << name << "\n";
        cin.ignore(1, '\n');     // Xóa bộ đệm đầu vào của cin, bỏ qua ký tự newline
        file << price << "\n";
        file << amount << "\n";
}

string Product::getProductId() {
        return productId;
}

string Product::getName() {
        return name;
}

float Product::getPrice() {
        return price;
}

int Product::getAmount() {
        return amount;
}

void Product::setProductId(const string& productId) {
        this->productId = productId;
}

void Product::WriteProducts() {
    cnt++;
    STT = string(3 - to_string(cnt).length(), '0') + to_string(cnt);
    cout << "Nhap ma hang: "; 
    cin >> productId;
    cout << "Nhap ten hang: ";
    cin.ignore();
    getline(cin,name);
    cout << "Nhap gia tien: ";
    cin >> price;
    cout << "Nhap so luong: ";
    cin>> amount;
}

void Product::ReadData() {
    cout<< setw(5)<<"STT " << setw(20) << "Ma hang: " << setw(20) << "Ten hang: " <<setw(25) << "Gia tien: " << setw(25)   << "So luong: "  << endl;

    cout << setw(5) << STT << setw(20) << productId << setw(20) << name  << setw(25) << price << setw(25) << amount << endl;
}

int Product::getCount(){
    return cnt;
}

string Product::getCreateDate() {
    return this->createDate;
}

bool Product::getDeleted() {
    return this->deleted;
}

void Product::setDeleted(bool deleted) {
    this->deleted = deleted;
}

bool Product::isEmpty() {
    return empty(this->productId);
}

void Product::show() {
    if (this->isEmpty()) {
        cout << "Not found product!";
        return ;
    } 
    
    string productIdStr = this->productId;
    productIdStr.resize(PRODUCT_ID_COL_SIZE, ' ');
    string nameStr = this->name;
    nameStr.resize(PRODUCT_NAME_COL_SIZE, ' ');
    string priceStr = to_string(this->price);
    priceStr.resize(PRODUCT_PRICE_COL_SIZE, ' ');
    string amountStr = to_string(this->amount);
    amountStr.resize(PRODUCT_AMOUNT_COL_SIZE, ' ');
    string createDateStr = this->createDate;
    createDateStr.resize(PRODUCT_DATE_COL_SIZE, ' ');
    string deletedStr = to_string(this->deleted);
    deletedStr.resize(PRODUCT_DELETED_COL_SIZE, ' ');

    cout << productIdStr << nameStr << priceStr << amountStr << createDateStr << deletedStr << '\n';
}

istream& operator >>(istream& is, Product& sp) {
    sp.WriteProducts();
    return is;
}

ostream& operator <<(ostream& os, Product& sp) {
    sp.ReadData(); 
    return os;
}
int Product::cnt = 0;

Product Product::readLine(string line) {
        int start = 0, end = PRODUCT_ID_COL_SIZE;
        string productId = line.substr(start, end);
        productId = trim(productId);
        start = end;
        end += PRODUCT_NAME_COL_SIZE;
        string name = line.substr(start, end);
        name = trim(name);
        start = end;
        end += PRODUCT_PRICE_COL_SIZE;
        string priceStr = line.substr(start, end);
        float price = stof(priceStr);
        start =end;
        end += PRODUCT_AMOUNT_COL_SIZE;
        string amountStr = line.substr(start, end);
        int amount = stoi(amountStr);
        start = end;
        end += PRODUCT_DATE_COL_SIZE;
        string createDate = line.substr(start, end);
        createDate = trim(createDate);
        start =end;
        end += PRODUCT_DELETED_COL_SIZE;
        string deletedStr = line.substr(start, end);
        deletedStr = trim(deletedStr);
        bool deleted = stob(deletedStr);

        if (!deleted) {
            Product product(productId, name, price, amount, createDate, deleted);
            return product;
        }
        return Product();
}

Product Product::findByProductId(string targetId) {
    ifstream file(PRODUCT_FILE_NAME);
    if (!file.is_open()) {
        cerr << "Error opening file for reading: " << PRODUCT_FILE_NAME << endl;
        return Product();
    }
    string line;
    // Inorge the first line
    getline(file, line);
    while (getline(file, line)) {
        Product product = readLine(line);
        if (product.getProductId() == targetId) {
            file.close();
            return product;
        }
    }

    file.close();
    return Product();
}

void Product::save(Product &product) {
    ofstream file(PRODUCT_FILE_NAME, ios::app); // Opend in append mode
    if (!file.is_open()) {
        cerr << "Error opening file for writting: " << PRODUCT_FILE_NAME << endl;
        return;
    }

    // Check if file is empty
    if (isFileEmpty(PRODUCT_FILE_NAME)) {
        string productIdCol = "Product_ID";
        productIdCol.resize(PRODUCT_ID_COL_SIZE, ' ');
        string nameCol = "Name";
        nameCol.resize(PRODUCT_NAME_COL_SIZE, ' ');
        string priceCol = "Price";
        priceCol.resize(PRODUCT_PRICE_COL_SIZE, ' ');
        string amountCol = "Amount";
        amountCol.resize(PRODUCT_AMOUNT_COL_SIZE, ' ');
        string createDateCol = "Create Date";
        createDateCol.resize(PRODUCT_DATE_COL_SIZE, ' ');
        string deletedCol = "Deleted";
        deletedCol.resize(PRODUCT_DELETED_COL_SIZE, ' ');

        file << productIdCol << nameCol << priceCol << amountCol << createDateCol << deletedCol << '\n';
    }

    
    string productIdStr = product.getProductId();
    productIdStr.resize(PRODUCT_ID_COL_SIZE, ' ');
    string nameStr = product.getName();
    nameStr.resize(PRODUCT_NAME_COL_SIZE, ' ');
    string priceStr = to_string(product.getPrice());
    priceStr.resize(PRODUCT_PRICE_COL_SIZE, ' ');
    string amountStr = to_string(product.getAmount());
    amountStr.resize(PRODUCT_AMOUNT_COL_SIZE, ' ');
    string createDateStr = product.getCreateDate();
    createDateStr.resize(PRODUCT_DATE_COL_SIZE, ' ');
    string deletedStr = to_string(product.getDeleted());
    deletedStr.resize(PRODUCT_DELETED_COL_SIZE, ' ');

    file << productIdStr << nameStr << priceStr << amountStr << createDateStr << deletedStr << '\n';

    file.close();
}

void Product::update(string productId) {
    // Product product = 
}

void Product::remove(string productId) {
    // Product product = findByProductId(productId);
    // if (product.isEmpty()) {
    //     cout << "Not found product" << endl;
    //     return;
    // }

    vector<Product> products = getAllProducts();
    remove(PRODUCT_FILE_NAME);
}

vector<Product> Product::getAllProducts() {
    vector<Product> products;
    ifstream file(PRODUCT_FILE_NAME);
    if (!file.is_open()) {
        cerr << "Error opening file for reading: " << PRODUCT_FILE_NAME << endl;
        return products;
    }

    string line;
    // Skip the header line
    getline(file, line);
    while (getline(file, line)) {
        Product product = readLine(line);
        if (!product.isEmpty()) products.push_back(product);
        
    }

    file.close();
    return products;
}

void Product::showTableHeader() {
    string productIdCol = "Product_ID";
    productIdCol.resize(PRODUCT_ID_COL_SIZE, ' ');
    string nameCol = "Name";
    nameCol.resize(PRODUCT_NAME_COL_SIZE, ' ');
    string priceCol = "Price";
    priceCol.resize(PRODUCT_PRICE_COL_SIZE, ' ');
    string amountCol = "Amount";
    amountCol.resize(PRODUCT_AMOUNT_COL_SIZE, ' ');
    string createDateCol = "Create Date";
    createDateCol.resize(PRODUCT_DATE_COL_SIZE, ' ');
    string deletedCol = "Deleted";
    deletedCol.resize(PRODUCT_DELETED_COL_SIZE, ' ');

    cout << productIdCol << nameCol << priceCol << amountCol << createDateCol << deletedCol << '\n';
}

void Product::showAllProducts() {
    vector<Product> products = getAllProducts();
    Product::showTableHeader();

    for (int i = 0; i < products.size(); i ++) {
        products[i].show();
    }
    
}