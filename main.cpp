#include <bits/stdc++.h>
#include "model/Order.h"
using namespace std;

int main() {
    Order order;
    int choice;
    Product sp;
    while (1) {
        cout << "==============================================  CUA HANG KINH THUOC  ===========================================" << endl;
        cout << "1. Product " << endl;
        cout << "2. Menu \n";
        cout << "3. Add to Cart\n";
        cout << "4. View Cart\n";
        cout << "5. Print Receipt\n";
        cout << "0. Thoat" << endl;
        cout << "================================================================================================================" << endl;
        cout << "Enter your choice: ";
        
        cin >> choice;
        switch (choice) {
            case 1:
                Product::manageProductMenu();
                break;
            case 2:
                Product::showAllProducts();
                break;
            case 3:
                cin >> order;
                Order::save(order);
                break;
            case 4:
                Order::manageOrderMenu(order);
                break;
            case 5:
                // cin >> order;
                // Order::save(order);
                break;
            case 0:
                cout << "Cam on ban da mua hang!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai!" << endl;
                break;
        }
    }
    return 0;
}