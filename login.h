#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>

#include "model/Order.h"
using namespace std;

void setStdinEcho(bool enable) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if (!enable) mode &= ~ENABLE_ECHO_INPUT;
    else mode |= ENABLE_ECHO_INPUT;

    SetConsoleMode(hStdin, mode);
}
#else
#include <unistd.h>
#include <termios.h>
void setStdinEcho(bool enable) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (!enable) tty.c_lflag &= ~ECHO;
    else tty.c_lflag |= ECHO;

    (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}
#endif

string getPassword() {
    string password;
    char ch;

    // Disable terminal line echo
    setStdinEcho(false);

    // Provide prompt for password input
    cout << "Nhap mat khau: ";

#ifdef _WIN32
    // Get characters without echo
    while ((ch = _getch()) != '\r') { // Use getch on Windows to read character without echo
        if (ch == '\b') { // Backspace should remove the asterisk as well
            if (password.length() != 0) {
                cout << "\b \b"; // Move back, print space, move back again to overwrite the asterisk
                password.resize(password.size() - 1);
            }
        } else if (ch == '\r') {
            // Do nothing if Enter is pressed, it's already the condition to break the loop
        } else {
            password += ch;
            cout << '*'; // Print an asterisk for each entered character that is not backspace
        }
    }
#else
    // Get characters without echo for Unix systems
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch == 127 || ch == 8) { // Backspace (ASCII 127 in Unix, sometimes 8) should remove the asterisk as well
            if (password.length() != 0) {
                cout << "\b \b"; // Move back, print space, move back again to overwrite the asterisk
                password.resize(password.size() - 1);
            }
        } else {
            password += ch;
            cout << '*'; // Print an asterisk for each entered character that is not backspace
        }
    }
    // Terminate the line when done
    cout << endl;
#endif

    // Re-enable terminal line echo
    setStdinEcho(true);

    cout << endl; // Move to the next line after input is done
    return password;
}

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