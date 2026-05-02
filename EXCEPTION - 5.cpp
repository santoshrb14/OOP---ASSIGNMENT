// HARD 1: Flight Booking System
// Real-life use: Airlines — layered exception propagation & rethrowing
// Concept: Custom exceptions, throw_with_nested, rethrow_if_nested
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

struct BookingException : runtime_error {
    BookingException(const string& m) : runtime_error(m) {}
};

bool seats[5] = {false, true, false, true, true}; // false=occupied, true=free

void reserveSeat(int s) {
    if (s < 1 || s > 5) throw out_of_range("Seat " + to_string(s) + " doesn't exist.");
    if (!seats[s-1])    throw BookingException("Seat " + to_string(s) + " already occupied.");
    seats[s-1] = false;
    cout << "  [SEAT OK] Seat " << s << " reserved.\n";
}
void chargeCard(double fare, bool valid) {
    if (!valid) throw BookingException("Card declined by payment gateway.");
    cout << "  [PAYMENT OK] $" << fare << " charged.\n";
}
void bookFlight(const string& name, int seat, double fare, bool card) {
    try { reserveSeat(seat); chargeCard(fare, card);
          cout << "  [CONFIRMED] " << name << " | Seat " << seat << " | $" << fare << "\n"; }
    catch (const exception& e) {
        throw_with_nested(runtime_error("Booking failed for '" + name + "': " + e.what()));
    }
}
void printNested(const exception& e, int d = 0) {
    cout << string(d*2,' ') << (d ? "-> " : "[ERR] ") << e.what() << "\n";
    try { rethrow_if_nested(e); } catch (const exception& n) { printNested(n, d+1); }
}
int main() {
    cout << "=== Flight Booking System ===\n";
    struct T { string name; int seat; double fare; bool card; };
    T tests[] = {{"Alice",2,299.99,true},{"Bob",1,199.99,true},
                 {"Carol",9,349.00,true},{"Dave",4,149.00,false}};
    for (auto& t : tests) {
        cout << "\nBooking: " << t.name << "\n";
        try { bookFlight(t.name, t.seat, t.fare, t.card); }
        catch (const exception& e) { printNested(e); }
    }
}
