#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <iomanip>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

struct AwardNode
{
    string award;
    AwardNode *next;

    AwardNode(const string &a) : award(a), next(nullptr) {}
};

struct AwardLinkedList
{
    AwardNode *head;

    AwardLinkedList() : head(nullptr) {}

    void addAward(const string &newAward)
    {
        AwardNode *newNode = new AwardNode(newAward);
        newNode->next = head;
        head = newNode;
    }

    void printAwards() const
    {
        AwardNode *current = head;
        while (current != nullptr)
        {
            cout << current->award << endl;
            current = current->next;
        }
    }

    bool deleteAward(const string &targetAward)
    {
        AwardNode *current = head;
        AwardNode *prev = nullptr;

        while (current != nullptr)
        {
            if (current->award == targetAward)
            {
                if (prev == nullptr)
                {
                    head = current->next;
                }
                else
                {
                    prev->next = current->next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    ~AwardLinkedList()
    {
        while (head != nullptr)
        {
            AwardNode *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

struct CommentNode
{
    string comment;
    CommentNode *next;

    CommentNode(const string &c) : comment(c), next(nullptr) {}
};

struct CommentLinkedList
{
    CommentNode *head;

    CommentLinkedList() : head(nullptr) {}

    void addComment(const string &newComment)
    {
        CommentNode *newNode = new CommentNode(newComment);
        newNode->next = head;
        head = newNode;
    }

    void printComments() const
    {
        CommentNode *current = head;
        while (current != nullptr)
        {
            cout << current->comment << endl;
            current = current->next;
        }
    }

    bool deleteComment(const string &targetComment)
    {
        CommentNode *current = head;
        CommentNode *prev = nullptr;

        while (current != nullptr)
        {
            if (current->comment == targetComment)
            {
                if (prev == nullptr)
                {
                    head = current->next;
                }
                else
                {
                    prev->next = current->next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    ~CommentLinkedList()
    {
        while (head != nullptr)
        {
            CommentNode *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

struct SubjectNode
{
    string subjectCode;
    string subjectName;
    vector<string> subjectClasses;
    SubjectNode *next;

    SubjectNode(const string &code, const string &name, const vector<string> &classes)
        : subjectCode(code), subjectName(name), subjectClasses(classes), next(nullptr) {}
};

struct SubjectLinkedList
{
    SubjectNode *head;

    SubjectLinkedList() : head(nullptr) {}

    void addSubject(const string &code, const string &name, const vector<string> &classes)
    {
        SubjectNode *newNode = new SubjectNode(code, name, classes);
        newNode->next = head;
        head = newNode;
    }

    void printSubjects() const
    {
        SubjectNode *current = head;
        while (current != nullptr)
        {
            cout << current->subjectCode << " | " << current->subjectName << " | ";
            for (const auto &cls : current->subjectClasses)
            {
                cout << cls << " ";
            }
            cout << endl;
            current = current->next;
        }
    }

    bool deleteSubject(const string &code)
    {
        SubjectNode *current = head;
        SubjectNode *prev = nullptr;

        while (current != nullptr)
        {
            if (current->subjectCode == code)
            {
                if (prev == nullptr)
                {
                    head = current->next;
                }
                else
                {
                    prev->next = current->next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    ~SubjectLinkedList()
    {
        while (head != nullptr)
        {
            SubjectNode *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

struct StudentInfo
{
    string studentId;
    string studentClass;
    CommentLinkedList comments;
    AwardLinkedList awards;
    vector<float> grades;
    float attendancePercentage;

    StudentInfo() : attendancePercentage(0.0)
    {
        grades.resize(21, 0.0);
    }
};

class Identity
{
public:
    virtual void open_menu() = 0;

    string m_type;
    string m_id;
    string m_name;
    string m_password;
    string m_gender;
    string m_class;

    virtual ~Identity()
    {
        ;
    }
};

class Teacher : public Identity
{

    friend class Student;

public:
    Teacher()
    {
        ;
    }

    ~Teacher()
    {
        ;
    }

    Teacher(string user_type, string user_id, string user_name, string user_password, string user_gender, string user_class)
    {
        this->m_type = user_type;
        this->m_id = user_id;
        this->m_name = user_name;
        this->m_password = user_password;
        this->m_gender = user_gender;
        this->m_class = user_class;
    }

    static void loadStudentGradeAttendance(const string &filename, vector<StudentInfo> &students)
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
            getline(ss, student.studentClass, '|');
            for (int i = 0; i < 21; ++i)
            {
                getline(ss, gradeStr, '|');
                student.grades[i] = stof(gradeStr);
            }
            getline(ss, gradeStr);
            student.attendancePercentage = stof(gradeStr);

            students.push_back(student);
        }

        file.close();
    }

    static void saveStudentGradeAttendace(const vector<StudentInfo> &students, const string &filename)
    {
        ofstream file(filename);

        for (const auto &student : students)
        {
            file << student.studentId << "|" << student.studentClass;
            for (const auto &grade : student.grades)
            {
                file << "|" << grade;
            }
            file << "|" << student.attendancePercentage << "\n";
        }

        file.close();
    }

    static void loadStudentComments(const string &filename, vector<StudentInfo> &students)
    {
        ifstream file(filename);
        string line;

        if (!file.is_open())
        {
            cout << "Failed to open " << filename << endl;
            return;
        }

        while (getline(file, line))
        {
            stringstream ss(line);
            string studentId, studentClass, comment;

            getline(ss, studentId, '|');
            getline(ss, studentClass, '|');

            auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                              { return s.studentId == studentId; });

            if (it != students.end())
            {
                while (getline(ss, comment, '|'))
                {
                    it->comments.addComment(comment);
                }
            }
        }
        file.close();
    }

    static void saveStudentComments(const vector<StudentInfo> &students, const string &filename)
    {
        ofstream file(filename);

        for (const auto &student : students)
        {
            file << student.studentId << "|" << student.studentClass;

            CommentNode *current = student.comments.head;
            while (current != nullptr)
            {
                file << "|" << current->comment;
                current = current->next;
            }
            file << "\n";
        }

        file.close();
    }
    static void loadStudentAwards(const string &filename, vector<StudentInfo> &students)
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
            string studentId, award;

            getline(ss, studentId, '|');

            auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                              { return s.studentId == studentId; });

            if (it != students.end())
            {
                while (getline(ss, award, '|'))
                {
                    it->awards.addAward(award);
                }
            }
        }
        file.close();
    }

    static void saveStudentAwards(const vector<StudentInfo> &students, const string &filename)
    {
        ofstream file(filename);

        for (const auto &student : students)
        {
            file << student.studentId;

            AwardNode *current = student.awards.head;
            while (current != nullptr)
            {
                file << "|" << current->award;
                current = current->next;
            }
            file << "\n";
        }

        file.close();
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

    void open_menu()
    {
        int choice = 0;
        do
        {
            system("cls");
            cout << "================================================================================" << endl;
            cout << "                                 TEACHER MENU                                 " << endl;
            cout << "================================================================================" << endl;
            cout << right << setw(50) << "Welcome, " << this->m_name << endl;
            cout << "    [1] Update Student Marks" << endl;
            cout << "    [2] Update Student Attendance" << endl;
            cout << "    [3] View Class Marks and Attendance" << endl;
            cout << "    [4] View Student Marks and Attendance" << endl;
            cout << "    [5] Update Student Comment" << endl;
            cout << "    [6] Manage Student Awards" << endl;
            cout << "    [7] Logout" << endl;
            cout << "================================================================================" << endl;
        RECHOICE:
            cout << "    Please Enter Your Choice: ";
            cin >> choice;
            if (cin.fail())
            {
                cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto RECHOICE;
            }

            switch (choice)
            {
            case 1:
                system("cls");
                update_student_grades();
                break;
            case 2:
                system("cls");
                update_student_attendance();
                break;
            case 3:
                system("cls");
                view_class_attendance_and_grades();
                break;
            case 4:
                system("cls");
                student_attendance_and_grades();
                break;
            case 5:
                system("cls");
                update_student_comment();
                break;
            case 6:
                system("cls");
                manage_student_awards();
                break;
            case 7:
                return;
            default:
                cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
                goto RECHOICE;
            }
        } while (true);
        return;
    }

    void update_student_grades()
    {
        vector<StudentInfo> students;
        loadStudentGradeAttendance("gradeAttendance.txt", students);

        cout << "============================================================================" << endl;
        cout << "                            UPDATE STUDENT MARKS" << endl;
        cout << "============================================================================" << endl;
        cout << "    Enter the student ID : ";

        string studentId;
        cin >> studentId;

        auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                          { return s.studentId == studentId; });
        if (it == students.end())
        {
            char choice;

            cout << "\033[1;31m    Student not found. Please try again. \033[0m" << endl;
            cout << "    Do you want to try again ? (Y/N) : ";
            cin >> choice;

            while (choice == 'y' || choice == 'Y')
            {
                cout << "============================================================================" << endl;
                cout << "    Enter the correct student ID : ";
                cin >> studentId;
                it = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                             { return s.studentId == studentId; });

                if (it == students.end())
                {
                    cout << "\033[1;31m    Student not found. Please try again. \033[0m" << endl;
                    cout << "    Do you want to try again ? (Y/N) : ";
                    cin >> choice;
                }
                else
                {
                    break;
                }
            }
            if (choice != 'y' && choice != 'Y')
            {
                system("cls");
                return;
            }
        }

        system("cls");
        cout << "============================================================================" << endl;
        cout << "                            UPDATE STUDENT MARKS" << endl;
        cout << "============================================================================" << endl;
        cout << "    Select the term to update marks" << endl;
        cout << "    [1] First Term Exam" << endl;
        cout << "    [2] Midterm Exam" << endl;
        cout << "    [3] Final Exam" << endl;
        cout << "    [4] Back to Main Menu" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "    Enter your choice: ";
        int termChoice;
        cin >> termChoice;

        int gradeOffset;
        switch (termChoice)
        {
        case 1:
            gradeOffset = 0;
            break;
        case 2:
            gradeOffset = 7;
            break;
        case 3:
            gradeOffset = 14;
            break;
        case 4:
            return;
        default:
            while (termChoice != 1 && termChoice != 2 && termChoice != 3 && termChoice != 4)
            {
                cout << "\033[1;31m    Invalid choice. Please make sure you entered the correct one. \033[0m" << endl;
                cout << "----------------------------------------------------------------------------" << endl;
                cout << "    Enter the correct choice : ";
                cin >> termChoice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                if (termChoice == 1)
                {
                    gradeOffset = 0;
                }
                else if (termChoice == 2)
                {
                    gradeOffset = 7;
                }
                else if (termChoice == 3)
                {
                    gradeOffset = 14;
                }
                else if (termChoice == 4)
                {
                    return;
                }
            }
        }
        char continueUpdate;
        do
        {
            system("cls");
            cout << "============================================================================" << endl;
            cout << "                            UPDATE STUDENT MARKS" << endl;
            cout << "============================================================================" << endl;
            cout << "    Current grades for " << studentId << endl;
            string subjects[7] = {"Bahasa Melayu", "English", "Mandarin", "Mathematics", "History", "Science", "Moral"};
            const int setwValues[] = {6, 12, 11, 8, 12, 12, 14};
            for (int i = 0; i < 7; ++i)
            {
                cout << "    [" << i + 1 << "] " << subjects[i] << setw(setwValues[i]) << ": ";

                if (it->grades[gradeOffset + i] == -1)
                {
                    cout << "-";
                }
                else
                {
                    cout << static_cast<int>(it->grades[gradeOffset + i]);
                }
                cout << endl;
            }
            cout << "----------------------------------------------------------------------------" << endl;
            cout << "    Select the subject code to update the marks (1-7) : ";
            int subjectChoice;
            cin >> subjectChoice;

            if (cin.fail() || subjectChoice < 1 || subjectChoice > 7)
            {
                cout << "\033[1;31m    Invalid subject choice. Please try again. \033[0m" << endl;

                while (subjectChoice < 1 || subjectChoice > 7)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "    Select the correct subject code to update the marks (1-7) : ";
                    cin >> subjectChoice;
                    if (subjectChoice < 1 || subjectChoice > 7)
                    {
                        cout << "\033[1;31m    Invalid subject code choice. Please try again. \033[0m" << endl;
                    }
                }
            }

            cout << "    Enter the new mark : ";
            float newGrade;
            cin >> newGrade;

            while (cin.fail() || newGrade < 0 || newGrade > 100)
            {
                cout << "\033[1;31m    Invalid marks. Please enter a valid number between 0 and 100.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "    Enter the correct marks: ";
                cin >> newGrade;
            }

            it->grades[gradeOffset + subjectChoice - 1] = newGrade;

            saveStudentGradeAttendace(students, "gradeAttendance.txt");
            cout << "\33[1;32m    Marks updated successfully! \033[0m" << endl;

            cout << "    Do you want to update another subject? (Y/N): ";
            cin >> continueUpdate;

            while (cin.fail())
            {
                cout << "\033[1;31m    Invalid choice. Please enter agian.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "    Enter the correct choice : ";
                cin >> continueUpdate;

                if (continueUpdate != 'y' && continueUpdate != 'Y')
                {
                    system("pause");
                    system("cls");
                }
            }
        } while (continueUpdate == 'y' || continueUpdate == 'Y');
    }

    void update_student_attendance()
    {
        vector<StudentInfo> students;
        loadStudentGradeAttendance("gradeAttendance.txt", students);

        cout << "============================================================================" << endl;
        cout << "                       UPDATE STUDENT ATTENDANCE " << endl;
        cout << "============================================================================" << endl;
        cout << "    Enter the student ID : ";
        string studentId;
        cin >> studentId;

        auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                          { return s.studentId == studentId; });
        if (it == students.end() || it->studentClass != this->m_class)
        {
            do
            {
                cout << "\033[1;31m    Student not found or not in your class. Please try again. \033[0m" << endl;
                cout << "    Enter the correct student ID : ";
                cin >> studentId;

                it = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                             { return s.studentId == studentId; });
            } while (it == students.end() || it->studentClass != this->m_class);
        }

        system("cls");
        cout << "============================================================================" << endl;
        cout << "                       UPDATE STUDENT ATTENDANCE " << endl;
        cout << "============================================================================" << endl;
        cout << "    Current attendance for " << studentId << " : ";
        if (it->attendancePercentage == -1)
        {
            cout << "-" << endl;
        }
        else
        {
            cout << it->attendancePercentage << "%" << endl;
        }
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "    Enter the new attendance or press enter to skip: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string newAttendanceStr;
        getline(cin, newAttendanceStr);

        if (!newAttendanceStr.empty())
        {
            try
            {
                float newAttendance = stof(newAttendanceStr);
                while (newAttendance < 0.0f || newAttendance > 100.0f)
                {
                    cout << "\033[1;31m    Invalid attendance value. Please enter again. \033[0m" << endl;
                    cout << "============================================================================" << endl;
                    cout << "    Enter the correct attendance : ";
                    getline(cin, newAttendanceStr);
                    newAttendance = stof(newAttendanceStr);
                }
                it->attendancePercentage = newAttendance;
                saveStudentGradeAttendace(students, "gradeAttendance.txt");
                cout << "\33[1;32m \n    Attendance updated successfully.\n \033[0m" << endl;
                system("pause");
                system("cls");
            }
            catch (const invalid_argument &)
            {
                cout << "\033[1;31m    Invalid input. Attendance not updated. \033[0m" << endl;
                system("pause");
                system("cls");
            }
        }
        else
        {
            cout << "\033[1;32m    Update skipped.\033[0m" << endl;
            system("pause");
            system("cls");
        }
    }

    void view_class_attendance_and_grades()
    {
        vector<StudentInfo> students;
        loadStudentGradeAttendance("gradeAttendance.txt", students);

        string classToView = this->m_class;
        int termChoice;
        int gradeOffset;
        cout << "============================================================================" << endl;
        cout << "                       VIEW CLASS MARKS AND ATTENDANCE " << endl;
        cout << "============================================================================" << endl;
        cout << "    Select the term to view marks " << endl;
        cout << "    [1] First Term Exam" << endl;
        cout << "    [2] Midterm Exam" << endl;
        cout << "    [3] Final Exam" << endl;
        cout << "    [4] Back to Main Menu" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        do
        {
            cout << "    Enter your choice : ";
            if (!(cin >> termChoice))
            {
                cout << "\033[1;31m    Invalid input. Please enter again. \033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            switch (termChoice)
            {
            case 1:
                gradeOffset = 0;
                break;
            case 2:
                gradeOffset = 7;
                break;
            case 3:
                gradeOffset = 14;
                break;
            case 4:
                system("pause");
                system("cls");
                return;
            default:
                cout << "\033[1;31m    Invalid choice. Please enter again. \033[0m" << endl;
            }
        } while (termChoice < 1 || termChoice > 3);

        system("cls");
        cout << "=======================================================================================================================================" << endl;
        cout << "                                                      CLASS " << classToView << " MARKS AND ATTENDANCE" << endl;
        cout << "=======================================================================================================================================" << endl;
        cout << left << setw(15) << "Student ID"
             << setw(15) << "Bahasa Melayu" << setw(15) << "English" << setw(15) << "Mandarin"
             << setw(15) << "Mathematics" << setw(15) << "History" << setw(15) << "Science"
             << setw(15) << "Moral";
        if (termChoice == 3)
        {
            cout << setw(15) << "Attendance";
        }
        cout << endl;

        for (const auto &student : students)
        {
            if (student.studentClass == classToView)
            {
                cout << setw(15) << student.studentId;
                for (int i = gradeOffset; i < gradeOffset + 7; ++i)
                {
                    if (student.grades[i] == -1)
                    {
                        cout << setw(15) << "-";
                    }
                    else
                    {
                        if (student.grades[i] < 40.0f)
                        {
                            cout << "\033[1;31m";
                        }
                        else
                        {
                            cout << "\033[1;32m";
                        }
                        cout << setw(15) << static_cast<int>(student.grades[i]) << "\033[0m";
                    }
                }
                if (termChoice == 3)
                {
                    if (student.attendancePercentage == -1)
                    {
                        cout << setw(15) << "-";
                    }
                    else
                    {
                        if (student.attendancePercentage < 80.0f)
                        {
                            cout << "\033[1;31m";
                        }
                        else
                        {
                            cout << "\033[1;32m";
                        }
                        cout << student.attendancePercentage << "%\033[0m";
                    }
                }
                cout << endl;
            }
        }
        cout << "---------------------------------------------------------------------------------------------------------------------------------------" << endl;
        system("pause");
        system("cls");
    }

    void student_attendance_and_grades()
    {
        vector<StudentInfo> students;
        loadStudentGradeAttendance("gradeAttendance.txt", students);

        cout << "=======================================================================================================" << endl;
        cout << "                                       View Grades and Attendance" << endl;
        cout << "=======================================================================================================" << endl;
        string studentId;
        cout << "    Enter the student ID : ";
        cin >> studentId;

        auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                          { return s.studentId == studentId; });
        if (it == students.end() || it->studentClass != this->m_class)
        {
            do
            {
                cout << "\033[1;31m    Student not found or not in your class.Please make sure you enter the correct student id. \033[0m" << endl;
                cout << "=======================================================================================================" << endl;
                cout << "    Enter the correct student ID : ";
                cin >> studentId;
                it = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                             { return s.studentId == studentId; });
            } while (it == students.end() || it->studentClass != this->m_class);
            system("cls");
        }
        system("cls");
        cout << "============================================================================" << endl;
        cout << "                       STUDENT MARKS AND ATTENDANCE                         " << endl;
        cout << "============================================================================" << endl;
        cout << "    ID   : " << left << setw(30) << it->studentId << "Class  : " << it->studentClass << endl;

        string subjects[7] = {"Bahasa Melayu", "English", "Mandarin", "Mathematics", "History", "Science", "Moral"};

        string terms[3] = {"First Term Exam", "Midterm Exam", "Final Exam"};
        float totalMarks = 0.0f;
        float totalPossibleMarks = 0.0f;
        const int widths[] = {18, 12, 13, 16, 12, 12, 10};
        const int secondwidths[] = {8, 14, 13, 10, 14, 14, 16};
        const int thirdwidths[] = {6, 6, 6, 6, 6, 6, 6};

        for (int term = 0; term < 3; ++term)
        {
            cout << "----------------------------------------------------------------------------" << endl;
            cout << "                       \033[1;34m" << "Marks for " << terms[term] << "\033[0m" << endl;
            cout << "----------------------------------------------------------------------------" << endl;
            cout << "    No.  " << left << setw(35) << "Subject" << setw(10) << "Marks" << setw(10) << "Grades " << endl;
            int gradeOffset = term * 7;

            for (int i = 0; i < 7; ++i)
            {
                float grade = it->grades[gradeOffset + i];
                totalMarks += grade;
                totalPossibleMarks += 100.0f;

                cout << "    " << i + 1 << ".   " << setw(36) << subjects[i] << setw(11);
                if (grade == -1)
                {
                    cout << "-";
                }
                else
                {
                    cout << grade;
                }
                cout << setw(10) << getGradeLetter(grade) << endl;
            }
        }
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "Attendance : ";
        if (it->attendancePercentage == -1)
        {
            cout << "-";
        }
        else
        {
            if (it->attendancePercentage < 80.0f)
            {
                cout << "\033[1;31m";
            }
            else
            {
                cout << "\033[1;32m";
            }
            cout << it->attendancePercentage << "%" << "\033[0m";
        }
        cout << endl;
        cout << "============================================================================" << endl;

        system("pause");
        system("cls");
    }

    void update_student_comment()
    {
        vector<StudentInfo> students;
        loadStudentGradeAttendance("gradeAttendance.txt", students);
        loadStudentComments("comment.txt", students);

        cout << "============================================================================" << endl;
        cout << "                           UPDATE STUDENT COMMENT" << endl;
        cout << "============================================================================" << endl;
        cout << "    Enter the student ID : ";
        string studentId;
        cin >> studentId;

        auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                          { return s.studentId == studentId; });

        if (it == students.end() || it->studentClass != this->m_class)
        {
            do
            {
                cout << "\033[1;31m    Student not found or not in your class. Please try again. \033[0m" << endl;
                cout << "============================================================================" << endl;
                cout << "    Enter the correct student ID : ";
                cin >> studentId;
                it = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                             { return s.studentId == studentId; });
            } while (it == students.end() || it->studentClass != this->m_class);
        }

        system("cls");
        cout << "============================================================================" << endl;
        cout << "                           UPDATE STUDENT COMMENT" << endl;
        cout << "============================================================================" << endl;
        cout << "    Current comments for " << studentId << " :" << endl;
        it->comments.printComments();

        cout << "----------------------------------------------------------------------------" << endl;
        cout << "    [1] Add a new comment" << endl;
        cout << "    [2] Delete an existing comment" << endl;
        cout << "    [3] Back to Main Menu" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "    Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "    Enter the new comment or press Enter to skip: ";
            string newComment;
            getline(cin, newComment);

            if (!newComment.empty())
            {
                it->comments.addComment(newComment);
                saveStudentComments(students, "comment.txt");
                cout << "\033[1;32m    Comment added successfully. \033[0m" << endl;
            }
            else
            {
                cout << "\033[1;32m    Update skipped.\033[0m" << endl;
            }
        }
        else if (choice == 2)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "    Enter the comment to delete or press Enter to skip: ";
            string deleteComment;
            getline(cin, deleteComment);

            if (!deleteComment.empty())
            {
                if (it->comments.deleteComment(deleteComment))
                {
                    saveStudentComments(students, "comment.txt");
                    cout << "\033[1;32m    Comment deleted successfully. \033[0m" << endl;
                }
                else
                {
                    cout << "\033[1;31m    Comment not found. \033[0m" << endl;
                }
            }
            else
            {
                cout << "\033[1;32m    Deletion skipped.\033[0m" << endl;
            }
        }
        else if (choice == 3)
        {
            system("cls");
            return;
        }

        system("pause");
        system("cls");
    }

    void manage_student_awards()
    {
        vector<StudentInfo> students;
        loadStudentGradeAttendance("gradeAttendance.txt", students);
        loadStudentAwards("awards.txt", students);

        cout << "============================================================================" << endl;
        cout << "                           MANAGE STUDENT AWARDS" << endl;
        cout << "============================================================================" << endl;
        cout << "    Enter the student ID : ";
        string studentId;
        cin >> studentId;

        auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                          { return s.studentId == studentId; });

        if (it == students.end() || it->studentClass != this->m_class)
        {
            do
            {
                cout << "\033[1;31m    Student not found or not in your class. Please try again. \033[0m" << endl;
                cout << "============================================================================" << endl;
                cout << "    Enter the correct student ID : ";
                cin >> studentId;
                it = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                             { return s.studentId == studentId; });
            } while (it == students.end() || it->studentClass != this->m_class);
        }

        system("cls");
        cout << "============================================================================" << endl;
        cout << "                           MANAGE STUDENT AWARDS" << endl;
        cout << "============================================================================" << endl;
        cout << "    Current awards for " << studentId << " :" << endl;
        it->awards.printAwards();

        cout << "----------------------------------------------------------------------------" << endl;
        cout << "    [1] Add a new award" << endl;
        cout << "    [2] Delete an existing award" << endl;
        cout << "    [3] Back to Main Menu" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "    Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "    Enter the new award or press Enter to skip: ";
            string newAward;
            getline(cin, newAward);

            if (!newAward.empty())
            {
                it->awards.addAward(newAward);
                saveStudentAwards(students, "awards.txt");
                cout << "\033[1;32m    Award added successfully. \033[0m" << endl;
            }
            else
            {
                cout << "\033[1;32m    Update skipped.\033[0m" << endl;
            }
        }
        else if (choice == 2)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "    Enter the award to delete or press Enter to skip: ";
            string deleteAward;
            getline(cin, deleteAward);

            if (!deleteAward.empty())
            {
                if (it->awards.deleteAward(deleteAward))
                {
                    saveStudentAwards(students, "awards.txt");
                    cout << "\033[1;32m    Award deleted successfully. \033[0m" << endl;
                }
                else
                {
                    cout << "\033[1;31m    Award not found. \033[0m" << endl;
                }
            }
            else
            {
                cout << "\033[1;32m    Deletion skipped.\033[0m" << endl;
            }
        }
        else if (choice == 3)
        {
            system("cls");
            return;
        }

        system("pause");
        system("cls");
    }
};

class Student : public Identity
{

    friend class Teacher;

public:
    Student()
    {
        ;
    }

    ~Student()
    {
        ;
    }

    Student(string user_type, string user_id, string user_name, string user_password, string user_gender, string user_class)
    {
        this->m_type = user_type;
        this->m_id = user_id;
        this->m_name = user_name;
        this->m_password = user_password;
        this->m_gender = user_gender;
        this->m_class = user_class;
    }

    void open_menu()
    {
        int choice = 0;
        do
        {
            cout << "============================================================================" << endl;
            cout << "                               STUDENT MENU                                 " << endl;
            cout << "============================================================================" << endl;
            cout << right << setw(55) << "Welcome, " << this->m_name << endl;
            cout << "    [1] View Exam Result Slip" << endl;
            cout << "    [2] View Report Card" << endl;
            cout << "    [3] Logout" << endl;
            cout << "============================================================================" << endl;
        RECHOICE:
            cout << "    Please Enter Your Choice: ";
            cin >> choice;
            if (cin.fail())
            {
                cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto RECHOICE;
            }

            switch (choice)
            {
            case 1:
                system("cls");
                view_exam_result_slip();
                break;
            case 2:
                system("cls");
                view_report_card();
                break;
            case 3:
                return;
            default:
                cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
                goto RECHOICE;
            }
        } while (true);
        return;
    }

    void view_exam_result_slip()
    {
        vector<StudentInfo> students;
        Teacher::loadStudentGradeAttendance("gradeAttendance.txt", students);

        auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                          { return s.studentId == this->m_id; });
        if (it == students.end())
        {
            cout << "\033[1;31m    Student data not found. \033[0m" << endl;
            return;
        }
        int termChoice;
        int gradeOffset;
        float termTotalMarks = 0.0f;
        float termTotalPossibleMarks = 0.0f;

        cout << "============================================================================" << endl;
        cout << "                             VIEW EXAM RESULT SLIP " << endl;
        cout << "============================================================================" << endl;
        cout << "    Select the term to update marks" << endl;
        cout << "    [1] First Term Exam" << endl;
        cout << "    [2] Midterm Exam" << endl;
        cout << "    [3] Final Exam" << endl;
        cout << "    [4] Back to Main Menu" << endl;
        cout << "===========================================================================" << endl;
        while (true)
        {
            cout << "    Enter your choice : ";
            cin >> termChoice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "\033[1;31m    Invalid input. Please try again.\033[0m" << endl;
            }
            else
            {
                switch (termChoice)
                {
                case 1:
                    gradeOffset = 0;
                    break;
                case 2:
                    gradeOffset = 7;
                    break;
                case 3:
                    gradeOffset = 14;
                    break;
                case 4:
                    system("pause");
                    system("cls");
                    return;
                default:
                    cout << "\033[1;31m    Invalid choice. Please enter a valid option (1, 2, or 3).\033[0m" << endl;
                    continue;
                }
                break;
            }
        }
        for (int i = 0; i < 7; ++i)
        {
            float grade = it->grades[gradeOffset + i];
            if (grade != -1)
            {
                termTotalMarks += grade;
                termTotalPossibleMarks += 100.0f;
            }
        }

        cin.clear();
        system("cls");
        cout << "============================================================================" << endl;
        cout << "                              EXAM RESULT SLIP                              " << endl;
        cout << "============================================================================" << endl;
        cout << "    Name : " << left << setw(30) << this->m_name << "Gender : " << this->m_gender << endl;
        cout << "    ID   : " << left << setw(30) << this->m_id << "Class  : " << this->m_class << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "\033[1;34m                         Marks for " << (termChoice == 1 ? "First Term Exam" : termChoice == 2 ? "Midterm Exam"
                                                                                                                          : "Final Exam")
             << "\033[0m" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "    No.  " << left << setw(35) << "Subject" << setw(10) << "Marks" << setw(10) << "Grades " << endl;
        cout << "    1.   " << left << setw(36) << "Bahasa Melayu" << setw(11) << (it->grades[gradeOffset + 0] == -1 ? "-" : to_string(static_cast<int>(it->grades[gradeOffset + 0]))) << setw(10) << getGradeLetter(it->grades[gradeOffset + 0]) << endl;
        cout << "    2.   " << left << setw(36) << "English" << setw(11) << (it->grades[gradeOffset + 1] == -1 ? "-" : to_string(static_cast<int>(it->grades[gradeOffset + 1]))) << setw(10) << getGradeLetter(it->grades[gradeOffset + 1]) << endl;
        cout << "    3.   " << left << setw(36) << "Mandarin" << setw(11) << (it->grades[gradeOffset + 2] == -1 ? "-" : to_string(static_cast<int>(it->grades[gradeOffset + 2]))) << setw(10) << getGradeLetter(it->grades[gradeOffset + 2]) << endl;
        cout << "    4.   " << left << setw(36) << "Mathematics" << setw(11) << (it->grades[gradeOffset + 3] == -1 ? "-" : to_string(static_cast<int>(it->grades[gradeOffset + 3]))) << setw(10) << getGradeLetter(it->grades[gradeOffset + 3]) << endl;
        cout << "    5.   " << left << setw(36) << "History" << setw(11) << (it->grades[gradeOffset + 4] == -1 ? "-" : to_string(static_cast<int>(it->grades[gradeOffset + 4]))) << setw(10) << getGradeLetter(it->grades[gradeOffset + 4]) << endl;
        cout << "    6.   " << left << setw(36) << "Science" << setw(11) << (it->grades[gradeOffset + 5] == -1 ? "-" : to_string(static_cast<int>(it->grades[gradeOffset + 5]))) << setw(10) << getGradeLetter(it->grades[gradeOffset + 5]) << endl;
        cout << "    7.   " << left << setw(36) << "Moral" << setw(11) << (it->grades[gradeOffset + 6] == -1 ? "-" : to_string(static_cast<int>(it->grades[gradeOffset + 6]))) << setw(10) << getGradeLetter(it->grades[gradeOffset + 6]) << endl;
        cout << "----------------------------------------------------------------------------" << endl;

        float termPercentage = (termTotalPossibleMarks > 0.0f) ? ((termTotalMarks / termTotalPossibleMarks) * 100.0f) : -1.0f;

        cout << "    Total marks for " << (termChoice == 1 ? "First Term Exam" : termChoice == 2 ? "Midterm Exam"
                                                                                                 : "Final Exam")
             << " : " << termTotalMarks << "/" << termTotalPossibleMarks << endl;
        cout << "    Percentage for " << (termChoice == 1 ? "First Term Exam" : termChoice == 2 ? "Midterm Exam"
                                                                                                : "Final Exam")
             << "  : ";

        if (termPercentage == -1.0f)
        {
            cout << "-" << endl;
        }
        else if (termPercentage < 50.0f)
        {
            cout << " \033[1;31m";
            cout << fixed << setprecision(0) << termPercentage << "%" << "\033[0m" << endl;
        }
        else
        {
            cout << " \033[1;32m";
            cout << fixed << setprecision(0) << termPercentage << "%" << "\033[0m" << endl;
        }

        cout << "----------------------------------------------------------------------------" << endl;
        system("pause");
        system("cls");
    }

