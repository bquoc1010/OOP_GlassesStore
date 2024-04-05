#include <bits/stdc++.h>

using namespace std;
using ll = long long;

class Products {
   friend class Calculator;
   private:
    string Id, STT;
    string name;
    ll price;
    int amounts;
    static int cnt;

   public:
    // Constructor mặc định khi khởi tạo
    Products() {
        Id , STT, name = "";
        price = 0.0;
        amounts = 0;
    }


    // Constructor with parameters
    Products(string ma,string STT, string ten, ll gia, int sl) {
        Id = ma;
        STT = STT;
        name = ten;
        price = gia;
        amounts = sl;
        
    }

    void xuatfile(ofstream& file);
    // Lấy mã hàng
    string getId();    
    // Lấy tên hàng
    string getname();
    // Lấy giá tiền
    ll getprice();
    // Lấy số lượng hàng
    int getamounts();
    void setId(const string& Id); 
   void WriteProducts();
   // Xuất thông tin sản phẩm
   void ReadData();  
    int getCount();
    friend istream& operator >>(istream& is, Products& sp);
    friend ostream& operator <<(ostream& os, Products& sp);
};

void Products::xuatfile(ofstream& file) {
        file << Id << "\n";
        file << name << "\n";
        cin.ignore(1, '\n');     // Xóa bộ đệm đầu vào của cin, bỏ qua ký tự newline
        file << price << "\n";
        file << amounts << "\n";
}
string Products::getId() {
        return Id;
}
string Products::getname() {
        return name;
}
ll Products::getprice() {
        return price;
}
int Products::getamounts() {
        return amounts;
}
void Products::setId(const string& Id) {
        this->Id = Id;
}

void Products::WriteProducts()
{
    cnt++;
    STT = string(3 - to_string(cnt).length(), '0') + to_string(cnt);
    cout << "Nhap ma hang: "; 
    cin >> Id;
    cout << "Nhap ten hang: ";
    cin.ignore();
    getline(cin,name);
    cout << "Nhap gia tien: ";
    cin >> price;
    cout << "Nhap so luong: ";
    cin>> amounts;
}
   


   // Xuất thông tin sản phẩm
void Products::ReadData() {
    cout<< setw(5)<<"STT " << setw(20) << "Ma hang: " << setw(20) << "Ten hang: " <<setw(25) << "Gia tien: " << setw(25)   << "So luong: "  << endl;

    cout << setw(5) << STT << setw(20) << Id << setw(20) << name  << setw(25) << price << setw(25) << amounts << endl;
}
int Products::getCount(){
    return cnt;
}
// Nạp chồng toán tử nhập dữ liệu
 istream& operator >>(istream& is, Products& sp) {
    sp.WriteProducts();
    return is;
}

ostream& operator <<(ostream& os, Products& sp) {
    sp.ReadData(); 
    return os;
}
int Products::cnt = 0;
// Lớp máy tính tiền
class Calculator {
   private:
    vector<Products> Cart;       // Danh sách sản phẩm trong giỏ hàng
    vector<Products> List;  // Danh sách sản phẩm của cửa hàng
   public:
    string Id;

    //Nhập dữ liệu hàng hóa kiểu bình thường
    void WriteData();

    // Thêm món hàng vào giỏ hàng
    void AddToCart(string Id);
    // Xóa món hàng khỏi giỏ hàng
    void Delete(string Id);
    // Tính tổng số lượng hàng và tổng tiền hàng trong giỏ hàng
    void AmountAndPrice();
    // Chèn thông tin món hàng vào danh sách của cửa hàng
  
    void InsertToList();
    void Inventory();
    // Ghi danh sách hàng tồn vào file danhsach.xlsx
    void WriteToFile();
    void Menu();
      
};
void Calculator::WriteData() {
        Products sp;
        cin >> sp;
        cin.ignore();  // Loại bỏ ký tự newline trong bộ đệm nhập chuẩn
        List.push_back(sp);
}

// Thêm món hàng vào giỏ hàng
void Calculator::AddToCart(string Id) {
    bool timThay = false;
    for (int i = 0; i < List.size(); i++) {
        if (List[i].Id == Id) {  // truy cập trực tiếp vào thành viên dữ liệu Id
            if (List[i].amounts > 0) {   // truy cập trực tiếp vào thành viên dữ liệu amounts
                Cart.push_back(List[i]);
                List[i].amounts--;  // truy cập trực tiếp vào thành viên dữ liệu amounts và giảm giá trị đi 1
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
void Calculator::Delete(string Id){
    int ok = 0;
    for(int i=0;i<Cart.size();i++){
        if(Cart[i].Id == Id){
            if(Cart[i].amounts > 0){
                Cart.pop_back();
                Cart[i].amounts--;
                List[i].amounts++;
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
    int tongAmounts = 0;
    ll tongTien = 0;
    for (int i = 0; i < Cart.size(); i++) {
        tongAmounts += Cart[i].amounts;
        tongTien += Cart[i].amounts * Cart[i].price;
    }
    cout << "Tong so luong hang trong gio hang: " << tongAmounts << endl;
    cout << "Tong tien hang trong gio hang: " << tongTien << endl;
}

// Chèn thông tin món hàng vào danh sách của cửa hàng

void Calculator::InsertToList() {
    Products sp;
    int viTri;  // Vị trí cần chèn
        do {
            cout << "Nhap vi tri can chen (0 - " << List.size() - 1 << "): ";
            cin >> viTri;
                if (viTri < 0 || viTri > List.size() - 1) {
                cout << "Vi tri khong hop le. Vui long nhap lai." << endl;
    }
        } while (viTri < 0 || viTri > List.size() - 1);

        WriteData();  // Nhập thông tin của món hàng và gán giá trị cho đối tượng sp
        
    }



void Calculator::Inventory() {
    
        for (int i = 0; i < List.size(); i++) {
            List[i].ReadData();
            cout << endl;
        }
        cin.ignore();  
}

// Ghi danh sách hàng tồn vào file danhsach.xlsx
void Calculator::WriteToFile() {
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

void Calculator::Menu() {
    int choice;
    Products sp;
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
                WriteData();
                break;
            case 2: {
                string Id;
                cout << "Nhap ma hang: ";
                cin >> Id;
                AddToCart(Id);
            }

            break;
            case 3:
                AmountAndPrice();
                break;
            case 4:
                InsertToList();
                break;
            case 5:
                Inventory();
                break;
            case 6:
                WriteToFile();
                break;
            case 7:{
                string id;
                cout << "Nhap ma hang: ";
                cin >> id;
                Delete(id);
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
int main() {
    Calculator GlassStore;  
    GlassStore.Menu();
    return 0;
}