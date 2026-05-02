#include <iostream>
#include <string>
using namespace std;

template <typename PriceType>
class CartItem {
private:
    string  itemName;
    PriceType price;
    int     quantity;

public:
    CartItem(string name, PriceType p, int qty)
        : itemName(name), price(p), quantity(qty) {}

    PriceType totalCost() const {
        return price * quantity;
    }

    void display() const {
        cout << "Item     : " << itemName << endl;
        cout << "Price    : $" << price << endl;
        cout << "Quantity : " << quantity << endl;
        cout << "Total    : $" << totalCost() << endl;
        cout << "-----------------------------" << endl;
    }

    void applyDiscount(PriceType discountPercent) {
        price = price - (price * discountPercent / 100);
        cout << "[Discount Applied] New price of " << itemName
             << " : $" << price << endl;
    }
};

int main() {
    cout << "===== Shopping Cart =====" << endl;

    // Integer price (whole dollar items)
    CartItem<int> book("C++ Primer", 45, 2);
    book.display();
    book.applyDiscount(10);
    book.display();

    // Double price (grocery/electronics)
    CartItem<double> headphones("Sony WH-1000XM5", 299.99, 1);
    headphones.display();
    headphones.applyDiscount(15.5);
    headphones.display();

    return 0;
}
