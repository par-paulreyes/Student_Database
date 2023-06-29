#include <iostream>
#include <sstream>

using namespace std;

const int MAX_STUDENTS = 50;
const int MAX_SUBJECTS = 10;

class Student
{
private:
    string name;
    int srcode;
    int numSubjects;
    string subjects[MAX_SUBJECTS];

public:
    void inputStudentData()
    {
        cout << "Name: ";
        cin.ignore();
        getline(cin, name);

        while (true)
        {
            cout << "Srcode: ";
            string input;
            if (getline(cin, input))
            {
                stringstream ss(input);
                if (ss >> srcode)
                {
                    break;
                }
            }
            cout << "Invalid input! Please enter an integer.\n";
        }

        cout << "Number of Subjects: ";
        for (;;)
        {
            string input;
            if (getline(cin, input))
            {
                stringstream ss(input);
                if (ss >> numSubjects && numSubjects >= 0 && numSubjects <= MAX_SUBJECTS)
                {
                    break;
                }
            }
            cout << "Error:Invalid input!\n";
            cout << "Number of Subjects: ";
        }

        cout << "Subjects:\n";
        for (int i = 0; i < numSubjects; ++i)
        {
            cout << "Subject " << i + 1 << ": ";
            getline(cin, subjects[i]);
        }
    }

    void printStudentData() const
    {
        cout << "Name: " << name << "\n";
        cout << "Srcode: " << srcode << "\n";
        cout << "Number of Subjects: " << numSubjects << "\n";
        cout << "Subjects: ";
        for (int i = 0; i < numSubjects; ++i)
        {
            cout << subjects[i] << " ";
        }
        cout << "\n\n";
    }

    int getSrcode() const
    {
        return srcode;
    }
};

int searchStudentBySrcode(const Student students[], int numStudents, int srcode)
{
    for (int i = 0; i < numStudents; ++i)
    {
        if (students[i].getSrcode() == srcode)
        {
            return i;
        }
    }
    return -1;
}
int main();

void displayAllStudents(const Student students[], int numStudents)
{
    if (numStudents == 0)
    {
        cout << "No student data available.\n";
        main();
    }
    else
    {
        cout << "\nStudent's Data\n";
        for (int i = 0; i < numStudents; ++i)
        {
            cout << "Student " << i + 1 << ":\n";
            students[i].printStudentData();
        }
    }
}

void searchStudentInfo(const Student students[], int numStudents)
{

    char choice;
    int searchSrcode;
    displayAllStudents(students, numStudents);
    while (true)
    {
        string input;
        if (getline(cin, input))
        {
            stringstream ss(input);
            if (ss >> searchSrcode)
            {
                break;
            }
        }
        cout << "Search Sr-Code: ";
    }

    int foundIndex = searchStudentBySrcode(students, numStudents, searchSrcode);
    if (foundIndex != -1)
    {
        cout << "\nStudent found!\n";
        cout << "Student Information:\n";
        students[foundIndex].printStudentData();
        cout << "Search another Sr-Code? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            searchStudentInfo(students, numStudents);
        }
        if (choice == 'n' || choice == 'N')
        {
            main();
        }
    }
    else
    {
        cout << "Sr-Code: " << searchSrcode << " not found.\n";
        cout << "Search another Sr-Code? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            searchStudentInfo(students, numStudents);
        }
        if (choice == 'n' || choice == 'N')
        {
            main();
        }
    }
}

int main()
{
    Student students[MAX_STUDENTS];
    int numStudents = 0;

    char choice;
    do
    {
        cout << "Menu:\n";
        cout << "1. Add student\n";
        cout << "2. Search student\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            if (numStudents == MAX_STUDENTS)
            {
                cout << "Error: Maximum number of students reached.\n";
                break;
            }
            students[numStudents].inputStudentData();
            numStudents++;
            break;

        case '2':
            searchStudentInfo(students, numStudents);
            break;

        case '3':
            cout << "Do you want to exit? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                exit(0);
            }
            break;

        default:
            cout << "Invalid choice! Please enter a valid option.\n";
            break;
        }
    } while (choice != '3');

    cout << "\nStudent's Data\n";
    for (int i = 0; i < numStudents; ++i)
    {
        cout << "Student " << i + 1 << ":\n";
        students[i].printStudentData();
    }

    return 0;
}