    void view_report_card()
    {
        vector<StudentInfo> students;
        Teacher::loadStudentGradeAttendance("gradeAttendance.txt", students);
        Teacher::loadStudentComments("comment.txt", students);
        Teacher::loadStudentAwards("awards.txt", students);

        auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                          { return s.studentId == this->m_id; });

        if (it == students.end())
        {
            cout << "\033[1;31m    Student data not found. \033[0m" << endl;
            return;
        }

        cout << "========================================================================================" << endl;
        cout << "                                       REPORT CARD" << endl;
        cout << "========================================================================================" << endl;
        cout << "    Name : " << left << setw(50) << this->m_name << "Gender : " << this->m_gender << endl;
        cout << "    ID   : " << left << setw(50) << this->m_id << "Class  : " << this->m_class << endl;

        string subjects[7] = {"Bahasa Melayu", "English", "Mandarin", "Mathematics", "History", "Science", "Moral"};
        string terms[3] = {"First Term Exam", "Midterm Exam", "Final Exam"};
        float totalMarks = 0.0f;
        float totalPossibleMarks = 0.0f;

        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "         " << left << setw(24) << " " << "| " << setw(15) << "\033[1;34mFirst Term Exam\033[0m " << "| " << setw(15) << " \033[1;34mMidterm Exam\033[0m" << "   | " << setw(15) << "   \033[1;34mFinal Exam\033[0m" << "   |" << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "    No.  " << left << setw(24) << "Subject" << "| " << setw(9) << "Marks" << setw(7) << "Grades" << "| " << setw(9) << "Marks" << setw(7) << "Grades " << "| " << setw(9) << "Marks" << setw(7) << "Grades " << "|" << endl;

