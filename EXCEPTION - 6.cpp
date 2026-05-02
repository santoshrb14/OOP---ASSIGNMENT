#include <iostream>
#include <string>
using namespace std;

// Generic Observer interface
template <typename EventData>
class Observer {
public:
    virtual void onEvent(const string& source, const EventData& data) = 0;
    virtual ~Observer() = default;
};

// Generic Subject (event source) — fixed max 5 observers for simplicity
template <typename EventData>
class Subject {
private:
    Observer<EventData>* observers[5];
    int count = 0;
    string name;

public:
    Subject(string n) : name(n) {}

    void subscribe(Observer<EventData>* obs) {
        if (count < 5) observers[count++] = obs;
    }

    void notify(const EventData& data) {
        for (int i = 0; i < count; i++)
            observers[i]->onEvent(name, data);
    }
};

// ---- Concrete Event Data ----
struct StockTick { string symbol; double price; double change; };

// ---- Concrete Observers ----
class MobileAlertObserver : public Observer<StockTick> {
public:
    void onEvent(const string& src, const StockTick& tick) override {
        if (abs(tick.change) >= 5.0)
            cout << "[MOBILE ALERT] " << src << ": " << tick.symbol
                 << " moved " << tick.change << "% -> $" << tick.price << endl;
    }
};

class PortfolioTracker : public Observer<StockTick> {
public:
    void onEvent(const string& src, const StockTick& tick) override {
        cout << "[PORTFOLIO]    " << tick.symbol << " @ $" << tick.price
             << "  (" << (tick.change >= 0 ? "+" : "") << tick.change << "%)" << endl;
    }
};

class StopLossObserver : public Observer<StockTick> {
    double threshold;
public:
    StopLossObserver(double t) : threshold(t) {}
    void onEvent(const string&, const StockTick& tick) override {
        if (tick.price < threshold)
            cout << "[STOP LOSS]    SELL TRIGGERED for " << tick.symbol
                 << " at $" << tick.price << " (below $" << threshold << ")" << endl;
    }
};

int main() {
    Subject<StockTick> market("NYSE");

    MobileAlertObserver mobile;
    PortfolioTracker    portfolio;
    StopLossObserver    stopLoss(145.0);

    market.subscribe(&mobile);
    market.subscribe(&portfolio);
    market.subscribe(&stopLoss);

    cout << "=== Stock Market Feed ===" << endl;
    market.notify({"AAPL", 178.50,  +2.3});
    market.notify({"TSLA", 142.10,  -6.8});   // triggers mobile + stop-loss
    market.notify({"NVDA", 890.00, +11.2});   // triggers mobile alert
    market.notify({"MSFT", 415.30,  +0.5});

    return 0;
}
