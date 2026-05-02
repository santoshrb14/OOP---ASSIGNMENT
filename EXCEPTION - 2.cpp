// BEGINNER 2: Student Grade Entry System
// Real-life use: School portal — validates marks before storing
// Concept: Multiple catch blocks, throw with custom messages

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

struct Student {
    string name;
    double marks[5];
    int    count = 0;
};

void addMark(Student& s, double mark, const string& subject) {
    if (s.count >= 5)
        throw overflow_error("Cannot add more than 5 subjects.");
    if (mark < 0)
        throw underflow_error("Mark cannot be negative for subject: " + subject);
    if (mark > 100)
        throw out_of_range("Mark exceeds 100 for subject: " + subject);

    s.marks[s.count++] = mark;
    cout << "[ADDED] " << subject << " : " << mark << endl;
}

double calculateAverage(const Student& s) {
    if (s.count == 0)
        throw runtime_error("No marks entered. Cannot compute average.");
    double sum = 0;
    for (int i = 0; i < s.count; i++) sum += s.marks[i];
    return sum / s.count;
}

string getGrade(double avg) {
    if (avg >= 90) return "A+";
    if (avg >= 75) return "A";
    if (avg >= 60) return "B";
    if (avg >= 50) return "C";
    return "F";
}

int main() {
    Student s;
    s.name = "Ravi Kumar";

    cout << "=== Student Grade System ===" << endl;

    double inputs[] = {88, -5, 102, 76, 91, 55};
    string subjects[] = {"Math", "Physics", "Chemistry", "English", "CS", "History"};

    for (int i = 0; i < 6; i++) {
        try {
            addMark(s, inputs[i], subjects[i]);
        }
        catch (const underflow_error& e) { cout << "[NEGATIVE MARK]   " << e.what() << endl; }
        catch (const out_of_range& e)    { cout << "[EXCEEDS MAX]     " << e.what() << endl; }
        catch (const overflow_error& e)  { cout << "[LIMIT REACHED]   " << e.what() << endl; }
    }

    try {
        double avg = calculateAverage(s);
        cout << "\nStudent : " << s.name << endl;
        cout << "Average : " << avg << "%" << endl;
        cout << "Grade   : " << getGrade(avg) << endl;
    }
    catch (const runtime_error& e) { cout << "[ERROR] " << e.what() << endl; }

    return 0;
}
