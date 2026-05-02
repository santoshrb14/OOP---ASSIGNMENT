// INTERMEDIATE 1: Online Food Ordering System
// Real-life use: Swiggy/Zomato — handles order failures with custom exceptions
// Concept: Custom exception class hierarchy, re-throwing, exception chaining

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// ---------- Custom Exception Hierarchy ----------
class OrderException : public exception {
protected: string msg;
public:
    OrderException(const string& m) : msg(m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class ItemUnavailableException : public OrderException {
public:
    ItemUnavailableException(const string& item)
        : OrderException("Item unavailable: '" + item + "'. Try another restaurant.") {}
};

class RestaurantClosedException : public OrderException {
public:
    RestaurantClosedException(const string& rest)
        : OrderException("Restaurant '" + rest + "' is currently closed.") {}
};

class PaymentFailedException : public OrderException {
public:
    PaymentFailedException(const string& reason)
        : OrderException("Payment failed: " + reason) {}
};

// ---------- Order Processing ----------
void checkRestaurant(bool isOpen, const string& name) {
    if (!isOpen) throw RestaurantClosedException(name);
}

void checkItem(bool available, const string& item) {
    if (!available) throw ItemUnavailableException(item);
}

void processPayment(double balance, double amount) {
    if (balance < amount)
        throw PaymentFailedException("Wallet balance $" + to_string((int)balance) +
                                     " is less than order total $" + to_string((int)amount));
}

void placeOrder(bool restOpen, bool itemAvail, double wallet, double total,
                const string& rest, const string& item) {
    try {
        checkRestaurant(restOpen, rest);
        checkItem(itemAvail, item);
        processPayment(wallet, total);
        cout << "[ORDER PLACED] " << item << " from " << rest << " | Total: $" << total << endl;
    }
    catch (const PaymentFailedException& e) { cout << "[PAYMENT ERROR]  " << e.what() << endl; }
    catch (const ItemUnavailableException& e){ cout << "[MENU ERROR]     " << e.what() << endl; }
    catch (const RestaurantClosedException& e){ cout << "[RESTO ERROR]    " << e.what() << endl; }
    catch (const OrderException& e)          { cout << "[ORDER ERROR]    " << e.what() << endl; }
}

int main() {
    cout << "=== Food Ordering System ===" << endl;
    placeOrder(false, true,  200, 150, "Pizza Palace",  "Margherita");   // closed
    placeOrder(true,  false, 200, 150, "Burger Barn",   "Truffle Fries");// unavailable
    placeOrder(true,  true,   50, 150, "Sushi House",   "Dragon Roll");  // low wallet
    placeOrder(true,  true,  300, 150, "Pasta Point",   "Penne Arrabbiata"); // success
    return 0;
}
