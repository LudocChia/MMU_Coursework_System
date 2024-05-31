#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

struct StudentInfo
{
    string studentId;
    string studentName;
    string className;
    vector<float> grades; // 5 grades for 5 subjects

    StudentInfo()
    {
        grades.resize(5, 0.0); // Initialize all grades to 0.0
    }
};

class Teacher
{
public:
    Teacher() {}

    static void loadStudents(const string &filename, vector<StudentInfo> &students)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Failed to open " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            StudentInfo student;
            string gradeStr;

            getline(ss, student.studentId, '|');
            getline(ss, student.studentName, '|');
            getline(ss, student.className, '|');
            for (int i = 0; i < 5; ++i)
            {
                getline(ss, gradeStr, '|');
                student.grades[i] = stof(gradeStr);
            }

            students.push_back(student);
        }

        file.close();
    }

    static void saveStudents(const vector<StudentInfo> &students, const string &filename)
    {
        ofstream file(filename);

        for (const auto &student : students)
        {
            file << student.studentId << "|" << student.studentName << "|" << student.className;
            for (const auto &grade : student.grades)
            {
                file << "|" << grade;
            }
            file << "\n";
        }

        file.close();
    }

    bool isDuplicateId(const vector<StudentInfo> &students, const string &id)
    {
        for (const auto &student : students)
        {
            if (student.studentId == id)
            {
                return true;
            }
        }
        return false;
    }

    string getGradeLetter(float grade)
    {
        if (grade == -1)
            return "-";
        else if (grade >= 90)
            return "A+";
        else if (grade >= 80)
            return "A";
        else if (grade >= 76)
            return "B+";
        else if (grade >= 72)
            return "B";
        else if (grade >= 68)
            return "B-";
        else if (grade >= 65)
            return "C+";
        else if (grade >= 60)
            return "C";
        else if (grade >= 56)
            return "C-";
        else if (grade >= 50)
            return "D+";
        else if (grade >= 40)
            return "D";
        else
            return "F";
    }

    void addStudentAndGrades()
    {
        vector<StudentInfo> students;
        loadStudents("students.txt", students);

        while (true)
        {
            system("cls");
            cout << "================================================================================" << endl;
            cout << "                            ADD STUDENT AND GRADES MENU                         " << endl;
            cout << "================================================================================" << endl;

            cout << "Please enter student information" << endl;

            StudentInfo newStudent;
            cout << "Student ID   : ";
            cin >> newStudent.studentId;

            if (isDuplicateId(students, newStudent.studentId))
            {
                cout << "\033[1;31mStudent ID already exists. Please enter a different ID.\033[0m" << endl;
                char choice;
                cout << "Do you want to retry? (Y/N): ";
                cin >> choice;
                if (choice == 'Y' || choice == 'y')
                {
                    continue;
                }
                else
                {
                    cout << "\033[1;32m    Returned Successfully.\033[0m" << endl;
                    system("pause");
                    system("cls");
                    return;
                }
            }

            cout << "Student Name : ";
            cin.ignore();
            getline(cin, newStudent.studentName);

            cout << "Student Class: ";
            getline(cin, newStudent.className);

            cout << "--------------------------------------------------------------------------------" << endl;
            cout << "Please enter subject mark:" << endl;

            string subjects[5] = {"Bahasa Melayu", "English", "Mathematics", "History", "Science"};
            for (int i = 0; i < 5; ++i)
            {
                cout << setw(13) << left << subjects[i] << ": ";
                cin >> newStudent.grades[i];
            }

            students.push_back(newStudent);
            saveStudents(students, "students.txt");
            cout << "================================================================================" << endl;
            cout << "\033[1;32mStudent and grades added successfully.\033[0m" << endl;
            system("pause");
            system("cls");
            return;
        }
    }

    void viewClassGrades()
    {
        system("cls");

        vector<StudentInfo> students;
        loadStudents("students.txt", students);

        cout << "==============================================================================================" << endl;
        cout << "                                CLASS GRADES (Unsorted Data)" << endl;
        cout << "==============================================================================================" << endl;
        cout << "| No. | Student ID      | Student Name       | Class    | Subject         | Mark    | Grade  |" << endl;
        cout << "----------------------------------------------------------------------------------------------" << endl;

        string subjects[5] = {"Bahasa Melayu", "English", "Mathematics", "History", "Science"};
        int no = 1;
        for (const auto &student : students)
        {
            for (int i = 0; i < 5; ++i)
            {
                if (i == 2)
                {
                    cout << "| " << setw(3) << left << no++ << " | " << setw(15) << left << student.studentId << " | " << setw(18) << left << student.studentName << " | " << setw(8) << left << student.className << " | " << setw(15) << left << subjects[i] << " | ";
                }
                else
                {
                    cout << "| " << setw(3) << left << "" << " | " << setw(15) << left << "" << " | " << setw(18) << left << "" << " | " << setw(8) << left << "" << " | " << setw(15) << left << subjects[i] << " | ";
                }

                if (student.grades[i] < 40.0f)
                {
                    cout << "\033[1;31m" << setw(8) << left << student.grades[i];
                }
                else
                {
                    cout << "\033[1;32m" << setw(8) << left << student.grades[i];
                }
                cout << "\033[0m" << " | " << setw(6) << left << getGradeLetter(student.grades[i]) << " |" << endl;
            }
            if (&student != &students.back())
            {
                cout << "----------------------------------------------------------------------------------------------" << endl;
            }
        }
        cout << "==============================================================================================" << endl;
        system("pause");
        system("cls");
    }

    void stringSearch()
    {
        vector<StudentInfo> students;
        loadStudents("students.txt", students);

        int searchChoice;
        system("cls");
        cout << "================================================================================" << endl;
        cout << "                                 SEARCH CATEGORY                                " << endl;
        cout << "================================================================================" << endl;
        cout << "Choose the category to search by:" << endl;
        cout << "[1] Student ID" << endl;
        cout << "[2] Student Name" << endl;
        cout << "[3] Student Class" << endl;
        cout << "[4] Subject" << endl;
        cout << "[5] Back to Assignment Menu" << endl;
        cout << "================================================================================" << endl;
        cout << "Enter your choice: ";
        cin >> searchChoice;

        if (searchChoice == 5)
        {
            return;
        }

        string searchString;
        if (searchChoice >= 1 && searchChoice <= 4)
        {
            cout << "Enter the string to search for: ";
            cin.ignore();
            getline(cin, searchString);
        }
        else
        {
            cout << "Invalid choice!" << endl;
            return;
        }

        bool found = false;
        string subjects[5] = {"Bahasa Melayu", "English", "Mathematics", "History", "Science"};
        int no = 1;

        cout << "==============================================================================================" << endl;
        cout << "                                SEARCH RESULTS" << endl;
        cout << "==============================================================================================" << endl;
        cout << "| No. | Student ID      | Student Name       | Class    | Subject         | Mark    | Grade  |" << endl;
        cout << "----------------------------------------------------------------------------------------------" << endl;

        for (const auto &student : students)
        {
            bool match = false;
            if (searchChoice == 1 && student.studentId.find(searchString) != string::npos)
                match = true;
            else if (searchChoice == 2 && student.studentName.find(searchString) != string::npos)
                match = true;
            else if (searchChoice == 3 && student.className.find(searchString) != string::npos)
                match = true;
            else if (searchChoice == 4)
            {
                for (int i = 0; i < 5; ++i)
                {
                    if (subjects[i].find(searchString) != string::npos)
                    {
                        cout << "| " << setw(3) << left << no++ << " | " << setw(15) << left << student.studentId << " | " << setw(18) << left << student.studentName << " | " << setw(8) << left << student.className << " | " << setw(15) << left << subjects[i] << " | ";
                        if (student.grades[i] < 40.0f)
                        {
                            cout << "\033[1;31m" << setw(6) << right << student.grades[i];
                        }
                        else
                        {
                            cout << "\033[1;32m" << setw(6) << right << student.grades[i];
                        }
                        cout << "\033[0m" << " | " << setw(6) << left << getGradeLetter(student.grades[i]) << " |" << endl;
                        cout << "----------------------------------------------------------------------------------------------" << endl;
                        found = true;
                    }
                }
            }

            if (match && searchChoice != 4)
            {
                found = true;
                cout << "| " << setw(3) << left << no++ << " | " << setw(15) << left << student.studentId << " | " << setw(18) << left << student.studentName << " | " << setw(8) << left << student.className << " | " << setw(15) << left << subjects[0] << " | ";
                if (student.grades[0] < 40.0f)
                {
                    cout << "\033[1;31m" << setw(6) << right << student.grades[0];
                }
                else
                {
                    cout << "\033[1;32m" << setw(6) << right << student.grades[0];
                }
                cout << "\033[0m" << " | " << setw(6) << left << getGradeLetter(student.grades[0]) << " |" << endl;
                for (int i = 1; i < 5; ++i)
                {
                    cout << "|     |                 |                    |          | " << setw(15) << left << subjects[i] << " | ";
                    if (student.grades[i] < 40.0f)
                    {
                        cout << "\033[1;31m" << setw(6) << right << student.grades[i];
                    }
                    else
                    {
                        cout << "\033[1;32m" << setw(6) << right << student.grades[i];
                    }
                    cout << "\033[0m" << " | " << setw(6) << left << getGradeLetter(student.grades[i]) << " |" << endl;
                }
                cout << "----------------------------------------------------------------------------------------------" << endl;
            }
        }

        if (!found)
        {
            cout << "No student information found with the given criteria." << endl;
        }
        cout << "==============================================================================================" << endl;
        system("pause");
    }

    void assignmentMenu()
    {
        int choice = 0;
        do
        {
            system("cls");
            cout << "================================================================================" << endl;
            cout << "                                 ASSIGNMENT MENU                                " << endl;
            cout << "================================================================================" << endl;
            cout << "[1] String Searching" << endl;
            cout << "[2] Ternary Searching" << endl;
            cout << "[3] Cocktail Sorting" << endl;
            cout << "[4] Heap Sorting" << endl;
            cout << "[5] Back to Main Menu" << endl;
            cout << "================================================================================" << endl;
            cout << "Please Enter Your Choice: ";
            cin >> choice;
            system("cls");

            switch (choice)
            {
            case 1:
                stringSearch();
                break;
            case 2:
                // ternary searching
                break;
            case 3:
                // cocktail sorting
                break;
            case 4:
                // heap sorting
                break;
            case 5:
                cout << "\033[1;32mReturned Successfully.\033[0m" << endl;
                system("pause");
                system("cls");
                return;
            default:
                cout << "\033[1;31mInvalid Choice. Please Try Again.\033[0m" << endl;
            }
        } while (true);
    }

    void openMenu()
    {
        int choice = 0;
        do
        {
            system("cls");
            cout << "================================================================================" << endl;
            cout << "                          Secondary Report Card System                          " << endl;
            cout << "================================================================================" << endl;
            time_t now = time(NULL);
            tm *local = localtime(&now);
            cout << "\t\t\t\t\t\t" << "Friday  " << local->tm_mday << "/" << local->tm_mon + 1 << "/" << local->tm_year + 1900 << endl;
            cout << "[1] Add Student and Grades" << endl;
            cout << "[2] View Class Grades" << endl;
            cout << "[3] Assignment" << endl;
            cout << "[4] Exit" << endl;
            cout << "================================================================================" << endl;
            cout << "Please Enter Your Choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                addStudentAndGrades();
                break;
            case 2:
                viewClassGrades();
                break;
            case 3:
                assignmentMenu();
                break;
            case 4:
                cout << "\033[1;32mExited the system successfully.\033[0m" << endl;
                return;
            default:
                cout << "\033[1;31mInvalid Choice. Please Try Again.\033[0m" << endl;
            }
        } while (true);
    }
};

int main()
{
    Teacher teacher;
    teacher.openMenu();

    return 0;
}
