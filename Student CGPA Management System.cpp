// ======================================================
// STUDENT CGPA MANAGEMENT SYSTEM (C++)
// ======================================================
// Features:
// 1. Add Student
// 2. Calculate CGPA
// 3. File Handling
// 4. Save File
// 5. Exit
// ======================================================

#include <iostream>  // input-output
#include <fstream>   // file handling
#include <vector>    // dynamic array
#include <iomanip>   // formatting (setprecision)
#include <limits>    // numeric limits
using namespace std; // standard namespace

// ================= COURSE CLASS =================
class Course
{
public:
    float grade; // grade value
    int credit;  // credit hours

    // constructor with initialization list
    Course(float g, int c) : grade(g), credit(c) {}
};

// ================= STUDENT CLASS =================
class Student
{
private:
    string name;            // student name
    vector<Course> courses; // list of courses
    float cgpa;             // calculated CGPA

public:
    // constructor
    Student(string n = "") : name(n), cgpa(0.0) {}

    // add course to vector
    void addCourse(float grade, int credit)
    {
        courses.push_back(Course(grade, credit)); // store course
    }

    // calculate CGPA
    void calculateCGPA()
    {
        float totalPoints = 0; // total grade points
        int totalCredits = 0;  // total credit hours

        // loop through courses
        for (const auto &c : courses)
        {
            totalPoints += c.grade * c.credit; // grade × credit
            totalCredits += c.credit;          // sum credits
        }

        // exception if no credits
        if (totalCredits == 0)
            throw runtime_error("Total credits cannot be zero.");

        cgpa = totalPoints / totalCredits; // final CGPA formula
    }

    // display student data
    void display() const
    {
        cout << "\nStudent Name: " << name << endl;
        cout << "----------------------------------\n";

        // table header
        cout << left << setw(10) << "Course"
             << setw(10) << "Grade"
             << setw(10) << "Credit" << endl;

        cout << "----------------------------------\n";

        // loop for displaying courses
        for (size_t i = 0; i < courses.size(); ++i)
        {
            cout << left << setw(10) << i + 1
                 << setw(10) << fixed << setprecision(2) << courses[i].grade
                 << setw(10) << courses[i].credit << endl;
        }

        cout << "----------------------------------\n";
        cout << "CGPA: " << fixed << setprecision(2) << cgpa << endl;
    }

    // save report in file
    void saveReport()
    {
        ofstream file("student_report.txt", ios::app); // open file (append mode)

        // check file opened
        if (!file)
        {
            cout << "Error opening file.\n";
            return;
        }

        file << "========================================\n";
        file << "Student Name   : " << name << "\n";
        file << "Total Courses  : " << courses.size() << "\n\n";

        file << "Course Details\n";
        file << "----------------------------------------\n";

        // write each course
        for (size_t i = 0; i < courses.size(); ++i)
        {
            file << "Course " << i + 1
                 << " : Grade = "
                 << fixed << setprecision(2) << courses[i].grade
                 << " | Credit = " << courses[i].credit << "\n";
        }

        file << "\nFinal CGPA     : "
             << fixed << setprecision(2) << cgpa << "\n";

        // performance classification
        if (cgpa >= 9)
            file << "Performance    : Excellent\n";
        else if (cgpa >= 7)
            file << "Performance    : Good\n";
        else if (cgpa >= 5)
            file << "Performance    : Average\n";
        else
            file << "Performance    : Needs Improvement\n";

        file << "========================================\n\n";

        file.close(); // close file
    }
};

// ================= FUNCTION TO ADD STUDENT =================
void addStudent()
{
    string name; // student name
    int n;       // number of courses
    float grade; // grade input
    int credit;  // credit input

    cout << "Enter Student Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
    getline(cin, name);                                  // read full name

    Student s(name); // create student object

    cout << "Enter number of courses: ";

    // validate number of courses
    while (true)
    {
        cin >> n;
        if (!cin.fail() && n > 0)
            break;
        cout << "Number of courses must be greater than 0: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    // loop for course input
    for (int i = 0; i < n; i++)
    {

        cout << "\nCourse " << i + 1 << endl;

        // validate grade
        while (true)
        {
            cout << "Enter Grade (0-10): ";
            cin >> grade;

            if (!cin.fail() && grade >= 0 && grade <= 10)
                break;

            cout << "Invalid grade. Try again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // validate credit
        while (true)
        {
            cout << "Enter Credit Hours (>0): ";
            cin >> credit;

            if (!cin.fail() && credit > 0)
                break;

            cout << "Invalid credit. Try again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        s.addCourse(grade, credit); // add course
    }

    try
    {
        s.calculateCGPA(); // compute CGPA
        s.display();       // show result
        s.saveReport();    // save file
        cout << "\nStudent report saved successfully.\n";
    }
    catch (exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }
}

// ================= MAIN FUNCTION =================
int main()
{

    int choice;

    do
    {
        cout << "\n===== STUDENT CGPA MANAGEMENT SYSTEM =====\n";
        cout << "1. Add New Student\n";
        cout << "2. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent(); // call function
            break;
        case 2:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 2); // repeat until exit

    return 0;
}