        float termTotalMarks[3] = {0.0f};
        float termTotalPossibleMarks[3] = {0.0f};

        for (int i = 0; i < 7; ++i)
        {
            cout << "    " << i + 1 << ".   " << left << setw(24) << subjects[i];

            for (int term = 0; term < 3; ++term)
            {
                int gradeOffset = term * 7;
                float grade = it->grades[gradeOffset + i];

                if (grade != -1)
                {
                    termTotalMarks[term] += grade;
                    termTotalPossibleMarks[term] += 100.0f;
                }

                cout << "|  " << setw(10) << (grade == -1 ? "-" : to_string(static_cast<int>(grade))) << setw(5) << getGradeLetter(grade);
            }

            cout << "|" << endl;
        }

        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "\033[0m    Total Mark                   ";
        for (int term = 0; term < 3; ++term)
        {
            cout << "|    " << termTotalMarks[term] << "/" << termTotalPossibleMarks[term] << "      ";
        }
        cout << "|";
        cout << "\033[0m" << endl;

        cout << "    Percentage                  ";

        for (int term = 0; term < 3; ++term)
        {
            float percentage = (termTotalMarks[term] / termTotalPossibleMarks[term]) * 100.0f;

            cout << " |   ";
            if (percentage < 50.0f)
            {
                cout << " \033[1;31m";
            }
            else
            {
                cout << " \033[1;32m";
            }
            cout << fixed << "  " << setprecision(0) << percentage << "%      " << "\033[0m ";
        }
        cout << " |" << endl;

        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "    Attendance  : ";
        if (it->attendancePercentage == -1)
        {
            cout << "-";
        }
        else
        {
            if (it->attendancePercentage < 80.0f)
            {
                cout << "\033[1;31m";
            }
            else
            {
                cout << "\033[1;32m";
            }
            cout << it->attendancePercentage << "%" << "\033[0m" << endl;
        }
        cout << "    Teacher's Comments : " << endl;
        it->comments.printComments();
        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "    Awards : " << endl;
        it->awards.printAwards();
        cout << "-----------------------------------------------------------------------------------------" << endl;
        system("pause");
        system("cls");
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
};

