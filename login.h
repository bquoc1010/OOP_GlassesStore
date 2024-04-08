#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

#include "model/Order.h" 

using namespace std;

class Employee {
public:
    bool login(const string& username, const string& password) {
        return username == "admin" && password == "1234";
    }
};

class App {
private:
    Employee emp;
    Order order;
    int role; // 1: nhân viên, 2: khách hàng

public:
    App() : role(0) {}
    void run() {
        loginUser();
        displayMenu();
    }
    void loginUser();
    void displayMenu();  
};

void App::loginUser() {
    cout << "Chon la nhan vien (1) hoac khach hang (2): ";
    int choice;
    cin >> choice;
    cin.ignore();  // Xóa bộ đệm nhập

    if (choice == 1) {
        string username, password;
        cout << "Nhap ten dang nhap: ";
        getline(cin, username);
        cout << "Nhap mat khau: ";
        getline(cin, password);

        if (emp.login(username, password)) {
            cout << "Dang nhap thanh cong!" << endl;
            this->role = 1;  //
        } else {
            cout << "Dang nhap that bai!" << endl;
            this->role = 0; // Reset role của class nếu đăng nhập thất bại
        }
    } else {
        this->role = 2; // Cập nhật biến thành viên `role`
    }
}

void App::displayMenu() {
    int choice;

    do {
        cout << "==============================================  CUA HANG KINH THUOC  ===========================================" << endl;
        if (role == 1) {
            // Menu dành cho nhân viên
            cout << "1. Product " << endl;
        }
        // Menu chung cho mọi người
        cout << "2. Menu \n";
        cout << "3. Search \n";
        cout << "4. Add to Cart\n";
        cout << "5. View Cart\n";
        cout << "6. Print Receipt\n";
        cout << "0. Thoat" << endl;
        cout << "================================================================================================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (role == 1) {
                    Product::manageProductMenu();
                    cout << "Danh sach san pham." << endl;
                } else {
                    cout << "Ban khong co quyen truy cap vao chuc nang nay!" << endl;
                }
                break;
            case 2:
                Product::showAllProducts();
                break;
            case 3:
                Product::searchProduct();
                break;
            case 4:
                cin >> order;
                Order::save(order);
                break;
            case 5:
                Order::manageOrderMenu(order);
                break;
            case 6:
                //Print Bill
                break;
            case 0:
                cout << "Cam on ban da mua hang!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai!" << endl;
                break;
        }
    } while (choice != 0);
}