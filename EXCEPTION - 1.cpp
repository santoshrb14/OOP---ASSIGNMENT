// BEGINNER 1: ATM Withdrawal System
// Real-life use: Bank ATM — handles invalid PIN, insufficient funds
// Concept: try-catch with standard exceptions and basic throw

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class ATM {
private:
    double balance;
    int    correctPIN;

public:
    ATM(double bal, int pin) : balance(bal), correctPIN(pin) {}

    void verifyPIN(int enteredPIN) {
        if (enteredPIN != correctPIN)
            throw invalid_argument("Incorrect PIN! Access denied.");
    }

    void withdraw(double amount) {
        if (amount <= 0)
            throw invalid_argument("Withdrawal amount must be positive.");
        if (amount > balance)
            throw runtime_error("Insufficient funds! Available: $" + to_string(balance));
        if (fmod(amount, 100) != 0)
            throw invalid_argument("Amount must be a multiple of 100.");

        balance -= amount;
        cout << "[SUCCESS] $" << amount << " dispensed. Remaining balance: $" << balance << endl;
    }

    double getBalance() const { return balance; }
};

void performTransaction(ATM& atm, int pin, double amount) {
    try {
        atm.verifyPIN(pin);
        atm.withdraw(amount);
    }
    catch (const invalid_argument& e) {
        cout << "[INPUT ERROR]  " << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cout << "[TRANSACTION FAILED] " << e.what() << endl;
    }
}

int main() {
    ATM myATM(5000.0, 1234);

    cout << "=== ATM Simulation ===" << endl;

    cout << "\nTest 1 - Wrong PIN:" << endl;
    performTransaction(myATM, 9999, 500);

    cout << "\nTest 2 - Invalid amount (not multiple of 100):" << endl;
    performTransaction(myATM, 1234, 350);

    cout << "\nTest 3 - Insufficient funds:" << endl;
    performTransaction(myATM, 1234, 9000);

    cout << "\nTest 4 - Valid withdrawal:" << endl;
    performTransaction(myATM, 1234, 1000);

    return 0;
}