class Admin : public Identity
{
public:
    Admin() { ; }

    ~Admin() { ; }

    Admin(string name, string password)
    {
        this->m_name = name;
        this->m_password = password;
        this->init_vector();
        loadSubjects("subjects.txt");
    }

    void open_menu() override
    {
        int choice = 0;
        do
        {
            cout << "============================================================================" << endl;
            cout << "                                 ADMIN MENU                                 " << endl;
            cout << "============================================================================" << endl;
            cout << right << setw(60) << "Welcome, " << this->m_name << endl;
            cout << "    [1] Activate New Account" << endl;
            cout << "    [2] Deactivate Exist Account" << endl;
            cout << "    [3] Edit User Profile" << endl;
            cout << "    [4] View Teacher or Student List" << endl;
            cout << "    [5] View All Classes List" << endl;
            cout << "    [6] Add Subject" << endl;
            cout << "    [7] Delete Subject" << endl;
            cout << "    [8] View Subjects" << endl;
            cout << "    [9] Logout" << endl;
            cout << "============================================================================" << endl;
        RECHOICE:
            cout << "    Please Enter Your Choice: ";
            cin >> choice;
            if (cin.fail())
            {
                cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto RECHOICE;
            }

            switch (choice)
            {
            case 1:
                system("cls");
                activate_new_account();
                break;
            case 2:
                system("cls");
                deactivate_exist_account();
                break;
            case 3:
                system("cls");
                edit_user_profile();
                break;
            case 4:
                system("cls");
                view_teacher_or_student_list();
                break;
            case 5:
                system("cls");
                view_all_classes_list();
                break;
            case 6:
                system("cls");
                add_subject();
                break;
            case 7:
                system("cls");
                delete_subject();
                break;
            case 8:
                system("cls");
                view_subjects();
                break;
            case 9:
                saveSubjects("subjects.txt");
                return;
            default:
                cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
                goto RECHOICE;
            }
        } while (true);
        return;
    }

private:
    void display_teacher_details(const Teacher &teacher)
    {
        cout << "============================================================================" << endl;
        cout << "                           EDIT TEACHER PROFILE                             " << endl;
        cout << "============================================================================" << endl;
        cout << "    Name     : " << left << setw(30) << teacher.m_name << "Gender : " << setw(15) << teacher.m_gender << endl;
        cout << "    Password : " << left << setw(30) << teacher.m_password << "Class  : " << setw(15) << teacher.m_class << endl;
    }

