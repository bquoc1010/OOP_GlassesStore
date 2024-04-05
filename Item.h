#include <iostream>

using namespace std;

class Item {
private:
    string itemId;
    string productId;
    int count;

public:
    Item() {
        this->count = 0;
    };
    Item(string itemId, string productId, int count) {
        this->itemId = itemId;
        this->productId = productId;
        this->count = count;
    }

    ~Item() {};

    string getProductId() {
        return this->productId;
    }

    void setProductId(string productId) {
        return this->productId;
    }

    int getCount() {
        return this->count;
    }

    void setCount(int count) {
        this->count = count;
    }
};