#include <bits/stdc++.h>

#include "model/Order.h"

using namespace std;

int main() {
    Order order;
    int choice;
    Product sp;
    while (1) {
        cout << "==============================================  CUA HANG KINH THUOC  ===========================================" << endl;
        cout << "1. Add new product " << endl;
        cout << "2. Update product infomation \n";
        cout << "3. Delete product\n";
        cout << "4. Show all products in store\n";
        cout << "5. Create new order\n";
        cout << "6. Pay the bill\n";
        cout << "7. Add new item to order: \n";
        cout << "8. Delete order: \n";

        // cout << "2. Them mon hang vao gio hang" << endl;
        // cout << "3. Tinh tong so luong hang va tong tien hang trong gio hang" << endl;
        // cout << "4. Chen thong tin mon hang vao danh sach cua cua hang" << endl;
        // cout << "5. Xem danh sach hang con ton trong kho" << endl;
        // cout << "6. Ghi danh sach hang ton vao file danhsach.xlsx" << endl;
        // cout << "7. Xoa san pham khoi gio hang" << endl;fdsaf
        cout << "0. Thoat" << endl;
        cout << "=================================================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                Product product;
                cin >> product;
                Product::save(product);
            }
                break;
            case 2: {
                string productId;
                cout << "Enter product's ID to update: " << endl;
                cin >> productId;
                cout << "Enter product information to update\n";
                Product product;
                cin >> product;
                Product::update(productId, product);
            }

            break;
            case 3:{
                string productId;
                cout << "Enter product's ID to delete: " << endl;
                cin.ignore();
                getline(cin, productId);
                Product::remove(productId);
            }
                break;
            case 4:
                Product::showAllProducts();
                break;
            case 5:{
                cin >> order;
                Order::save(order);
            }
                break;
            case 6: {
                if (order.isEmpty()) {
                    cout << "You don't have any orders to pay?" << endl;
                    break;
                }
                if (!order.isEmpty()) {
                    order.pay();
                    Order::save(order);
                    order = Order();
                }
            }
            break;
            case 7: {
                if (order.isEmpty()) {
                    cout << "You don't have any orders" << endl;
                    break;
                }

                while (1) {
                    order.addItem();
                    string flag;

                    cout << "Do you want to add more item? (Y/N)?";
                    cin.ignore();
                    getline(cin, flag);
                    if (flag != "Y") break;
                }
                
            }
                break;
            case 8:{
                if (order.isEmpty()) {
                    cout << "You don't have any order to delete!" << endl;
                    break;
                }
                Order::remove(order.getOrderId());
                cout << "Delete order successfully";
                order = Order();
            }
                break;
            case 0:
                cout << "Cam on ban da mua hang!" << endl;

            default:
                cout << "Lua chon khong hop le. Vui long chon lai!" << endl;
                break;
        }
    }
    return 0;
}