    void display_student_details(const Student &student)
    {
        cout << "============================================================================" << endl;
        cout << "                           EDIT STUDENT PROFILE                             " << endl;
        cout << "============================================================================" << endl;
        cout << "    Name     : " << left << setw(30) << student.m_name << "Gender : " << setw(15) << student.m_gender << endl;
        cout << "    Password : " << left << setw(30) << student.m_password << "Class  : " << setw(15) << student.m_class << endl;
    }

    void edit_user_profile()
    {
        int edit_choice;
        int choice;
        string user_id;
        bool userFound = false;

        vector<Teacher>::iterator itTea;
        vector<Student>::iterator itStu;

    EDITUSERPROFILEMENU:
        cout << "============================================================================" << endl;
        cout << "                              EDIT USER PROFILE                             " << endl;
        cout << "============================================================================" << endl;
        cout << "    What user type would you like to edit?" << endl;
        cout << "    [1] Edit Teacher Profile" << endl;
        cout << "    [2] Edit Student Profile" << endl;
        cout << "    [3] Back to Main Menu" << endl;
        cout << "============================================================================" << endl;
    RECHOICE:
        cout << "    Please Enter Your Choice: ";
        cin >> choice;
        if (cin.fail())
        {
            cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto RECHOICE;
        }
        else if (choice < 1 || choice > 3)
        {
            cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
            goto RECHOICE;
        }
        else if (choice == 3)
        {
            cout << "\033[1;32m    Returned Successfully.\033[0m" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            if (choice == 1)
            {
                cout << "    Please Enter Teacher ID: ";
                cin >> user_id;
                itTea = find_if(vTea.begin(), vTea.end(), [&](const Teacher &t)
                                { return t.m_id == user_id; });
                userFound = itTea != vTea.end();
            }
            else
            {
                cout << "    Please Enter Student ID: ";
                cin >> user_id;
                itStu = find_if(vStu.begin(), vStu.end(), [&](const Student &s)
                                { return s.m_id == user_id; });
                userFound = itStu != vStu.end();
            }
        }

        if (!userFound)
        {
            cout << "\033[1;31m    User not found. Please Reenter Choice.\033[0m" << endl;
            goto RECHOICE;
        }

        system("cls");

        do
        {
            if (choice == 1)
            {
                display_teacher_details(*itTea);
            }
            else
            {
                display_student_details(*itStu);
            }
            cout << "----------------------------------------------------------------------------" << endl;
            cout << "    What profile type would you like to edit?" << endl;
            cout << "    [1] Edit User Name" << endl;
            cout << "    [2] Reset User Password" << endl;
            cout << "    [3] Edit User Gender" << endl;
            cout << "    [4] Edit User Class" << endl;
            cout << "    [5] Cancel" << endl;
            cout << "============================================================================" << endl;

        EDITRECHOICE:
            cout << "    Please Enter Your Choice: ";
            cin >> edit_choice;
            if (cin.fail())
            {
                cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto EDITRECHOICE;
            }
            cin.ignore();

            if (edit_choice < 1 || edit_choice > 5)
            {
                cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
                goto EDITRECHOICE;
            }

            if (edit_choice == 5)
            {
                cout << "\033[1;32m    Cancel Successfully.\033[0m" << endl;
                system("pause");
                system("cls");
                goto EDITUSERPROFILEMENU;
            }

            string newValue;
            cout << "    Please Enter New Value: ";
            getline(cin, newValue);

            if (choice == 1 && userFound)
            {
                switch (edit_choice)
                {
                case 1:
                    itTea->m_name = newValue;
                    break;
                case 2:
                    itTea->m_password = newValue;
                    break;
                case 3:
                    while (newValue != "Male" && newValue != "Female")
                    {
                        cout << "\033[1;31m    Invalid Input. Please Enter Male or Female.\033[0m" << endl;
                        cout << "    Please Enter New Gender: ";
                        getline(cin, newValue);
                    }
                    itTea->m_gender = newValue;
                    break;
                case 4:
                    itTea->m_class = newValue;
                    break;
                }
            }
            else if (choice == 2 && userFound)
            {
                switch (edit_choice)
                {
                case 1:
                    itStu->m_name = newValue;
                    break;
                case 2:
                    itStu->m_password = newValue;
                    break;
                case 3:
                    while (newValue != "Male" && newValue != "Female")
                    {
                        cout << "\033[1;31m    Invalid Input. Please Enter Male or Female.\033[0m" << endl;
                        cout << "    Please Enter New Gender: ";
                        getline(cin, newValue);
                    }
                    itStu->m_gender = newValue;
                    break;
                case 4:
                    itStu->m_class = newValue;
                    updateCommentFile(itStu->m_id, itStu->m_class);
                    updateGradeAttendanceFile(itStu->m_id, itStu->m_class);
                    break;
                }
            }

            update_user_file();
            cout << "\033[1;32m    User Profile Updated Successfully.\033[0m" << endl;
            system("pause");
            system("cls");
        } while (edit_choice != 5);
    }

    void activate_new_account()
    {
        int choice;
        char confirm;
        string user_id, user_name, user_password, user_gender, user_class;
        string prompt;
        string error_prompt;

        do
        {
            cout << "============================================================================" << endl;
            cout << "                            ACTIVATE NEW ACCOUNT                            " << endl;
            cout << "============================================================================" << endl;
            cout << "    What user type would you like to activate?" << endl;
            cout << "    [1] Activate Teacher Account" << endl;
            cout << "    [2] Activate Student Account" << endl;
            cout << "    [3] Back to Main Menu" << endl;
            cout << "============================================================================" << endl;

        RECHOICE:
            cout << "    Please Enter Your Choice: ";
            cin >> choice;
            if (cin.fail())
            {
                cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto RECHOICE;
            }

            if (choice == 3)
            {
                cout << "\033[1;32m    Returned Successfully.\033[0m" << endl;
                system("pause");
                system("cls");
                return;
            }

            ofstream ofs;
            ofs.open("user.txt", ios::out | ios::app);

            int user_type = choice;

            cout << "----------------------------------------------------------------------------" << endl;
            switch (choice)
            {
            case 1:
                cout << "    Please Enter Teacher Profile" << endl;
                prompt = "    Teacher ID\t\t: ";
                error_prompt = "\033[1;31m    Teacher ID Duplicated. Please Enter Again.\033[0m";
                break;
            case 2:
                cout << "    Please Enter Student Profile" << endl;
                prompt = "    Student ID\t\t: ";
                error_prompt = "\033[1;31m    Student ID Duplicated. Please Enter Again.\033[0m";
                break;
            default:
                cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
                goto RECHOICE;
            }
            cout << prompt;

            while (true)
            {
                cin >> user_id;
                bool ret = check_repeat(user_id, user_type);
                if (ret)
                {
                    cout << error_prompt << endl;
                    cout << prompt;
                }
                else
                {
                    break;
                }
            }

            if (choice == 1)
            {
                cin.ignore();
                cout << "    Teacher Name\t: ";
                getline(cin, user_name);
                cout << "    Teacher Password\t: ";
                getline(cin, user_password);

                do
                {
                    cout << "    Teacher Gender\t: ";
                    getline(cin, user_gender);
                    if (user_gender != "Male" && user_gender != "Female")
                    {
                        cout << "\033[1;31m    Invalid Input. Please Enter Male or Female.\033[0m" << endl;
                    }
                } while (user_gender != "Male" && user_gender != "Female");

                cout << "    Teacher Class\t: ";
                getline(cin, user_class);
            }
            else if (choice == 2)
            {
                cin.ignore();
                cout << "    Student Name\t: ";
                getline(cin, user_name);
                cout << "    Student Password\t: ";
                getline(cin, user_password);
                do
                {
                    cout << "    Student Gender\t: ";
                    getline(cin, user_gender);
                    if (user_gender != "Male" && user_gender != "Female")
                    {
                        cout << "\033[1;31m    Invalid Input. Please Enter Male or Female.\033[0m" << endl;
                    }
                } while (user_gender != "Male" && user_gender != "Female");
                cout << "    Student Class\t: ";
                getline(cin, user_class);
            }
            cout << "----------------------------------------------------------------------------" << endl;
            cout << "\033[1;33m    Are you sure you want to activate this user account?(Y/N): \033[0m";
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y')
            {
                if (ofs.is_open())
                {
                    stringstream ss;
                    ss << user_type << "|" << user_id << "|" << user_name << "|" << user_password << "|" << user_gender << "|" << user_class << endl;

                    ofs << ss.str();
                    ofs.close();
                    cout << "\033[1;32m    User Added Successfully. Returning to Rechoice\033[0m" << endl;

                    if (user_type == 2)
                    {
                        ofstream gradeFile("gradeAttendance.txt", ios::out | ios::app);
                        if (gradeFile.is_open())
                        {
                            vector<string> subjectCodes;
                            ifstream subjectsFile("subjects.txt");
                            if (subjectsFile.is_open())
                            {
                                string line;
                                while (getline(subjectsFile, line))
                                {
                                    stringstream ss(line);
                                    string subjectCode, subjectName, className;
                                    getline(ss, subjectCode, '|');
                                    getline(ss, subjectName, '|');
                                    while (getline(ss, className, '|'))
                                    {
                                        if (className == user_class)
                                        {
                                            subjectCodes.push_back(subjectCode);
                                        }
                                    }
                                }
                                subjectsFile.close();
                            }
                            gradeFile << user_id << "|" << user_class;
                            for (size_t i = 0; i < subjectCodes.size(); ++i)
                            {
                                gradeFile << "|-1";
                            }
                            gradeFile << "|0" << endl;
                            gradeFile.close();
                        }
                        else
                        {
                            cout << "Unable to open gradeAttendance.txt for writing" << endl;
                        }

                        ofstream commentFile("comment.txt", ios::out | ios::app);
                        if (commentFile.is_open())
                        {
                            commentFile << user_id << "|" << user_class << "|null" << endl;
                            commentFile.close();
                        }
                        else
                        {
                            cout << "Unable to open comment.txt for writing" << endl;
                        }
                    }

                    this->init_vector();
                    system("pause");
                    system("cls");
                }
                else
                {
                    cout << "File does not exist" << endl;
                    ofs.close();
                    return;
                }
            }
            else
            {
                cout << "\033[1;33m    This user account is not activated.\033[0m" << endl;
                system("pause");
                system("cls");
            }
        } while (choice != 3);
        return;
    }

