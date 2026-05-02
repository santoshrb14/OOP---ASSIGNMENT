#include <iostream>
#include <string>
using namespace std;

template <typename Key, typename Value>
class ConfigEntry {
private:
    Key   key;
    Value value;

public:
    ConfigEntry(Key k, Value v) : key(k), value(v) {}

    Key   getKey()   const { return key; }
    Value getValue() const { return value; }
    void  setValue(Value v) { value = v; }

    void display() const {
        cout << "[CONFIG] " << key << " = " << value << endl;
    }
};

// A simple fixed-size config store using templates
template <typename Key, typename Value, int MaxEntries>
class ConfigStore {
private:
    ConfigEntry<Key, Value>* entries[MaxEntries];
    int count = 0;

public:
    ~ConfigStore() {
        for (int i = 0; i < count; i++) delete entries[i];
    }

    bool set(Key k, Value v) {
        for (int i = 0; i < count; i++) {
            if (entries[i]->getKey() == k) {
                entries[i]->setValue(v);   // update existing
                return true;
            }
        }
        if (count >= MaxEntries) return false;
        entries[count++] = new ConfigEntry<Key, Value>(k, v);
        return true;
    }

    void displayAll() const {
        cout << "--- Configuration Store ---" << endl;
        for (int i = 0; i < count; i++)
            entries[i]->display();
    }
};

int main() {
    // String key, int value (e.g., timeouts, limits)
    ConfigStore<string, int, 5> intConfig;
    intConfig.set("timeout_sec",   30);
    intConfig.set("max_retries",    3);
    intConfig.set("port",        8080);
    intConfig.displayAll();

    cout << endl;

    // String key, string value (e.g., theme, language)
    ConfigStore<string, string, 5> strConfig;
    strConfig.set("theme",    "dark");
    strConfig.set("language", "en-US");
    strConfig.set("theme",    "light");   // update existing key
    strConfig.displayAll();

    cout << endl;

    // String key, bool value
    ConfigStore<string, bool, 3> flagConfig;
    flagConfig.set("debug_mode",   true);
    flagConfig.set("auto_save",   false);
    flagConfig.displayAll();

    return 0;
}
