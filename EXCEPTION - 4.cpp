// INTERMEDIATE 2: Employee Record Manager
// Real-life use: HR software — safely reads/writes employee records with error handling
// Concept: Exception safety, finally-like cleanup using RAII, nested try-catch

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

struct Employee { int id; string name; double salary; };

// RAII file guard — ensures file is closed even if exception is thrown
class FileGuard {
    fstream& file;
public:
    FileGuard(fstream& f) : file(f) {}
    ~FileGuard() { if (file.is_open()) { file.close(); cout << "[FILE CLOSED SAFELY]" << endl; } }
};

void saveEmployee(const string& filename, const Employee& emp) {
    fstream file(filename, ios::app);
    FileGuard guard(file);             // auto-closes on exit or exception

    if (!file.is_open())
        throw runtime_error("Cannot open file: " + filename);
    if (emp.id <= 0)
        throw invalid_argument("Employee ID must be positive. Got: " + to_string(emp.id));
    if (emp.salary < 0)
        throw invalid_argument("Salary cannot be negative for: " + emp.name);

    file << emp.id << "," << emp.name << "," << emp.salary << "\n";
    cout << "[SAVED] " << emp.name << " (ID:" << emp.id << ", Salary:$" << emp.salary << ")" << endl;
}

void loadEmployees(const string& filename) {
    fstream file(filename, ios::in);
    FileGuard guard(file);

    if (!file.is_open())
        throw runtime_error("File not found: " + filename);

    cout << "\n--- Employee Records ---" << endl;
    string line;
    int lineNum = 0;
    while (getline(file, line)) {
        lineNum++;
        try {
            istringstream ss(line);
            string idStr, name, salStr;
            if (!getline(ss, idStr, ',') || !getline(ss, name, ',') || !getline(ss, salStr, ','))
                throw runtime_error("Malformed record at line " + to_string(lineNum));
            cout << "ID:" << stoi(idStr) << " | " << name << " | $" << stod(salStr) << endl;
        }
        catch (const runtime_error& e) { cout << "[SKIP] " << e.what() << endl; }
    }
}

int main() {
    const string FILE = "/tmp/employees.txt";
    cout << "=== Employee Record System ===" << endl;

    Employee records[] = {{101,"Alice",75000},{-5,"Bob",50000},{103,"Carol",-100},{104,"David",90000}};
    for (auto& e : records) {
        try { saveEmployee(FILE, e); }
        catch (const invalid_argument& e) { cout << "[VALIDATION ERROR] " << e.what() << endl; }
        catch (const runtime_error& e)    { cout << "[FILE ERROR] "       << e.what() << endl; }
    }

    try { loadEmployees(FILE); }
    catch (const runtime_error& e) { cout << "[LOAD ERROR] " << e.what() << endl; }

    return 0;
}
