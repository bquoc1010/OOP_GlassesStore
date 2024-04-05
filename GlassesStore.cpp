#include <bits/stdc++.h>
// #include "Calculator.h"
#include "Product.h"
// #include "utils.h"

using namespace std;
using ll = long long;


// Lớp máy tính tiền

int main() {
    // Calculator GlassStore;  
    // GlassStore.showMenu();fads
    Product product("002", "test 5", 2121.2121, 5, "2024-04-06", false);

    // Product::save(product);
    // Product::showAllProducts();
    // Product product2 = Product::findByProductId("002");
    // product2.show();

    Product::remove("003");
    return 0;
}