    void deactivate_exist_account()
    {
        int choice;
        string user_id;
        bool found = false;
        char confirm;

        do
        {
            cout << "============================================================================" << endl;
            cout << "                         DEACTIVATE EXIST ACCOUNT                           " << endl;
            cout << "============================================================================" << endl;
            cout << "    What user type would you like to deactivate?" << endl;
            cout << "    [1] Deactivate Teacher Account" << endl;
            cout << "    [2] Deactivate Student Account" << endl;
            cout << "    [3] Back to Main Menu" << endl;
            cout << "============================================================================" << endl;

        RECHOICE:
            cout << "    Please Enter Your Choice: ";
            cin >> choice;
            if (cin.fail())
            {
                cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto RECHOICE;
            }

            if (choice == 1)
            {
                cout << "    Please Enter Teacher ID: ";
                cin >> user_id;
                auto it = remove_if(vTea.begin(), vTea.end(), [&](const Teacher &t)
                                    { return t.m_id == user_id; });
                if (it != vTea.end())
                {
                    vTea.erase(it, vTea.end());
                    found = true;
                }
                else
                {
                    found = false;
                }
            }
            else if (choice == 2)
            {
                cout << "    Please Enter Student ID: ";
                cin >> user_id;
                auto it = remove_if(vStu.begin(), vStu.end(), [&](const Student &s)
                                    { return s.m_id == user_id; });
                if (it != vStu.end())
                {
                    vStu.erase(it, vStu.end());
                    found = true;
                }
                else
                {
                    found = false;
                }
            }
            else if (choice == 3)
            {
                cout << "\033[1;32m    Returned Successfully.\033[0m" << endl;
                system("pause");
                system("cls");
                return;
            }

            else
            {
                cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
                goto RECHOICE;
            }

            if (found == true)
            {
                cout << "\033[1;33m    Are you sure you want to deactivate this user account?(Y/N): \033[0m";
                cin >> confirm;
                if (confirm == 'Y' || confirm == 'y')
                {
                    update_user_file();
                    this->init_vector();

                    if (choice == 2)
                    {
                        removeStudentData(user_id, "gradeAttendance.txt");
                        removeStudentData(user_id, "comment.txt");
                    }

                    cout << "\033[1;32m    User Removed Sucessfully.\033[0m" << endl;
                    system("pause");
                    system("cls");
                }
                else
                {
                    cout << "\033[1;33m    This user account is not deactivated.\033[0m" << endl;
                    system("pause");
                    system("cls");
                }
            }
            else
            {
                cout << "\033[1;31m    User Not Found. Please Enter again.\033[0m" << endl;
                goto RECHOICE;
            }
        } while (choice != 3);
    }

    void removeStudentData(const string &studentId, const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Unable to open " << filename << " for reading" << endl;
            return;
        }

