#include <bits/stdc++.h>
#include "Product.h"

using namespace std;

class Calculator {
   private:
    vector<Product> Cart;       // Danh sách sản phẩm trong giỏ hàng
    vector<Product> List;  // Danh sách sản phẩm của cửa hàng
   public:
    string Id;

    //Nhập dữ liệu hàng hóa kiểu bình thường
    void writeData();

    // Thêm món hàng vào giỏ hàng
    void addToCart(string Id);
    // Xóa món hàng khỏi giỏ hàng
    void remove(string Id);
    // Tính tổng số lượng hàng và tổng tiền hàng trong giỏ hàng
    void AmountAndPrice();
    // Chèn thông tin món hàng vào danh sách của cửa hàng
  
    void insertToList();
    void inventory();
    // Ghi danh sách hàng tồn vào file danhsach.xlsx
    void writeToFile();
    void showMenu();
      
};
void Calculator::writeData() {
        Product sp;
        cin >> sp;
        cin.ignore();  // Loại bỏ ký tự newline trong bộ đệm nhập chuẩn
        List.push_back(sp);
}

// Thêm món hàng vào giỏ hàng
void Calculator::addToCart(string productId) {
    bool timThay = false;
    for (int i = 0; i < List.size(); i++) {
        if (List[i].productId == productId) {  // truy cập trực tiếp vào san pham dữ liệu Id
            if (List[i].amount > 0) {   // truy cập trực tiếp vào san pham dữ liệu amount
                Cart.push_back(List[i]);
                List[i].amount--;  // truy cập trực tiếp vào san pham dữ liệu amount và giảm so luong trị đi 1
                timThay = true;
                cout << "Them mon hang vao gio hang thanh cong!" << endl;
            } else {
                cout << "Khong co hang trong kho!" << endl;
            }
            break;
        }
    }
    if (!timThay) {
        cout << "Ma hang khong ton tai!" << endl;
    }
}
// Xóa món hàng khỏi giỏ hàng
void Calculator::remove(string productId){
    int ok = 0;
    for(int i=0;i<Cart.size();i++){
        if(Cart[i].productId == productId){
            if(Cart[i].amount > 0){
                Cart.pop_back();
                Cart[i].amount--;
                List[i].amount++;
                ok = 1;
                cout << "Xoa mon hang trong gio hang thanh cong!" << endl;
            }else{
                    cout << "Xoa mon hang trong gio hang khong thanh cong!" << endl;
            }
        } 

    }
    if(!ok) cout<<"Ma hang khong ton tai! "<<endl;
    
}
// Tính tổng số lượng hàng và tổng tiền hàng trong giỏ hàng
void Calculator::AmountAndPrice() {
    int SumAmounts = 0;
    float MoneySum = 0;
    for (int i = 0; i < Cart.size(); i++) {
        SumAmounts += Cart[i].amount;
        MoneySum += Cart[i].amount * Cart[i].price;
    }
    cout << "Tong so luong hang trong gio hang: " << SumAmounts << endl;
    cout << "Tong tien hang trong gio hang: " << MoneySum << endl;
}

// Chèn thông tin món hàng vào danh sách của cửa hàng

void Calculator::insertToList() {
    Product sp;
    int index;  // Vị trí cần chèn
        do {
            cout << "Nhap vi tri can chen (0 - " << List.size() - 1 << "): ";
            cin >> index;
                if (index < 0 || index > List.size() - 1) {
                cout << "Vi tri khong hop le. Vui long nhap lai." << endl;
    }
        } while (index < 0 || index > List.size() - 1);

        writeData();  // Nhập thông tin của món hàng và gán giá trị cho đối tượng sp
        
    }



void Calculator::inventory() {
    
        for (int i = 0; i < List.size(); i++) {
            List[i].ReadData();
            cout << endl;
        }
        cin.ignore();  
}

// Ghi danh sách hàng tồn vào file danhsach.txt
void Calculator::writeToFile() {
    ofstream out;
    out.open("danhsach.txt");
    if (out.is_open()) {
        for (int i = 0; i < List.size(); i++) {
                List[i].xuatfile(out);
        }
        
        cout << "Ghi danh sach hang ton vao file danhsach.xlsx thanh cong!" << endl;
    } else {
        cout << "Khong the mo file danhsach.txt de ghi!" << endl;
    }
    out.close();
}

void Calculator::showMenu() {
    int choice;
    Product sp;
    while (1) {
        cout << "==============  CUA HANG KINH THUOC  ==============" << endl;
        cout << "1. Nhap du lieu hang hoa " << endl;
        cout << "2. Them mon hang vao gio hang" << endl;
        cout << "3. Tinh tong so luong hang va tong tien hang trong gio hang" << endl;
        cout << "4. Chen thong tin mon hang vao danh sach cua cua hang" << endl;
        cout << "5. Xem danh sach hang con ton trong kho" << endl;
        cout << "6. Ghi danh sach hang ton vao file danhsach.xlsx" << endl;
        cout << "7. Xoa san pham khoi gio hang" << endl;
        cout << "0. Thoat" << endl;
        cout << "=================================================================" << endl;
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;
        switch (choice) {
            case 1:
                writeData();
                break;
            case 2: {
                string Id;
                cout << "Nhap ma hang: ";
                cin >> Id;
                addToCart(Id);
            }

            break;
            case 3:
                AmountAndPrice();
                break;
            case 4:
                insertToList();
                break;
            case 5:
                inventory();
                break;
            case 6:
                writeToFile();
                break;
            case 7:{
                string id;
                cout << "Nhap ma hang: ";
                cin >> id;
                remove(id);
            }
                break;
            case 0:
                cout << "Cam on ban da mua hang!" << endl;

            default:
                cout << "Lua chon khong hop le. Vui long chon lai!" << endl;
                break;
        }
    }
}