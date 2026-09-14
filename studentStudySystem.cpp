#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student
{
public:
    int rollNo;
    char name[50];
    int age;
    char course[50];
    float marks;

    void input()
    {
        cout << "\nEnter Roll Number: ";
        cin >> rollNo;

        cin.ignore();

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Age: ";
        cin >> age;

        cin.ignore();

        cout << "Enter Course: ";
        cin.getline(course, 50);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display()
    {
        cout << "\nRoll Number : " << rollNo;
        cout << "\nName        : " << name;
        cout << "\nAge         : " << age;
        cout << "\nCourse      : " << course;
        cout << "\nMarks       : " << marks;
        cout << "\n-----------------------------";
    }
};

// Function to check whether a roll number already exists
bool rollExists(int roll)
{
    Student s;
    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s)))
    {
        if (s.rollNo == roll)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Add a new student
void addStudent()
{
    Student s;

    s.input();

    if (rollExists(s.rollNo))
    {
        cout << "\nStudent with this Roll Number already exists!\n";
        return;
    }

    ofstream file("students.dat", ios::binary | ios::app);

    file.write((char*)&s, sizeof(s));

    file.close();

    cout << "\nStudent added successfully!\n";
}

// Display all students
void displayStudents()
{
    Student s;
    ifstream file("students.dat", ios::binary);

    if (!file)
    {
        cout << "\nNo student records found.\n";
        return;
    }

    bool found = false;

    cout << "\n========== STUDENT RECORDS ==========\n";

    while (file.read((char*)&s, sizeof(s)))
    {
        s.display();
        found = true;
    }

    file.close();

    if (!found)
        cout << "\nNo student records found.\n";
}

// Search for a student
void searchStudent()
{
    int roll;
    cout << "\nEnter Roll Number to search: ";
    cin >> roll;

    Student s;
    ifstream file("students.dat", ios::binary);

    bool found = false;

    while (file.read((char*)&s, sizeof(s)))
    {
        if (s.rollNo == roll)
        {
            cout << "\nStudent Found!";
            s.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nStudent not found!\n";
}

// Update student information
void updateStudent()
{
    int roll;
    cout << "\nEnter Roll Number to update: ";
    cin >> roll;

    Student s;
    fstream file("students.dat", ios::binary | ios::in | ios::out);

    bool found = false;

    while (file.read((char*)&s, sizeof(s)))
    {
        if (s.rollNo == roll)
        {
            cout << "\nCurrent Student Information:";
            s.display();

            cout << "\n\nEnter New Information:\n";

            cin.ignore();

            cout << "Enter Name: ";
            cin.getline(s.name, 50);

            cout << "Enter Age: ";
            cin >> s.age;

            cin.ignore();

            cout << "Enter Course: ";
            cin.getline(s.course, 50);

            cout << "Enter Marks: ";
            cin >> s.marks;

            // Move pointer back to the beginning of this record
            file.seekp(-static_cast<int>(sizeof(s)), ios::cur);

            file.write((char*)&s, sizeof(s));

            found = true;
            cout << "\nStudent updated successfully!\n";
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nStudent not found!\n";
}

// Delete student
void deleteStudent()
{
    int roll;
    cout << "\nEnter Roll Number to delete: ";
    cin >> roll;

    Student s;

    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    bool found = false;

    while (inFile.read((char*)&s, sizeof(s)))
    {
        if (s.rollNo == roll)
        {
            found = true;
        }
        else
        {
            outFile.write((char*)&s, sizeof(s));
        }
    }

    inFile.close();
    outFile.close();

    // Replace old file with new file
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "\nStudent deleted successfully!\n";
    else
        cout << "\nStudent not found!\n";
}

// Main menu
int main()
{
    int choice;

    do
    {
        cout << "\n\n====================================";
        cout << "\n       STUDENT MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Add Student";
        cout << "\n2. Update Student";
        cout << "\n3. Delete Student";
        cout << "\n4. Display All Students";
        cout << "\n5. Search Student";
        cout << "\n6. Exit";
        cout << "\n====================================";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            updateStudent();
            break;

        case 3:
            deleteStudent();
            break;

        case 4:
            displayStudents();
            break;

        case 5:
            searchStudent();
            break;

        case 6:
            cout << "\nThank you for using Student Management System!\n";
            break;

        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}