        vector<string> lines;
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id;
            getline(ss, id, '|');
            if (id != studentId)
            {
                lines.push_back(line);
            }
        }
        file.close();

        ofstream outFile(filename);
        if (!outFile.is_open())
        {
            cout << "Unable to open " << filename << " for writing" << endl;
            return;
        }

        for (const auto &l : lines)
        {
            outFile << l << "\n";
        }
        outFile.close();
    }

    void print_teacher(Teacher &t)
    {
        cout << "    " << left << setw(15) << t.m_id << setw(30) << t.m_name << setw(20) << t.m_password << endl;
    }

    void print_student(Student &s)
    {
        cout << "    " << left << setw(15) << s.m_id << setw(30) << s.m_name << setw(20) << s.m_password << endl;
    }

    void view_teacher_or_student_list()
    {
        int choice;

        do
        {
            cout << "============================================================================" << endl;
            cout << "                      VIEW TEACHER OR STUDENT LIST                          " << endl;
            cout << "============================================================================" << endl;
            cout << "    Which list of user types list would you like to view?" << endl;
            cout << "    [1] View Teacher List" << endl;
            cout << "    [2] View Student List" << endl;
            cout << "    [3] Back to Main Menu" << endl;
            cout << "============================================================================" << endl;

        RECHOICE:
            cout << "    Please Enter Your Choice: ";
            cin >> choice;
            if (cin.fail())
            {
                cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto RECHOICE;
            }

            if (choice == 1)
            {
                system("cls");
                cout << "============================================================================" << endl;
                cout << "                                TEACHER LIST                                " << endl;
                cout << "============================================================================" << endl;
                cout << "    " << left << setw(15) << "Teacher ID" << setw(30) << "Name" << setw(20) << "Password" << endl;
                for (auto &teacher : vTea)
                {
                    print_teacher(teacher);
                }

                cout << "\n    " << "Total Number of Teacher in this system : " << vTea.size() << endl;
                cout << "----------------------------------------------------------------------------" << endl;
                system("pause");
                system("cls");
            }

            else if (choice == 2)
            {
                system("cls");
                cout << "============================================================================" << endl;
                cout << "                                STUDENT LIST                                " << endl;
                cout << "============================================================================" << endl;
                cout << "    " << left << setw(15) << "Student ID" << setw(30) << "Name" << setw(20) << "Password" << endl;
                for (auto &student : vStu)
                {
                    print_student(student);
                }

                cout << "\n    " << "Total Number of Student in this system : " << vStu.size() << endl;
                cout << "----------------------------------------------------------------------------" << endl;
                system("pause");
                system("cls");
            }

            else if (choice == 3)
            {
                cout << "\033[1;32m    Returned Successfully.\033[0m" << endl;
                system("pause");
                system("cls");
                return;
            }

            else
            {
                cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
                goto RECHOICE;
            }
        } while (choice != 3);
    }

    void view_all_classes_list()
    {
        vector<string> classes;
        for (const auto &teacher : vTea)
        {
            if (find(classes.begin(), classes.end(), teacher.m_class) == classes.end())
            {
                classes.push_back(teacher.m_class);
            }
        }

        int choice;
        do
        {
            cout << "============================================================================" << endl;
            cout << "                             VIEW ALL CLASSES LIST                          " << endl;
            cout << "============================================================================" << endl;
            cout << right << setw(70) << "Total Class: " << classes.size() << endl;
            cout << "    " << left << setw(10) << "Grade" << setw(10) << "Class" << setw(30) << "Teacher Name" << setw(20) << "Student Quantity" << endl;

            for (const auto &className : classes)
            {
                int grade = 0;
                if (isdigit(className[0]))
                {
                    grade = className[0] - '0';
                }

                int studentCount = count_if(vStu.begin(), vStu.end(), [&](const Student &s)
                                            { return s.m_class == className; });
                string teacherName = "Unknown";
                for (const auto &teacher : vTea)
                {
                    if (teacher.m_class == className)
                    {
                        teacherName = teacher.m_name;
                        break;
                    }
                }
                cout << "    " << left << setw(10) << grade << setw(10) << className << setw(30) << teacherName << setw(20) << studentCount << endl;
            }

            cout << "----------------------------------------------------------------------------" << endl;
            cout << "    [1] Sorting" << endl;
            cout << "    [2] Searching" << endl;
            cout << "    [3] Back to Menu" << endl;
            cout << "============================================================================" << endl;
            cout << "    Please Enter Your Choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                break;
            case 2:
                search_classes_or_teachers(classes);
                break;
            case 3:
                return;
            default:
                cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
            }
        } while (choice != 3);
    }

    void search_classes_or_teachers(const vector<string> &classes)
    {
        int searchChoice;
        cout << "============================================================================" << endl;
        cout << "                                 SEARCHING                                  " << endl;
        cout << "============================================================================" << endl;
        cout << "    [1] Search by Class" << endl;
        cout << "    [2] Search by Teacher Name" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "    Please Enter Your Choice: ";
        cin >> searchChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (searchChoice == 1)
        {
            string className;
            cout << "    Enter Class Name: ";
            getline(cin, className);

            auto it = find(classes.begin(), classes.end(), className);
            if (it != classes.end())
            {
                display_class_info(*it);
            }
            else
            {
                cout << "\033[1;31m    Class not found.\033[0m" << endl;
            }
        }
        else if (searchChoice == 2)
        {
            string teacherName;
            cout << "    Enter Teacher Name: ";
            getline(cin, teacherName);

            bool found = false;
            for (const auto &teacher : vTea)
            {
                if (teacher.m_name == teacherName)
                {
                    display_class_info(teacher.m_class);
                    found = true;
                }
            }
            if (!found)
            {
                cout << "\033[1;31m    Teacher not found.\033[0m" << endl;
            }
        }
        else
        {
            cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
        }

        system("pause");
        system("cls");
    }

    void display_class_info(const string &className)
    {
        int grade = 0;
        if (isdigit(className[0]))
        {
            grade = className[0] - '0';
        }

        int studentCount = count_if(vStu.begin(), vStu.end(), [&](const Student &s)
                                    { return s.m_class == className; });
        string teacherName = "Unknown";
        for (const auto &teacher : vTea)
        {
            if (teacher.m_class == className)
            {
                teacherName = teacher.m_name;
                break;
            }
        }

        cout << "============================================================================" << endl;
        cout << "                             CLASS INFORMATION                              " << endl;
        cout << "============================================================================" << endl;
        cout << "    " << left << setw(10) << "Grade" << setw(10) << "Class" << setw(30) << "Teacher Name" << setw(20) << "Student Quantity" << endl;
        cout << "    " << left << setw(10) << grade << setw(10) << className << setw(30) << teacherName << setw(20) << studentCount << endl;
        cout << "----------------------------------------------------------------------------" << endl;
    }

    void add_subject()
    {
        string subjectCode, subjectName;
        int classCount;
        char confirm;

        cout << "============================================================================" << endl;
        cout << "                                 ADD SUBJECT                                " << endl;
        cout << "============================================================================" << endl;

        bool subjectCodeDuplicated;
        do
        {
            subjectCodeDuplicated = false;
            cout << "    Enter Subject Code: ";
            cin >> subjectCode;

            if (check_repeat(subjectCode, 3))
            {
                subjectCodeDuplicated = true;
                cout << "\033[1;31m    Subject Code Duplicated. Please Enter Again.\033[0m" << endl;
            }
        } while (subjectCodeDuplicated);

        cout << "    Enter Subject Name: ";
        cin >> subjectName;
        cout << "    Enter Number of Classes: ";
        cin >> classCount;

        vector<string> classes(classCount);
        for (int i = 0; i < classCount; ++i)
        {
            cout << "    Enter Class " << i + 1 << ": ";
            cin >> classes[i];
        }

        cout << "----------------------------------------------------------------------------" << endl;
        cout << "    Subject Code: " << subjectCode << endl;
        cout << "    Subject Name: " << subjectName << endl;
        cout << "    Number of Classes: " << classCount << endl;
        for (int i = 0; i < classCount; ++i)
        {
            cout << "    Class " << i + 1 << ": " << classes[i] << endl;
        }
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "\033[1;33m    Are you sure you want to add this subject?(Y/N): \033[0m";
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y')
        {
            subjects.addSubject(subjectCode, subjectName, classes);
            saveSubjects("subjects.txt");
            cout << "\033[1;32m    Subject Added Successfully.\033[0m" << endl;

            reinitialize_grades_for_classes(classes);
        }
        else
        {
            cout << "\033[1;33m    Subject not added.\033[0m" << endl;
        }

        system("pause");
        system("cls");
    }

    void delete_subject()
    {
        string subjectCode;
        cout << "============================================================================" << endl;
        cout << "                                DELETE SUBJECT                              " << endl;
        cout << "============================================================================" << endl;
        cout << "    Enter Subject Code to Delete: ";
        cin >> subjectCode;

        SubjectNode *current = subjects.head;
        SubjectNode *prev = nullptr;
        bool found = false;

        while (current != nullptr)
        {
            if (current->subjectCode == subjectCode)
            {
                found = true;
                if (prev == nullptr)
                {
                    subjects.head = current->next;
                }
                else
                {
                    prev->next = current->next;
                }
                delete current;
                cout << "\033[1;32m    Subject Deleted Successfully.\033[0m" << endl;
                break;
            }
            prev = current;
            current = current->next;
        }

        if (!found)
        {
            cout << "\033[1;31m    Subject Code Not Found. Please Try Again.\033[0m" << endl;
        }
        else
        {
            saveSubjects("subjects.txt");
            reinitialize_grades_after_deletion(subjectCode);
        }

        system("pause");
        system("cls");
    }

    void reinitialize_grades_after_deletion(const string &deletedSubjectCode)
    {
        ifstream inFile("gradeAttendance.txt");
        if (!inFile.is_open())
        {
            cout << "Unable to open gradeAttendance.txt for reading" << endl;
            return;
        }

        vector<string> lines;
        string line;
        vector<string> subjectCodes;

        SubjectNode *current = subjects.head;
        while (current != nullptr)
        {
            subjectCodes.push_back(current->subjectCode);
            current = current->next;
        }

        while (getline(inFile, line))
        {
            stringstream ss(line);
            string studentId, studentClass;
            getline(ss, studentId, '|');
            getline(ss, studentClass, '|');

            vector<string> grades;
            string grade;
            while (getline(ss, grade, '|'))
            {
                grades.push_back(grade);
            }

            stringstream newLine;
            newLine << studentId << "|" << studentClass;

            size_t gradeIndex = 0;
            for (size_t i = 0; i < subjectCodes.size(); ++i)
            {
                if (subjectCodes[i] == deletedSubjectCode)
                {
                    gradeIndex += 3;
                    continue;
                }
                newLine << "|" << grades[gradeIndex] << "|" << grades[gradeIndex + 1] << "|" << grades[gradeIndex + 2];
                gradeIndex += 3;
            }
            newLine << "|" << grades.back();
            lines.push_back(newLine.str());
        }
        inFile.close();

        ofstream outFile("gradeAttendance.txt");
        if (!outFile.is_open())
        {
            cout << "Unable to open gradeAttendance.txt for writing" << endl;
            return;
        }

        for (const auto &l : lines)
        {
            outFile << l << "\n";
        }
        outFile.close();
    }

    void reinitialize_grades_for_classes(const vector<string> &classes)
    {
        ifstream inFile("gradeAttendance.txt");
        if (!inFile.is_open())
        {
            cout << "Unable to open gradeAttendance.txt for reading" << endl;
            return;
        }

        vector<string> lines;
        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string studentId, studentClass;
            getline(ss, studentId, '|');
            getline(ss, studentClass, '|');

            vector<float> grades;
            float grade;
            int subjectCount = 0;

            if (find(classes.begin(), classes.end(), studentClass) != classes.end())
            {
                SubjectNode *current = subjects.head;
                while (current != nullptr)
                {
                    if (find(current->subjectClasses.begin(), current->subjectClasses.end(), studentClass) != current->subjectClasses.end())
                    {
                        subjectCount++;
                    }
                    current = current->next;
                }

                for (int i = 0; i < subjectCount * 3; ++i)
                {
                    grades.push_back(-1.0f);
                }

                float attendance;
                ss >> attendance;
                grades.push_back(attendance);
            }
            else
            {
                while (ss >> grade)
                {
                    if (ss.peek() == '|')
                    {
                        ss.ignore();
                    }
                    grades.push_back(grade);
                }
            }

            stringstream newLine;
            newLine << studentId << "|" << studentClass;
            for (size_t i = 0; i < grades.size() - 1; ++i)
            {
                newLine << "|" << grades[i];
            }
            newLine << "|" << grades.back();
            lines.push_back(newLine.str());
        }
        inFile.close();

        ofstream outFile("gradeAttendance.txt");
        if (!outFile.is_open())
        {
            cout << "Unable to open gradeAttendance.txt for writing" << endl;
            return;
        }

        for (const auto &l : lines)
        {
            outFile << l << "\n";
        }
        outFile.close();
    }

    void view_subjects()
    {
        cout << "============================================================================" << endl;
        cout << "                              VIEW SUBJECTS                                 " << endl;
        cout << "============================================================================" << endl;
        subjects.printSubjects();
        system("pause");
        system("cls");
    }

    void init_vector()
    {
        vStu.clear();
        vTea.clear();

        ifstream ifs;
        ifs.open("user.txt", ios::in);
        if (!ifs.is_open())
        {
            cout << "File does not exists" << endl;
            return;
        }

        string myString;
        string line;

        while (getline(ifs, line))
        {
            stringstream ss(line);
            string type;
            getline(ss, type, '|');

            if (type == "1")
            {
                Teacher t;
                getline(ss, t.m_id, '|');
                getline(ss, t.m_name, '|');
                getline(ss, t.m_password, '|');
                getline(ss, t.m_gender, '|');
                getline(ss, t.m_class, '|');
                vTea.push_back(t);
            }
            else if (type == "2")
            {
                Student s;
                getline(ss, s.m_id, '|');
                getline(ss, s.m_name, '|');
                getline(ss, s.m_password, '|');
                getline(ss, s.m_gender, '|');
                getline(ss, s.m_class, '|');
                vStu.push_back(s);
            }
        }
        ifs.close();
    }

    void update_user_file()
    {
        ofstream ofs("user.txt", ios::out | ios::trunc);
        if (!ofs.is_open())
        {
            cout << "Unable to open file for writing" << endl;
            return;
        }

        ofs << "0|Admin|Admin|1|None|None" << endl;

        for (const auto &user : vTea)
        {
            ofs << "1|" << user.m_id << "|" << user.m_name << "|" << user.m_password << "|" << user.m_gender << "|" << user.m_class << endl;
        }
        for (const auto &user : vStu)
        {
            ofs << "2|" << user.m_id << "|" << user.m_name << "|" << user.m_password << "|" << user.m_gender << "|" << user.m_class << endl;
        }

        ofs.close();
    }

    void updateCommentFile(const string &studentId, const string &newClass)
    {
        ifstream file("comment.txt");
        if (!file.is_open())
        {
            cout << "Unable to open comment.txt for reading" << endl;
            return;
        }

        vector<string> lines;
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id, oldClass, comment;
            getline(ss, id, '|');
            getline(ss, oldClass, '|');
            getline(ss, comment);

            if (id == studentId)
            {

                lines.push_back(studentId + "|" + newClass + "|" + comment);
            }
            else
            {
                lines.push_back(line);
            }
        }
        file.close();

        ofstream outFile("comment.txt");
        if (!outFile.is_open())
        {
            cout << "Unable to open comment.txt for writing" << endl;
            return;
        }

        for (const auto &l : lines)
        {
            outFile << l << "\n";
        }
        outFile.close();
    }

    void updateGradeAttendanceFile(const string &studentId, const string &newClass)
    {
        ifstream file("gradeAttendance.txt");
        if (!file.is_open())
        {
            cout << "Unable to open gradeAttendance.txt for reading" << endl;
            return;
        }

        vector<string> lines;
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id, oldClass, scores;
            getline(ss, id, '|');
            getline(ss, oldClass, '|');
            getline(ss, scores);

            if (id == studentId)
            {
                lines.push_back(studentId + "|" + newClass + "|" + scores);
            }
            else
            {
                lines.push_back(line);
            }
        }
        file.close();

        ofstream outFile("gradeAttendance.txt");
        if (!outFile.is_open())
        {
            cout << "Unable to open gradeAttendance.txt for writing" << endl;
            return;
        }

        for (const auto &l : lines)
        {
            outFile << l << "\n";
        }
        outFile.close();
    }

    bool check_repeat(const string &id, int type)
    {
        if (type == 1)
        {
            for (const auto &teacher : vTea)
            {
                if (teacher.m_id == id)
                {
                    return true;
                }
            }
        }
        else if (type == 2)
        {
            for (const auto &student : vStu)
            {
                if (student.m_id == id)
                {
                    return true;
                }
            }
        }
        else if (type == 3)
        {
            SubjectNode *current = subjects.head;
            while (current != nullptr)
            {
                if (current->subjectCode == id)
                {
                    return true;
                }
                current = current->next;
            }
        }
        return false;
    }

    void loadSubjects(const string &filename)
    {
        ifstream inFile(filename);
        if (!inFile.is_open())
        {
            cout << "Unable to open " << filename << " for reading" << endl;
            return;
        }

        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string subjectCode, subjectName, className;
            vector<string> subjectClasses;

            getline(ss, subjectCode, '|');
            getline(ss, subjectName, '|');
            while (getline(ss, className, '|'))
            {
                subjectClasses.push_back(className);
            }

            subjects.addSubject(subjectCode, subjectName, subjectClasses);
        }

        inFile.close();
    }

    void saveSubjects(const string &filename)
    {
        ofstream outFile(filename);
        if (!outFile.is_open())
        {
            cout << "Unable to open " << filename << " for writing" << endl;
            return;
        }

        SubjectNode *current = subjects.head;
        while (current != nullptr)
        {
            outFile << current->subjectCode << "|" << current->subjectName << "|";
            for (size_t i = 0; i < current->subjectClasses.size(); ++i)
            {
                outFile << current->subjectClasses[i];
                if (i < current->subjectClasses.size() - 1)
                {
                    outFile << "|";
                }
            }
            outFile << "\n";
            current = current->next;
        }

        outFile.close();
    }

    vector<Student> vStu;
    vector<Teacher> vTea;
    SubjectLinkedList subjects;
};

