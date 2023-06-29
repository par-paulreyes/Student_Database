#include <iostream>
#include <sstream>

using namespace std;

const int MAX_STUDENTS = 50;
const int MAX_SUBJECTS = 10;

class Student {
private:
    string name;
    int srcode;
    int numSubjects;
    string subjects[MAX_SUBJECTS];
    Student* next;

public:
    Student() : next(nullptr) {}

    void inputStudentData() {
        cout << "Name: ";
        cin.ignore();
        getline(cin, name);

        while (true) {
            cout << "Srcode: ";
            string input;
            if (getline(cin, input)) {
                stringstream ss(input);
                if (ss >> srcode) {
                    break;
                }
            }
            cout << "Invalid input! Please enter an integer.\n";
        }

        cout << "Number of Subjects: ";
        for (;;) {
            string input;
            if (getline(cin, input)) {
                stringstream ss(input);
                if (ss >> numSubjects && numSubjects >= 0 && numSubjects <= MAX_SUBJECTS) {
                    break;
                }
            }
            cout << "Error: Invalid input!\n";
            cout << "Number of Subjects: ";
        }

        cout << "Subjects:\n";
        for (int i = 0; i < numSubjects; ++i) {
            cout << "Subject " << i + 1 << ": ";
            getline(cin, subjects[i]);
        }
    }

    void printStudentData() const {
        cout << "Name: " << name << "\n";
        cout << "Srcode: " << srcode << "\n";
        cout << "Subjects: | ";
        for (int i = 0; i < numSubjects; ++i) {
            cout << subjects[i] << " | ";
        }
        cout << "\n\n";
    }

    int getSrcode() const {
        return srcode;
    }

    Student* getNext() const {
        return next;
    }

    void setNext(Student* student) {
        next = student;
    }
};

class LinkedList {
private:
    Student* head;
    int numStudents;

public:
    LinkedList() : head(nullptr), numStudents(0) {}

    void addStudent() {
        if (numStudents == MAX_STUDENTS) {
            cout << "Error: Maximum number of students reached.\n";
            return;
        }

        Student* newStudent = new Student();
        newStudent->inputStudentData();
        newStudent->setNext(head);
        head = newStudent;
        numStudents++;
    }

    int searchStudentBySrcode(int srcode) {
        Student* current = head;
        int index = 0;
        while (current) {
            if (current->getSrcode() == srcode) {
                return index;
            }
            current = current->getNext();
            index++;
        }
        return -1;
    }

    void displayAllStudents() {
        cout << "\nStudent's Data\n";
        Student* current = head;
        int index = 1;
        while (current) {
            cout << "Student " << index << ":\n";
            current->printStudentData();
            current = current->getNext();
            index++;
        }
    }

    void searchStudentInfo() {
        char choice;
        int searchSrcode;
        if (numStudents == 0) {
            cout << "No student data available.\n";
            return;
        }
        else
        displayAllStudents();

        while (true) {
            string input;
            if (getline(cin, input)) {
                stringstream ss(input);
                if (ss >> searchSrcode) {
                    break;
                }
            }
            cout << "Search Srcode: ";
        }

        int foundIndex = searchStudentBySrcode(searchSrcode);
        if (foundIndex != -1) {
            cout << "\nStudent found!\n";
            cout << "Student Information:\n";
            Student* current = head;
            for (int i = 0; i < foundIndex; ++i) {
                current = current->getNext();
            }
            current->printStudentData();

            cout << "Search another Srcode? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                searchStudentInfo();
            }
        } else {
            cout << "Srcode: " << searchSrcode << " not found.\n";
            cout << "Search another Srcode? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                searchStudentInfo();
            }
        }
    }

    ~LinkedList() {
        Student* current = head;
        while (current) {
            Student* next = current->getNext();
            delete current;
            current = next;
        }
    }
};

int main() {
    LinkedList studentList;
    char choice;

    do {
        cout << "Menu:\n";
        cout << "1. Add student\n";
        cout << "2. Search student\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                studentList.addStudent();
                break;

            case '2':
                studentList.searchStudentInfo();
                break;

            case '3':
                cout << "Do you want to exit? (y/n): ";
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    return 0;
                }
                break;

            default:
                cout << "Invalid choice! Please enter a valid option.\n";
                break;
        }
    } while (choice != '3');

    studentList.displayAllStudents();

    return 0;
}
