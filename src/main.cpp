// Student Gradebook - a C++ console app that demonstrates arrays.
//
// Arrays used:
//   std::string names[MAX_STUDENTS]            -> 1D array of student names
//   double      scores[MAX_STUDENTS][SUBJECTS] -> 2D array (student x subject)
//   double      totals[], averages[]           -> 1D arrays of computed values
//   int         rankOrder[]                    -> 1D array of indices, sorted for ranking

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

const int MAX_STUDENTS = 50;
const int SUBJECTS = 5;
const string SUBJECT_NAMES[SUBJECTS] = {"Maths", "English", "Science", "ICT", "Social"};

string names[MAX_STUDENTS];
double scores[MAX_STUDENTS][SUBJECTS];
double totals[MAX_STUDENTS];
double averages[MAX_STUDENTS];
int studentCount = 0;

// ---------- helpers ----------

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double readScore(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= 0 && value <= 100) {
            clearInput();
            return value;
        }
        cout << "  Invalid. Enter a number between 0 and 100.\n";
        clearInput();
    }
}

char gradeFor(double avg) {
    if (avg >= 80) return 'A';
    if (avg >= 70) return 'B';
    if (avg >= 60) return 'C';
    if (avg >= 50) return 'D';
    return 'F';
}

void calculate(int i) {
    double sum = 0;
    for (int j = 0; j < SUBJECTS; j++) sum += scores[i][j];
    totals[i] = sum;
    averages[i] = sum / SUBJECTS;
}

// ---------- features ----------

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Gradebook is full (" << MAX_STUDENTS << " students).\n";
        return;
    }
    cout << "Student name: ";
    string name;
    getline(cin, name);
    if (name.empty()) {
        cout << "Name cannot be empty.\n";
        return;
    }
    names[studentCount] = name;
    for (int j = 0; j < SUBJECTS; j++)
        scores[studentCount][j] = readScore("  " + SUBJECT_NAMES[j] + " score (0-100): ");
    calculate(studentCount);
    studentCount++;
    cout << "Added " << name << ".\n";
}

void viewAll() {
    if (studentCount == 0) {
        cout << "No students yet.\n";
        return;
    }
    cout << "\n" << left << setw(4) << "#" << setw(18) << "Name";
    for (int j = 0; j < SUBJECTS; j++) cout << setw(9) << SUBJECT_NAMES[j];
    cout << setw(9) << "Total" << setw(9) << "Average" << "Grade\n";
    cout << string(4 + 18 + SUBJECTS * 9 + 9 + 9 + 5, '-') << "\n";
    for (int i = 0; i < studentCount; i++) {
        cout << left << setw(4) << i + 1 << setw(18) << names[i].substr(0, 17);
        for (int j = 0; j < SUBJECTS; j++) cout << setw(9) << fixed << setprecision(1) << scores[i][j];
        cout << setw(9) << totals[i] << setw(9) << averages[i] << gradeFor(averages[i]) << "\n";
    }
}

void classStatistics() {
    if (studentCount == 0) {
        cout << "No students yet.\n";
        return;
    }
    cout << "\nClass statistics (" << studentCount << " students)\n";
    cout << left << setw(10) << "Subject" << setw(10) << "Average" << setw(10) << "Highest" << "Lowest\n";
    for (int j = 0; j < SUBJECTS; j++) {
        double sum = 0, hi = scores[0][j], lo = scores[0][j];
        for (int i = 0; i < studentCount; i++) {
            sum += scores[i][j];
            if (scores[i][j] > hi) hi = scores[i][j];
            if (scores[i][j] < lo) lo = scores[i][j];
        }
        cout << left << setw(10) << SUBJECT_NAMES[j] << setw(10) << fixed << setprecision(1)
             << sum / studentCount << setw(10) << hi << lo << "\n";
    }
}

// Fills rankOrder with student indices sorted by total score (highest first)
// using bubble sort. We sort the indices, not the data itself.
void buildRanking(int rankOrder[]) {
    for (int i = 0; i < studentCount; i++) rankOrder[i] = i;
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (totals[rankOrder[j]] < totals[rankOrder[j + 1]]) {
                int tmp = rankOrder[j];
                rankOrder[j] = rankOrder[j + 1];
                rankOrder[j + 1] = tmp;
            }
        }
    }
}

void showRanking() {
    if (studentCount == 0) {
        cout << "No students yet.\n";
        return;
    }
    int rankOrder[MAX_STUDENTS];
    buildRanking(rankOrder);
    cout << "\nRanking by total score\n";
    for (int r = 0; r < studentCount; r++) {
        int i = rankOrder[r];
        cout << right << setw(3) << r + 1 << ". " << left << setw(18) << names[i]
             << fixed << setprecision(1) << totals[i] << "  (avg " << averages[i]
             << ", grade " << gradeFor(averages[i]) << ")\n" << right;
    }
}

void searchStudent() {
    cout << "Name to search: ";
    string query;
    getline(cin, query);
    bool found = false;
    for (int i = 0; i < studentCount; i++) {          // linear search
        if (names[i] == query) {
            cout << names[i] << ": average " << fixed << setprecision(1) << averages[i]
                 << ", grade " << gradeFor(averages[i]) << "\n";
            found = true;
        }
    }
    if (!found) cout << "No student named \"" << query << "\".\n";
}

void saveReport() {
    ofstream out("gradebook_report.txt");
    if (!out) {
        cout << "Could not create report file.\n";
        return;
    }
    int rankOrder[MAX_STUDENTS];
    buildRanking(rankOrder);
    out << "GRADEBOOK REPORT\n================\n";
    for (int r = 0; r < studentCount; r++) {
        int i = rankOrder[r];
        out << r + 1 << ". " << names[i] << " | total " << fixed << setprecision(1) << totals[i]
            << " | average " << averages[i] << " | grade " << gradeFor(averages[i]) << "\n";
    }
    out.close();
    cout << "Saved to gradebook_report.txt\n";
}

void loadDemoData() {
    const string demoNames[6] = {"Kwame Mensah", "Ama Owusu", "Yaw Darko", "Efua Addo", "Kofi Boateng", "Zainab Yakubu"};
    const double demoScores[6][SUBJECTS] = {
        {72, 65, 80, 90, 70}, {88, 92, 79, 85, 90}, {95, 78, 88, 97, 82},
        {55, 60, 48, 70, 62}, {40, 52, 45, 58, 49}, {81, 74, 69, 77, 85}};
    studentCount = 0;
    for (int i = 0; i < 6; i++) {
        names[i] = demoNames[i];
        for (int j = 0; j < SUBJECTS; j++) scores[i][j] = demoScores[i][j];
        calculate(i);
        studentCount++;
    }
    cout << "Loaded 6 demo students.\n";
}

void printMenu() {
    cout << "\n===== STUDENT GRADEBOOK =====\n"
         << "1. Add student\n2. View all students\n3. Class statistics\n"
         << "4. Ranking\n5. Search student\n6. Save report to file\n"
         << "7. Load demo data\n0. Exit\nChoice: ";
}

int main() {
    int choice;
    while (true) {
        printMenu();
        if (!(cin >> choice)) {
            if (cin.eof()) break;
            clearInput();
            cout << "Please enter a number from the menu.\n";
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewAll(); break;
            case 3: classStatistics(); break;
            case 4: showRanking(); break;
            case 5: searchStudent(); break;
            case 6: saveReport(); break;
            case 7: loadDemoData(); break;
            case 0: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid option.\n";
        }
    }
    return 0;
}