void login();
void idm();
void change_password();
void view_my_account();

int main()
{
    int choice = 0;

    std::string weekdays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    do
    {
        cout << "============================================================================" << endl;
        cout << "                      Secondary Report Card System                          " << endl;
        cout << "============================================================================" << endl;
        time_t now = time(NULL);
        tm *local = localtime(&now);
        int weekday = local->tm_wday;

        cout << "\t\t\t\t\t\t" << weekdays[weekday];
        cout << "  " << local->tm_mday << "/" << local->tm_mon + 1 << "/" << local->tm_year + 1900 << endl;
        cout << "    [1] Log in" << endl;
        cout << "    [2] Identity Management (IDM)" << endl;
        cout << "    [3] Exit" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
    RECHOICE:
        cout << "    Please Enter Your Choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            goto RECHOICE;
        }

        switch (choice)
        {
        case 1:
            login();
            break;
        case 2:
            system("cls");
            idm();
            break;
        case 3:
            cout << "\033[1;32m    Exited the system sucessfully.\033[0m" << std::endl;
            system("pause");
            system("cls");
            return 0;
        default:
            cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << std::endl;
            goto RECHOICE;
        }
    } while (true);

    return 0;
}

void login()
{
    Identity *user = NULL;

    string user_type;
    string user_id, user_name, user_password, user_gender, user_class;
    bool flag = false;
    int count;

    string fType;
    string fId;
    string fName;
    string fPassword;
    string fGender;
    string fClass;

    string myString;
    string line;

    for (count = 3; count >= 0 && !flag; --count)
    {
        cout << "    Please Enter Your ID: ";
        cin >> user_id;
        cout << "    Please Enter Your Password: ";
        cin >> user_password;
        ifstream ifs;
        ifs.open("user.txt", ios::in);

        if (ifs.is_open())
        {
            while (getline(ifs, line))
            {
                stringstream ss(line);
                getline(ss, fType, '|');
                getline(ss, fId, '|');
                getline(ss, fName, '|');
                getline(ss, fPassword, '|');
                getline(ss, fGender, '|');
                getline(ss, fClass, '|');
                if (fId == user_id && fPassword == user_password)
                {
                    flag = true;
                    user_type = fType;
                    if (user_type == "0")
                    {
                        system("cls");
                        user = new Admin(fName, fPassword);
                    }
                    else if (user_type == "1")
                    {
                        system("cls");
                        user = new Teacher(fType, fId, fName, fPassword, fGender, fClass);
                    }
                    else
                    {
                        system("cls");
                        user = new Student(fType, fId, fName, fPassword, fGender, fClass);
                    }
                }
                if (user)
                {
                    user->open_menu();
                    delete user;
                    cout << "\033[1;32m    Logged Out Successfully.\033[0m" << endl;
                    system("pause");
                    system("cls");
                    return;
                    break;
                }
            }
            if (!flag && count > 1)
            {
                cout << "\033[1;31m    Invalid ID or password. Please try again (" << count << " attempts left)\033[0m" << endl;
            }
            else if (!flag && count == 1)
            {
                cout << "\033[1;31m    Invalid ID or password. Please try again (" << count << " attempt left)\033[0m" << endl;
            }
            else
            {
                system("pause");
                system("cls");
                return;
            }
            ifs.close();
        }
        else
        {
            cout << "File does not exist" << endl;
            ifs.close();
            return;
        }
    }
}

void idm()
{
    int choice = 0;
    do
    {
        cout << "============================================================================" << endl;
        cout << "                            IDENTITY MANAGEMENT                             " << endl;
        cout << "============================================================================" << endl;
        cout << "    [1] Change Password" << endl;
        cout << "    [2] View My Account" << endl;
        cout << "    [3] Back to Main Menu" << endl;
        cout << "============================================================================" << endl;
    RECHOICE:
        cout << "    Please Enter Your Choice: ";
        cin >> choice;
        if (cin.fail())
        {
            cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto RECHOICE;
        }

        switch (choice)
        {
        case 1:
            system("cls");
            change_password();
            break;
        case 2:
            system("cls");
            view_my_account();
            break;
        case 3:
            system("pause");
            system("cls");
            return;
        default:
            cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
            goto RECHOICE;
        }
    } while (true);
    return;
}

void change_password()
{
    string userId, oldPassword, newPassword, confirmPassword;

    cout << "============================================================================" << endl;
    cout << "                             CHANGE PASSWORD                                " << endl;
    cout << "============================================================================" << endl;
    cout << "    Please Enter Your ID: ";
    cin >> userId;
    cout << "    Please Enter Your Current Password: ";
    cin >> oldPassword;

    ifstream ifs("user.txt");
    if (!ifs.is_open())
    {
        cout << "Unable to open user.txt" << endl;
        return;
    }

    string line;
    vector<string> lines;
    bool passwordChanged = false;
    bool userFound = false;
    while (getline(ifs, line))
    {
        stringstream ss(line);
        string type, id, name, password, gender, userClass;
        getline(ss, type, '|');
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, password, '|');
        getline(ss, gender, '|');
        getline(ss, userClass, '|');

        if (id == userId && password == oldPassword)
        {
            userFound = true;
            cout << "    Please Enter New Password or Press Enter to Skip: ";
            cin.ignore();
            getline(cin, newPassword);
            if (!newPassword.empty())
            {
                cout << "    Please Reenter New Password: ";
                getline(cin, confirmPassword);
                if (newPassword == confirmPassword)
                {
                    password = newPassword;
                    passwordChanged = true;
                }
                else
                {
                    cout << "\033[1;31mPasswords do not match. Password change cancelled.\033[0m" << endl;
                }
            }
        }
        lines.push_back(type + "|" + id + "|" + name + "|" + password + "|" + gender + "|" + userClass);
    }

    ifs.close();

    if (!userFound)
    {
        cout << "\033[1;31m    Invalid User ID or Password.\033[0m" << endl;
        system("pause");
        system("cls");
        return;
    }

    if (passwordChanged)
    {
        ofstream ofs("user.txt");
        if (!ofs.is_open())
        {
            cout << "Unable to open user.txt for writing" << endl;
            return;
        }
        for (const auto &l : lines)
        {
            ofs << l << "\n";
        }
        ofs.close();
        cout << "\033[1;32m    Password changed successfully.\033[0m" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout << "\033[1;33m    Password change skipped.\033[0m" << endl;
        system("pause");
        system("cls");
    }
}

void view_my_account()
{
    string userId, userPassword;

    cout << "============================================================================" << endl;
    cout << "                              VIEW MY ACCOUNT                               " << endl;
    cout << "============================================================================" << endl;
    cout << "    Please Enter Your ID: ";
    cin >> userId;
    cout << "    Please Enter Your Password: ";
    cin >> userPassword;

    ifstream ifs("user.txt");
    if (!ifs.is_open())
    {
        cout << "Unable to open user.txt" << endl;
        return;
    }

    string line;
    bool userFound = false;
    while (getline(ifs, line))
    {
        stringstream ss(line);
        string type, id, name, password, gender, userClass;
        getline(ss, type, '|');
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, password, '|');
        getline(ss, gender, '|');
        getline(ss, userClass, '|');

        if (id == userId && password == userPassword)
        {
            userFound = true;
            cout << "----------------------------------------------------------------------------" << endl;
            cout << "    Name : " << left << setw(30) << name << "Gender : " << gender << endl;
            cout << "    ID   : " << left << setw(30) << id << "Class  : " << (type == "1" ? "Teacher" : (type == "2" ? "Student " + userClass : "")) << endl;
            cout << "----------------------------------------------------------------------------" << endl;
            system("pause");
            system("cls");
            break;
        }
    }

    ifs.close();

    if (!userFound)
    {
        cout << "\033[1;31m    Invalid User ID or Password.\033[0m" << endl;
        system("pause");
        system("cls");
    }
}