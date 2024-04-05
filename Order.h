#include <iostream>

#include "constants.h"
#include "utils.h"

using namespace std;

class Order {
private:
    long orderId;
    string itemId;
    string customerId;
    string status;
    float totalAmount;
    string createDate;

public:
    Order() {
        this->status = ORDER_STATUS_UNPAID;
        this->totalAmount = 0.0;
        this->createDate = getCurrentDate();
    }

    Order(long orderId, string itemId, string customerId) {
        this->orderId = orderId;
        this->itemId = itemId;
        this->customerId = customerId;
        this->status = ORDER_STATUS_UNPAID;
        this->totalAmount = 0.0;
        this->createDate = getCurrentDate();
    }

    ~Order() {}

    long getOrderId() {
        return this->orderId;
    }
    
    string getItemId() {
        return this->itemId;
    }

    void setItemId(string itemId) {
        this->itemId = itemId;
    }

    string getCustomerId() {
        return this->customerId = customerId;
    }

    void setCustomerId(string customerId) {
        this->customerId = customerId;
    }

    string getStatus() {
        return this->status;
    }

    void setStatus(string status) {
        this->status = status;
    }

    string getCreateDate() {
        return this->createDate;
    }

    float getTotalAmount() {
        return this->totalAmount;
    }

    void calcTotalAmount();

};

void Order::calcTotalAmount() {
    
}