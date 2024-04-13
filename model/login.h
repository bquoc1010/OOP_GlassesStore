#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>

#include "Order.h"
using namespace std;

void setStdinEcho(bool enable) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); //lay handle cua standard input (ban phim)
    DWORD mode; //luu che do hien tai cua console
    GetConsoleMode(hStdin, &mode); // lay che do hien tai cua console

    if (!enable) mode &= ~ENABLE_ECHO_INPUT; // neu enable = false, disable echo vao che do hien tai
    else mode |= ENABLE_ECHO_INPUT; // neu enable = true, enable echo vao che do hien tai

    SetConsoleMode(hStdin, mode); //thiet lap lai che do cho console
}
#endif

string getPassword() {
    string password; //chuoi luu password
    char ch; // bien tam dung de luu tung ki tu

    setStdinEcho(false); // disable echo ra khoi che do hien tai

    cout << "Nhap mat khau: ";

#ifdef _WIN32
    // doc tung ki tu ma khong hien thi
    while ((ch = _getch()) != '\r') { // neu khong phai la ki tu enter
        if (ch == '\b') { // neu la ki tu backspace, xoa ki tu truoc do o trong chuoi password
            if (password.length() != 0) {
                cout << "\b \b"; // di chuyen con tro ve ben trai, in ra space de xoa roi di chuyen con tro ve ben phai
                password.resize(password.size() - 1); // giam chuoi password di 1 ki tu
            }
        } else if (ch == '\r') {
            // dieu kien de thoat vong lap
        } else {
            password += ch; // them ki tu vao chuoi password
            cout << '*'; // in ra dau sao moi khi nhan duoc 1 ki tu moi
        }
    }
    #endif
    setStdinEcho(true); // enable lai echo

    cout << endl;
    return password;
}

class Employee {
    private:
        string username;
        string password;
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
        
        // Sử dụng getPassword để nhập mật khẩu mà không hiển thị trên màn hình
        password = getPassword();

        if (emp.login(username, password)) {
            cout << "Dang nhap thanh cong!" << endl;
            this->role = 1;  // Update role người dùng
        } else {
            cout << "Dang nhap that bai!" << endl;
            this->role = 0; // Reset role nếu đăng nhập thất bại
        }
    } else {
        this->role = 2; // Khách hàng
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
        // cout << "6. Print Receipt\n";
        cout << "0. Thoat" << endl;
        cout << "================================================================================================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                if (role == 1) {
                    Product::manageProductMenu();
                    cout << "Danh sach san pham." << endl;
                } else {
                    cout << "Ban khong co quyen truy cap vao chuc nang nay!" << endl;
                }
                break;
            }
            case 2: {
                Product::showAllProducts();
                break;
            }
            case 3: {
                Product::searchProduct();
                break;
            }
            case 4: {
                cin >> order;
                Order::save(order);
                break;
            }
            case 5: {
                Order::manageOrderMenu(order);
                break;
            }
            // case 6: {
            //     string orderId;
            //     getline(cin, orderId);
            //     if (order.isEmpty()) {
            //         cout << "You don't have any order!\n";
            //     } else {
            //         Customer customer = order.getCustomerInfo();
            //         vector<Item> items = order.getItems();
            //         cout << "Customer's name" << customer.getName() << endl;
            //         cout << "Product name" << '\t' << "Amount" << endl;
            //         for (int i = 0; i < items.size(); i ++) {
            //             Product product = Product::findByProductId(items[i].getProductId());
            //             cout << product.getName() << '\t' << items[i].getAmount() << endl;
            //         }
            //     }
            //     break;
            // }
            case 0: {
                cout << "Cam on ban da mua hang!" << endl;
                break;
            }
            default: {
                cout << "Lua chon khong hop le. Vui long chon lai!" << endl;
                break;
            }
        }
    } while (choice != 0);
}