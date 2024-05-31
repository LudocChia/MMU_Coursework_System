#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

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
                    cout << "\033[1;31m" << setw(4) << right << fixed << setprecision(1) << student.grades[i] << "%  ";
                }
                else
                {
                    cout << "\033[1;32m" << setw(4) << right << fixed << setprecision(1) << student.grades[i] << "%  ";
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

    void ternarySearch(const vector<StudentInfo> &students, const string &key, int left, int right, vector<int> &results, bool byName = false)
    {
        if (right >= left)
        {
            int mid1 = left + (right - left) / 3;
            int mid2 = right - (right - left) / 3;

            bool found_mid1 = false;
            for (int i : results)
            {
                if (i == mid1)
                {
                    found_mid1 = true;
                    break;
                }
            }

            if ((!byName && students[mid1].studentId.find(key) != string::npos && !found_mid1) ||
                (byName && students[mid1].studentName.find(key) != string::npos && !found_mid1))
            {
                results.push_back(mid1);
            }

            bool found_mid2 = false;
            for (int i : results)
            {
                if (i == mid2)
                {
                    found_mid2 = true;
                    break;
                }
            }

            if ((!byName && students[mid2].studentId.find(key) != string::npos && !found_mid2) ||
                (byName && students[mid2].studentName.find(key) != string::npos && !found_mid2))
            {
                results.push_back(mid2);
            }

            ternarySearch(students, key, left, mid1 - 1, results, byName);
            ternarySearch(students, key, mid1 + 1, mid2 - 1, results, byName);
            ternarySearch(students, key, mid2 + 1, right, results, byName);
        }
    }

    void searchByStudentID(const vector<StudentInfo> &students, const string &id)
    {
        vector<int> results;
        ternarySearch(students, id, 0, students.size() - 1, results);
        if (!results.empty())
        {
            string subjects[5] = {"Bahasa Melayu", "English", "Mathematics", "History", "Science"};

            cout << "==============================================================================================" << endl;
            cout << "                                SEARCH RESULTS" << endl;
            cout << "==============================================================================================" << endl;
            cout << "| No. | Student ID      | Student Name       | Class    | Subject         | Mark    | Grade  |" << endl;
            cout << "----------------------------------------------------------------------------------------------" << endl;
            int no = 1;
            for (const auto &index : results)
            {
                StudentInfo student = students[index];
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
                        cout << "\033[1;31m" << setw(4) << right << fixed << setprecision(1) << student.grades[i] << "   ";
                    }
                    else
                    {
                        cout << "\033[1;32m" << setw(4) << right << fixed << setprecision(1) << student.grades[i] << "   ";
                    }
                    cout << "\033[0m" << " | " << setw(6) << left << getGradeLetter(student.grades[i]) << " |" << endl;
                }
                if (&index != &results.back())
                {
                    cout << "----------------------------------------------------------------------------------------------" << endl;
                }
            }
            cout << "==============================================================================================" << endl;
        }
        else
        {
            cout << "\033[1;31mStudent ID not found.\033[0m" << endl;
        }
        system("pause");
        system("cls");
    }

    void searchByStudentName(const vector<StudentInfo> &students, const string &name)
    {
        vector<int> results;
        ternarySearch(students, name, 0, students.size() - 1, results, true);
        if (!results.empty())
        {
            string subjects[5] = {"Bahasa Melayu", "English", "Mathematics", "History", "Science"};

            cout << "==============================================================================================" << endl;
            cout << "                                SEARCH RESULTS" << endl;
            cout << "==============================================================================================" << endl;
            cout << "| No. | Student ID      | Student Name       | Class    | Subject         | Mark    | Grade  |" << endl;
            cout << "----------------------------------------------------------------------------------------------" << endl;
            int no = 1;
            for (const auto &index : results)
            {
                StudentInfo student = students[index];
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
                        cout << "\033[1;31m" << setw(4) << right << fixed << setprecision(1) << student.grades[i] << "   ";
                    }
                    else
                    {
                        cout << "\033[1;32m" << setw(4) << right << fixed << setprecision(1) << student.grades[i] << "   ";
                    }
                    cout << "\033[0m" << " | " << setw(6) << left << getGradeLetter(student.grades[i]) << " |" << endl;
                }
                if (&index != &results.back())
                {
                    cout << "----------------------------------------------------------------------------------------------" << endl;
                }
            }
            cout << "==============================================================================================" << endl;
        }
        else
        {
            cout << "\033[1;31mStudent Name not found.\033[0m" << endl;
        }
        system("pause");
        system("cls");
    }

    void ternarySearchByClass(const vector<StudentInfo> &students, const string &className, int left, int right, vector<int> &results)
    {
        if (right >= left)
        {
            int mid1 = left + (right - left) / 3;
            int mid2 = right - (right - left) / 3;

            bool found_mid1 = false;
            for (int i : results)
            {
                if (i == mid1)
                {
                    found_mid1 = true;
                    break;
                }
            }

            if (students[mid1].className.find(className) != string::npos && !found_mid1)
            {
                results.push_back(mid1);
            }

            bool found_mid2 = false;
            for (int i : results)
            {
                if (i == mid2)
                {
                    found_mid2 = true;
                    break;
                }
            }

            if (students[mid2].className.find(className) != string::npos && !found_mid2)
            {
                results.push_back(mid2);
            }

            ternarySearchByClass(students, className, left, mid1 - 1, results);
            ternarySearchByClass(students, className, mid1 + 1, mid2 - 1, results);
            ternarySearchByClass(students, className, mid2 + 1, right, results);
        }
    }

    void searchByClass(const vector<StudentInfo> &students, const string &className)
    {
        vector<int> results;
        ternarySearchByClass(students, className, 0, students.size() - 1, results);
        if (!results.empty())
        {
            string subjects[5] = {"Bahasa Melayu", "English", "Mathematics", "History", "Science"};

            cout << "==============================================================================================" << endl;
            cout << "                                SEARCH RESULTS" << endl;
            cout << "==============================================================================================" << endl;
            cout << "| No. | Student ID      | Student Name       | Class    | Subject         | Mark    | Grade  |" << endl;
            cout << "----------------------------------------------------------------------------------------------" << endl;
            int no = 1;
            for (const auto &index : results)
            {
                StudentInfo student = students[index];
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
                        cout << "\033[1;31m" << setw(4) << right << fixed << setprecision(1) << student.grades[i] << "   ";
                    }
                    else
                    {
                        cout << "\033[1;32m" << setw(4) << right << fixed << setprecision(1) << student.grades[i] << "   ";
                    }
                    cout << "\033[0m" << " | " << setw(6) << left << getGradeLetter(student.grades[i]) << " |" << endl;
                }
                if (&index != &results.back())
                {
                    cout << "----------------------------------------------------------------------------------------------" << endl;
                }
            }
            cout << "==============================================================================================" << endl;
        }
        else
        {
            cout << "\033[1;31mClass not found.\033[0m" << endl;
        }
        system("pause");
        system("cls");
    }

    void ternarySearchBySubject(const vector<StudentInfo> &students, const string &subject, int subjectIndex, int left, int right, vector<int> &results)
    {
        if (right >= left)
        {
            int mid1 = left + (right - left) / 3;
            int mid2 = right - (right - left) / 3;

            bool found_mid1 = false;
            for (int i : results)
            {
                if (i == mid1)
                {
                    found_mid1 = true;
                    break;
                }
            }

            if (students[mid1].grades[subjectIndex] != -1 && !found_mid1)
            {
                results.push_back(mid1);
            }

            bool found_mid2 = false;
            for (int i : results)
            {
                if (i == mid2)
                {
                    found_mid2 = true;
                    break;
                }
            }

            if (students[mid2].grades[subjectIndex] != -1 && !found_mid2)
            {
                results.push_back(mid2);
            }

            ternarySearchBySubject(students, subject, subjectIndex, left, mid1 - 1, results);
            ternarySearchBySubject(students, subject, subjectIndex, mid1 + 1, mid2 - 1, results);
            ternarySearchBySubject(students, subject, subjectIndex, mid2 + 1, right, results);
        }
    }

    void searchBySubject(const vector<StudentInfo> &students, const string &subject)
    {
        int subjectIndex = -1;
        string subjects[5] = {"Bahasa Melayu", "English", "Mathematics", "History", "Science"};

        for (int i = 0; i < 5; ++i)
        {
            if (subjects[i].find(subject) != string::npos)
            {
                subjectIndex = i;
                break;
            }
        }

        if (subjectIndex == -1)
        {
            cout << "\033[1;31mInvalid subject.\033[0m" << endl;
            return;
        }

        vector<int> results;
        ternarySearchBySubject(students, subject, subjectIndex, 0, students.size() - 1, results);

        if (!results.empty())
        {
            cout << "Results for subject \"" << subject << "\":" << endl;
            cout << "==============================================================================================" << endl;
            cout << "| No. | Student ID      | Student Name       | Class    | Subject         | Mark    | Grade  |" << endl;
            cout << "----------------------------------------------------------------------------------------------" << endl;
            int no = 1;
            for (const auto &index : results)
            {
                StudentInfo student = students[index];
                cout << "| " << setw(3) << left << no++ << " | " << setw(15) << left << student.studentId << " | " << setw(18) << left << student.studentName << " | " << setw(8) << left << student.className << " | " << setw(15) << left << subjects[subjectIndex] << " | ";
                if (student.grades[subjectIndex] < 40.0f)
                {
                    cout << "\033[1;31m" << setw(4) << right << fixed << setprecision(1) << student.grades[subjectIndex] << "   ";
                }
                else
                {
                    cout << "\033[1;32m" << setw(4) << right << fixed << setprecision(1) << student.grades[subjectIndex] << "   ";
                }
                cout << "\033[0m" << " | " << setw(6) << left << getGradeLetter(student.grades[subjectIndex]) << " |" << endl;
            }
            cout << "==============================================================================================" << endl;
        }
        else
        {
            cout << "\033[1;31mNo results found for subject \"" << subject << "\".\033[0m" << endl;
        }
        system("pause");
        system("cls");
    }

    void searchStudent()
    {
        system("cls");

        vector<StudentInfo> students;
        loadStudents("students.txt", students);

        cout << "==============================================================================================" << endl;
        cout << "                                  SEARCH STUDENT" << endl;
        cout << "==============================================================================================" << endl;

        int choice;
        cout << "[1] Search by Student ID" << endl;
        cout << "[2] Search by Student Name" << endl;
        cout << "[3] Search by Class" << endl;
        cout << "[4] Search by Subject" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        string searchStr;
        float searchGrade;
        switch (choice)
        {
        case 1:
            cout << "Enter Student ID to search: ";
            cin >> searchStr;
            searchByStudentID(students, searchStr);
            break;
        case 2:
            cout << "Enter Student Name to search: ";
            cin.ignore();
            getline(cin, searchStr);
            searchByStudentName(students, searchStr);
            break;
        case 3:
            cout << "Enter Class to search: ";
            cin.ignore();
            getline(cin, searchStr);
            searchByClass(students, searchStr);
            break;
        case 4:
            cout << "Enter Subject to search: ";
            cin.ignore();
            getline(cin, searchStr);
            searchBySubject(students, searchStr);
            break;
        default:
            cout << "\033[1;31mInvalid choice.\033[0m" << endl;
            break;
        }

        system("pause");
        system("cls");
    }

    void assignmentMenu()
    {
        system("cls");
        int choice = 0;
        do
        {
            cout << "================================================================================" << endl;
            cout << "                                 ASSIGNMENT MENU                                " << endl;
            cout << "================================================================================" << endl;
            cout << "[1] String Searching" << endl;
            cout << "[2] Search Student" << endl;
            cout << "[3] Cocktail Sorting" << endl;
            cout << "[4] Heap Sorting" << endl;
            cout << "[5] Back to Main Menu" << endl;
            cout << "================================================================================" << endl;
            cout << "Please Enter Your Choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                // string searching
                break;
            case 2:
                searchStudent();
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
