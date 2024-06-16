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
#include <list>
#include <unordered_map>
#include <sstream>
#include <numeric>

using namespace std;

// 学生信息结构体
struct StudentInfo {
    string studentId;
    string studentClass;
    string comment;       // 学生评论
    vector<float> grades; // 21 个成绩 (7 科目 * 3 学期)
    float attendancePercentage;

    StudentInfo() : attendancePercentage(0.0) {
        grades.resize(21, 0.0); // 初始化所有成绩为 0.0
    }
};

// 身份类
class Identity {
public:
    virtual void open_menu() = 0;

    string m_type;
    string m_id;
    string m_name;
    string m_password;
    string m_gender;
    string m_class;

    virtual ~Identity() {}
};

// Teacher 
class Teacher : public Identity {
    friend class Student;

public:
    Teacher() {}
    ~Teacher() {}

    Teacher(string user_type, string user_id, string user_name, string user_password, string user_gender, string user_class) {
        this->m_type = user_type;
        this->m_id = user_id;
        this->m_name = user_name;
        this->m_password = user_password;
        this->m_gender = user_gender;
        this->m_class = user_class;
    }

    static void loadStudentGradeAttendance(const string &filename, vector<StudentInfo> &students) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to open " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            StudentInfo student;
            string gradeStr;

            getline(ss, student.studentId, '|');
            getline(ss, student.studentClass, '|');
            for (int i = 0; i < 21; ++i) {
                getline(ss, gradeStr, '|');
                student.grades[i] = stof(gradeStr);
            }
            getline(ss, gradeStr);
            student.attendancePercentage = stof(gradeStr);

            students.push_back(student);
        }

        file.close();
    }

    static void saveStudentGradeAttendace(const vector<StudentInfo> &students, const string &filename) {
        ofstream file(filename);

        for (const auto &student : students) {
            file << student.studentId << "|" << student.studentClass;
            for (const auto &grade : student.grades) {
                file << "|" << grade;
            }
            file << "|" << student.attendancePercentage << "\n";
        }

        file.close();
    }

    static void loadStudentComments(const string &filename, vector<StudentInfo> &students) {
        ifstream file(filename);
        string line;

        if (!file.is_open()) {
            cout << "Failed to open " << filename << endl;
            return;
        }

        while (getline(file, line)) {
            stringstream ss(line);
            string studentId, studentClass, comment;
            getline(ss, studentId, '|');
            getline(ss, studentClass, '|');
            getline(ss, comment);

            auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s) { return s.studentId == studentId; });
            if (it != students.end()) {
                it->comment = comment;
            }
        }
        file.close();
    }

    static void saveStudentComments(const vector<StudentInfo> &students, const string &filename) {
        ofstream file(filename);

        for (const auto &student : students) {
            file << student.studentId << "|" << student.studentClass << "|" << student.comment << "\n";
        }

        file.close();
    }

    string getGradeLetter(float grade) {
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

    void open_menu() {
        int choice = 0;
        do {
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
            cout << "    [6] Logout" << endl;
            cout << "================================================================================" << endl;
        RECHOICE:
            cout << "    Please Enter Your Choice: ";
            cin >> choice;
            if (cin.fail()) {
                cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto RECHOICE;
            }

            switch (choice) {
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
                    return;
                default:
                    cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
                    goto RECHOICE;
            }
        } while (true);
        return;
    }

    void update_student_grades() {
        vector<StudentInfo> students;
        loadStudentGradeAttendance("gradeAttendance.txt", students);

        cout << "============================================================================" << endl;
        cout << "                            UPDATE STUDENT MARKS" << endl;
        cout << "============================================================================" << endl;
        cout << "    Enter the student ID : ";

        string studentId;
        cin >> studentId;

        auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s) { return s.studentId == studentId; });
        if (it == students.end()) {
            char choice;

            cout << "\033[1;31m    Student not found. Please try again. \033[0m" << endl;
            cout << "    Do you want to try again ? (Y/N) : ";
            cin >> choice;

            while (choice == 'y' || choice == 'Y') {
                cout << "============================================================================" << endl;
                cout << "    Enter the correct student ID : ";
                cin >> studentId;
                it = find_if(students.begin(), students.end(), [&](const StudentInfo &s) { return s.studentId == studentId; });

                if (it == students.end()) {
                    cout << "\033[1;31m    Student not found. Please try again. \033[0m" << endl;
                    cout << "    Do you want to try again ? (Y/N) : ";
                    cin >> choice;
                } else {
                    break;
                }
            }
            if (choice != 'y' && choice != 'Y') {
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
        switch (termChoice) {
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
                while (termChoice != 1 && termChoice != 2 && termChoice != 3 && termChoice != 4) {
                    cout << "\033[1;31m    Invalid choice. Please make sure you entered the correct one. \033[0m" << endl;
                    cout << "----------------------------------------------------------------------------" << endl;
                    cout << "    Enter the correct choice : ";
                    cin >> termChoice;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    if (termChoice == 1) {
                        gradeOffset = 0;
                    } else if (termChoice == 2) {
                        gradeOffset = 7;
                    } else if (termChoice == 3) {
                        gradeOffset = 14;
                    } else if (termChoice == 4) {
                        return;
                    }
                }
        }
        char continueUpdate;
        do {
            system("cls");
            cout << "============================================================================" << endl;
            cout << "                            UPDATE STUDENT MARKS" << endl;
            cout << "============================================================================" << endl;
            cout << "    Current grades for " << studentId << endl;
            string subjects[7] = {"Bahasa Melayu", "English", "Mandarin", "Mathematics", "History", "Science", "Moral"};
            const int setwValues[] = {6, 12, 11, 8, 12, 12, 14};
            for (int i = 0; i < 7; ++i) {
                cout << "    [" << i + 1 << "] " << subjects[i] << setw(setwValues[i]) << ": ";

                if (it->grades[gradeOffset + i] == -1) {
                    cout << "-";
                } else {
                    cout << static_cast<int>(it->grades[gradeOffset + i]);
                }
                cout << endl;
            }
            cout << "----------------------------------------------------------------------------" << endl;
            cout << "    Select the subject code to update the marks (1-7) : ";
            int subjectChoice;
            cin >> subjectChoice;

            if (cin.fail() || subjectChoice < 1 || subjectChoice > 7) {
                cout << "\033[1;31m    Invalid subject choice. Please try again. \033[0m" << endl;

                while (subjectChoice < 1 || subjectChoice > 7) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "    Select the correct subject code to update the marks (1-7) : ";
                    cin >> subjectChoice;
                    if (subjectChoice < 1 || subjectChoice > 7) {
                        cout << "\033[1;31m    Invalid subject code choice. Please try again. \033[0m" << endl;
                    }
                }
            }

            cout << "    Enter the new mark : ";
            float newGrade;
            cin >> newGrade;

            while (cin.fail() || newGrade < 0 || newGrade > 100) {
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

            while (cin.fail()) {
                cout << "\033[1;31m    Invalid choice. Please enter agian.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "    Enter the correct choice : ";
                cin >> continueUpdate;

                if (continueUpdate != 'y' && continueUpdate != 'Y') {
                    system("pause");
                    system("cls");
                }
            }
        } while (continueUpdate == 'y' || continueUpdate == 'Y');
    }

    void update_student_attendance() {
        vector<StudentInfo> students;
        loadStudentGradeAttendance("gradeAttendance.txt", students);

        cout << "============================================================================" << endl;
        cout << "                       UPDATE STUDENT ATTENDANCE " << endl;
        cout << "============================================================================" << endl;
        cout << "    Enter the student ID : ";
        string studentId;
        cin >> studentId;

        auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s) { return s.studentId == studentId; });
        if (it == students.end() || it->studentClass != this->m_class) {
            do {
                cout << "\033[1;31m    Student not found or not in your class. Please try again. \033[0m" << endl;
                cout << "    Enter the correct student ID : ";
                cin >> studentId;

                it = find_if(students.begin(), students.end(), [&](const StudentInfo &s) { return s.studentId == studentId; });
            } while (it == students.end() || it->studentClass != this->m_class);
        }

        system("cls");
        cout << "============================================================================" << endl;
        cout << "                       UPDATE STUDENT ATTENDANCE " << endl;
        cout << "============================================================================" << endl;
        cout << "    Current attendance for " << studentId << " : ";
        if (it->attendancePercentage == -1) {
            cout << "-" << endl;
        } else {
            cout << it->attendancePercentage << "%" << endl;
        }
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "    Enter the new attendance or press enter to skip: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空输入缓冲区

        string newAttendanceStr;
        getline(cin, newAttendanceStr);

        if (!newAttendanceStr.empty()) {
            try {
                float newAttendance = stof(newAttendanceStr);
                while (newAttendance < 0.0f || newAttendance > 100.0f) {
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
            } catch (const invalid_argument &) {
                cout << "\033[1;31m    Invalid input. Attendance not updated. \033[0m" << endl;
                system("pause");
                system("cls");
            }
        } else {
            cout << "\033[1;32m    Update skipped.\033[0m" << endl;
            system("pause");
            system("cls");
        }
    }

    void view_class_attendance_and_grades() {
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
        do {
            cout << "    Enter your choice : ";
            if (!(cin >> termChoice)) {
                cout << "\033[1;31m    Invalid input. Please enter again. \033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            switch (termChoice) {
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
        if (termChoice == 3) {
            cout << setw(15) << "Attendance";
        }
        cout << endl;

        for (const auto &student : students) {
            if (student.studentClass == classToView) {
                cout << setw(15) << student.studentId;
                for (int i = gradeOffset; i < gradeOffset + 7; ++i) {
                    if (student.grades[i] == -1) {
                        cout << setw(15) << "-";
                    } else {
                        if (student.grades[i] < 40.0f) {
                            cout << "\033[1;31m";
                        } else {
                            cout << "\033[1;32m";
                        }
                        cout << setw(15) << static_cast<int>(student.grades[i]) << "\033[0m";
                    }
                }
                if (termChoice == 3) {
                    if (student.attendancePercentage == -1) {
                        cout << setw(15) << "-";
                    } else {
                        if (student.attendancePercentage < 80.0f) {
                            cout << "\033[1;31m";
                        } else {
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

    void student_attendance_and_grades() {
        vector<StudentInfo> students;
        loadStudentGradeAttendance("gradeAttendance.txt", students);

        cout << "=======================================================================================================" << endl;
        cout << "                                       View Grades and Attendance" << endl;
        cout << "=======================================================================================================" << endl;
        string studentId;
        cout << "    Enter the student ID : ";
        cin >> studentId;

        auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s) { return s.studentId == studentId; });
        if (it == students.end() || it->studentClass != this->m_class) {
            do {
                cout << "\033[1;31m    Student not found or not in your class.Please make sure you enter the correct student id. \033[0m" << endl;
                cout << "=======================================================================================================" << endl;
                cout << "    Enter the correct student ID : ";
                cin >> studentId;
                it = find_if(students.begin(), students.end(), [&](const StudentInfo &s) { return s.studentId == studentId; });
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

        for (int term = 0; term < 3; ++term) {
            cout << "----------------------------------------------------------------------------" << endl;
            cout << "                       \033[1;34m" << "Marks for " << terms[term] << "\033[0m" << endl;
            cout << "----------------------------------------------------------------------------" << endl;
            cout << "    No.  " << left << setw(35) << "Subject" << setw(10) << "Marks" << setw(10) << "Grades " << endl;
            int gradeOffset = term * 7;

            for (int i = 0; i < 7; ++i) {
                float grade = it->grades[gradeOffset + i];
                totalMarks += grade;
                totalPossibleMarks += 100.0f;

                cout << "    " << i + 1 << ".   " << setw(36) << subjects[i] << setw(11);
                if (grade == -1) {
                    cout << "-";
                } else {
                    cout << grade;
                }
                cout << setw(10) << getGradeLetter(grade) << endl;
            }
        }
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "Attendance : ";
        if (it->attendancePercentage == -1) {
            cout << "-";
        } else {
            if (it->attendancePercentage < 80.0f) {
                cout << "\033[1;31m";
            } else {
                cout << "\033[1;32m";
            }
            cout << it->attendancePercentage << "%" << "\033[0m";
        }
        cout << endl;
        cout << "============================================================================" << endl;

        system("pause");
        system("cls");
    }

    void update_student_comment() {
        vector<StudentInfo> students;
        loadStudentGradeAttendance("gradeAttendance.txt", students);
        loadStudentComments("comment.txt", students);

        cout << "============================================================================" << endl;
        cout << "                           UPDATE STUDENT COMMENT" << endl;
        cout << "============================================================================" << endl;
        cout << "    Enter the student ID : ";
        string studentId;
        cin >> studentId;

        auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s) { return s.studentId == studentId; });
        if (it == students.end() || it->studentClass != this->m_class) {
            do {
                cout << "\033[1;31m    Student not found or not in your class.Please try again. \033[0m" << endl;
                cout << "============================================================================" << endl;
                cout << "    Enter the correct student ID : ";
                cin >> studentId;
                it = find_if(students.begin(), students.end(), [&](const StudentInfo &s) { return s.studentId == studentId; });
            } while (it == students.end() || it->studentClass != this->m_class);
        }
        system("cls");
        cout << "============================================================================" << endl;
        cout << "                           UPDATE STUDENT COMMENT" << endl;
        cout << "============================================================================" << endl;
        cout << "    Current comment for " << studentId << " :" << endl;
        cout << "    " << it->comment << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "    Enter the new comment or press Enter to skip : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string newComment;
        getline(cin, newComment);

        if (!newComment.empty()) {
            it->comment = newComment;
            saveStudentComments(students, "comment.txt");
            cout << "\033[1;32m    Comment updated successfully. \033[0m" << endl;
            system("pause");
            system("cls");
        } else {
            cout << "\033[1;32m    Update skipped.\033[0m" << endl;
            system("pause");
            system("cls");
        }
    }
};

// 学生类
class Student : public Identity {
    friend class Teacher;

public:
    Student() {}
    ~Student() {}

    Student(string user_type, string user_id, string user_name, string user_password, string user_gender, string user_class) {
        this->m_type = user_type;
        this->m_id = user_id;
        this->m_name = user_name;
        this->m_password = user_password;
        this->m_gender = user_gender;
        this->m_class = user_class;
    }

    void open_menu() {
        int choice = 0;
        do {
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
            if (cin.fail()) {
                cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto RECHOICE;
            }

            switch (choice) {
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

    void view_exam_result_slip() {
        vector<StudentInfo> students;
        Teacher::loadStudentGradeAttendance("gradeAttendance.txt", students);

        auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s) { return s.studentId == this->m_id; });
        if (it == students.end()) {
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
        while (true) {
            cout << "    Enter your choice : ";
            cin >> termChoice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "\033[1;31m    Invalid input. Please try again.\033[0m" << endl;
            } else {
                switch (termChoice) {
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
        for (int i = 0; i < 7; ++i) {
            float grade = it->grades[gradeOffset + i];
            if (grade != -1) {
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
        cout << "\033[1;34m                         Marks for " << (termChoice == 1 ? "First Term Exam" : termChoice == 2 ? "Midterm Exam" : "Final Exam") << "\033[0m" << endl;
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

        cout << "    Total marks for " << (termChoice == 1 ? "First Term Exam" : termChoice == 2 ? "Midterm Exam" : "Final Exam") << " : " << termTotalMarks << "/" << termTotalPossibleMarks << endl;
        cout << "    Percentage for " << (termChoice == 1 ? "First Term Exam" : termChoice == 2 ? "Midterm Exam" : "Final Exam") << "  : ";

        if (termPercentage == -1.0f) {
            cout << "-" << endl;
        } else if (termPercentage < 50.0f) {
            cout << " \033[1;31m";
            cout << fixed << setprecision(0) << termPercentage << "%" << "\033[0m" << endl;
        } else {
            cout << " \033[1;32m";
            cout << fixed << setprecision(0) << termPercentage << "%" << "\033[0m" << endl;
        }

        cout << "----------------------------------------------------------------------------" << endl;
        system("pause");
        system("cls");
    }

    void view_report_card() {
        vector<StudentInfo> students;
        Teacher::loadStudentGradeAttendance("gradeAttendance.txt", students);
        Teacher::loadStudentComments("comment.txt", students);

        auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s) { return s.studentId == this->m_id; });
        if (it == students.end()) {
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

        for (int i = 0; i < 7; ++i) {
            cout << "    " << i + 1 << ".   " << left << setw(24) << subjects[i];

            for (int term = 0; term < 3; ++term) {
                int gradeOffset = term * 7;
                float grade = it->grades[gradeOffset + i];

                if (grade != -1) {
                    termTotalMarks[term] += grade;
                    termTotalPossibleMarks[term] += 100.0f;
                }

                cout << "|  " << setw(10) << (grade == -1 ? "-" : to_string(static_cast<int>(grade))) << setw(5) << getGradeLetter(grade);
            }

            cout << "|" << endl;
        }

        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "\033[0m    Total Mark                   ";
        for (int term = 0; term < 3; ++term) {
            cout << "|    " << termTotalMarks[term] << "/" << termTotalPossibleMarks[term] << "      ";
        }
        cout << "|";
        cout << "\033[0m" << endl;

        cout << "    Percentage                  ";

        for (int term = 0; term < 3; ++term) {
            float percentage = (termTotalMarks[term] / termTotalPossibleMarks[term]) * 100.0f;

            cout << " |   ";
            if (percentage < 50.0f) {
                cout << " \033[1;31m";
            } else {
                cout << " \033[1;32m";
            }
            cout << fixed << "  " << setprecision(0) << percentage << "%      " << "\033[0m ";
        }
        cout << " |" << endl;

        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "    Attendance  : ";
        if (it->attendancePercentage == -1) {
            cout << "-";
        } else {
            if (it->attendancePercentage < 80.0f) {
                cout << "\033[1;31m";
            } else {
                cout << "\033[1;32m";
            }
            cout << it->attendancePercentage << "%" << "\033[0m" << endl;
        }
        cout << "    Teacher's Comment : " << it->comment << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;
        system("pause");
        system("cls");
    }

    string getGradeLetter(float grade) {
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

// 管理员类
class Admin : public Identity {
public:
    Admin() {}
    ~Admin() {}

    Admin(string name, string password) {
        this->m_name = name;
        this->m_password = password;
        this->init_vector();
    }

    void open_menu() {
        int choice = 0;
        do {
            cout << "============================================================================" << endl;
            cout << "                                 ADMIN MENU                                 " << endl;
            cout << "============================================================================" << endl;
            cout << right << setw(60) << "Welcome, " << this->m_name << endl;
            cout << "    [1] Activate New Account" << endl;
            cout << "    [2] Deactivate Exist Account" << endl;
            cout << "    [3] Edit User Profile" << endl;
            cout << "    [4] View Teacher or Student List" << endl;
            cout << "    [5] View All Classes List" << endl;
            cout << "    [6] Logout" << endl;
            cout << "============================================================================" << endl;
        RECHOICE:
            cout << "    Please Enter Your Choice: ";
            cin >> choice;
            if (cin.fail()) {
                cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto RECHOICE;
            }

            switch (choice) {
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
                    return;
                default:
                    cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
                    goto RECHOICE;
            }
        } while (true);
        return;
    }

private:
    void display_teacher_details(const Teacher &teacher) {
        cout << "============================================================================" << endl;
        cout << "                           EDIT TEACHER PROFILE                             " << endl;
        cout << "============================================================================" << endl;
        cout << "    Name     : " << left << setw(30) << teacher.m_name << "Gender : " << setw(15) << teacher.m_gender << endl;
        cout << "    Password : " << left << setw(30) << teacher.m_password << "Class  : " << setw(15) << teacher.m_class << endl;
    }

    void display_student_details(const Student &student) {
        cout << "============================================================================" << endl;
        cout << "                           EDIT STUDENT PROFILE                             " << endl;
        cout << "============================================================================" << endl;
        cout << "    Name     : " << left << setw(30) << student.m_name << "Gender : " << setw(15) << student.m_gender << endl;
        cout << "    Password : " << left << setw(30) << student.m_password << "Class  : " << setw(15) << student.m_class << endl;
    }

    void edit_user_profile() {
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
        if (cin.fail()) {
            cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto RECHOICE;
        } else if (choice < 1 || choice > 3) {
            cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
            goto RECHOICE;
        } else if (choice == 3) {
            cout << "\033[1;32m    Returned Successfully.\033[0m" << endl;
            system("pause");
            system("cls");
            return;
        } else {
            if (choice == 1) {
                cout << "    Please Enter Teacher ID: ";
                cin >> user_id;
                itTea = find_if(vTea.begin(), vTea.end(), [&](const Teacher &t) { return t.m_id == user_id; });
                userFound = itTea != vTea.end();
            } else {
                cout << "    Please Enter Student ID: ";
                cin >> user_id;
                itStu = find_if(vStu.begin(), vStu.end(), [&](const Student &s) { return s.m_id == user_id; });
                userFound = itStu != vStu.end();
            }

            if (!userFound) {
                cout << "\033[1;31m    User Not Found. Please Try Again.\033[0m" << endl;
                goto EDITUSERPROFILEMENU;
            }
        }

        do {
            system("cls");
            cout << "============================================================================" << endl;
            cout << "                              EDIT USER PROFILE                             " << endl;
            cout << "============================================================================" << endl;
            cout << "    What would you like to edit?" << endl;
            cout << "    [1] Name" << endl;
            cout << "    [2] Gender" << endl;
            cout << "    [3] Password" << endl;
            cout << "    [4] Class" << endl;
            cout << "    [5] Exit" << endl;
            cout << "============================================================================" << endl;
        RECHOICE2:
            cout << "    Please Enter Your Choice: ";
            cin >> edit_choice;
            if (cin.fail()) {
                cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto RECHOICE2;
            } else if (edit_choice < 1 || edit_choice > 5) {
                cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
                goto RECHOICE2;
            } else if (edit_choice == 5) {
                cout << "\033[1;32m    Returned Successfully.\033[0m" << endl;
                system("pause");
                system("cls");
                return;
            } else {
                string new_value;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "    Enter New Value: ";
                getline(cin, new_value);

                if (choice == 1) {
                    switch (edit_choice) {
                        case 1:
                            itTea->m_name = new_value;
                            break;
                        case 2:
                            itTea->m_gender = new_value;
                            break;
                        case 3:
                            itTea->m_password = new_value;
                            break;
                        case 4:
                            itTea->m_class = new_value;
                            break;
                    }
                    display_teacher_details(*itTea);
                } else {
                    switch (edit_choice) {
                        case 1:
                            itStu->m_name = new_value;
                            break;
                        case 2:
                            itStu->m_gender = new_value;
                            break;
                        case 3:
                            itStu->m_password = new_value;
                            break;
                        case 4:
                            itStu->m_class = new_value;
                            break;
                    }
                    display_student_details(*itStu);
                }
                save_teacher();
                save_student();
                cout << "\033[1;32m    Profile Updated Successfully.\033[0m" << endl;
                system("pause");
                system("cls");
            }
        } while (edit_choice != 5);
    }

    void view_teacher_or_student_list() {
        int choice = 0;
        int count = 0;
        string class_id;

        do {
            cout << "============================================================================" << endl;
            cout << "                            VIEW TEACHER/STUDENT LIST" << endl;
            cout << "============================================================================" << endl;
            cout << "    [1] View Teacher List" << endl;
            cout << "    [2] View Student List" << endl;
            cout << "    [3] Back to Main Menu" << endl;
            cout << "============================================================================" << endl;
        RECHOICE:
            cout << "    Please Enter Your Choice: ";
            cin >> choice;
            if (cin.fail()) {
                cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto RECHOICE;
            }

            switch (choice) {
                case 1:
                    system("cls");
                    cout << "============================================================================" << endl;
                    cout << "                                 TEACHER LIST                               " << endl;
                    cout << "============================================================================" << endl;
                    count = 0;
                    for (const auto &t : vTea) {
                        cout << "    Name: " << left << setw(30) << t.m_name << "Gender: " << setw(10) << t.m_gender << "Class: " << t.m_class << endl;
                        cout << "----------------------------------------------------------------------------" << endl;
                        count++;
                    }
                    cout << "    Total Teachers: " << count << endl;
                    system("pause");
                    system("cls");
                    break;
                case 2:
                    system("cls");
                    cout << "    Please Enter Class ID: ";
                    cin >> class_id;
                    system("cls");
                    cout << "============================================================================" << endl;
                    cout << "                                 STUDENT LIST                               " << endl;
                    cout << "============================================================================" << endl;
                    count = 0;
                    for (const auto &s : vStu) {
                        if (s.m_class == class_id) {
                            cout << "    Name: " << left << setw(30) << s.m_name << "Gender: " << setw(10) << s.m_gender << "Class: " << s.m_class << endl;
                            cout << "----------------------------------------------------------------------------" << endl;
                            count++;
                        }
                    }
                    cout << "    Total Students: " << count << endl;
                    system("pause");
                    system("cls");
                    break;
                case 3:
                    system("cls");
                    return;
                default:
                    cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
                    goto RECHOICE;
            }
        } while (true);
    }

    void view_all_classes_list() {
        system("cls");
        cout << "============================================================================" << endl;
        cout << "                               VIEW ALL CLASSES                              " << endl;
        cout << "============================================================================" << endl;

        unordered_map<string, list<string>> classMap;
        for (const auto &student : vStu) {
            classMap[student.m_class].push_back(student.m_name);
        }

        for (const auto &entry : classMap) {
            cout << "    Class: " << entry.first << endl;
            for (const auto &studentName : entry.second) {
                cout << "        " << studentName << endl;
            }
            cout << "----------------------------------------------------------------------------" << endl;
        }

        system("pause");
        system("cls");
    }

    void activate_new_account() {
        system("cls");
        int choice = 0;
        string name, id, password, gender, class_id;
        Teacher newTeacher;
        Student newStudent;

        do {
            cout << "============================================================================" << endl;
            cout << "                            ACTIVATE NEW ACCOUNT                            " << endl;
            cout << "============================================================================" << endl;
            cout << "    [1] Activate New Teacher Account" << endl;
            cout << "    [2] Activate New Student Account" << endl;
            cout << "    [3] Back to Main Menu" << endl;
            cout << "============================================================================" << endl;
        RECHOICE:
            cout << "    Please Enter Your Choice: ";
            cin >> choice;
            if (cin.fail()) {
                cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto RECHOICE;
            } else if (choice < 1 || choice > 3) {
                cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
                goto RECHOICE;
            }

            if (choice == 3) {
                system("cls");
                return;
            }

            cout << "    Enter Name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);

            cout << "    Enter ID: ";
            getline(cin, id);

            cout << "    Enter Password: ";
            getline(cin, password);

            cout << "    Enter Gender: ";
            getline(cin, gender);

            cout << "    Enter Class: ";
            getline(cin, class_id);

            if (choice == 1) {
                newTeacher = Teacher("T", id, name, password, gender, class_id);
                vTea.push_back(newTeacher);
                save_teacher();
                cout << "\033[1;32m    New Teacher Account Activated Successfully!\033[0m" << endl;
            } else if (choice == 2) {
                newStudent = Student("S", id, name, password, gender, class_id);
                vStu.push_back(newStudent);
                save_student();
                cout << "\033[1;32m    New Student Account Activated Successfully!\033[0m" << endl;
            }

            system("pause");
            system("cls");
        } while (true);
    }

    void deactivate_exist_account() {
        system("cls");
        int choice = 0;
        string user_id;
        do {
            cout << "============================================================================" << endl;
            cout << "                           DEACTIVATE EXISTING ACCOUNT                      " << endl;
            cout << "============================================================================" << endl;
            cout << "    [1] Deactivate Teacher Account" << endl;
            cout << "    [2] Deactivate Student Account" << endl;
            cout << "    [3] Back to Main Menu" << endl;
            cout << "============================================================================" << endl;
        RECHOICE:
            cout << "    Please Enter Your Choice: ";
            cin >> choice;
            if (cin.fail()) {
                cout << "\033[1;31m    Invalid Input. Please Enter a Number.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto RECHOICE;
            } else if (choice < 1 || choice > 3) {
                cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
                goto RECHOICE;
            }

            if (choice == 3) {
                system("cls");
                return;
            }

            cout << "    Enter User ID: ";
            cin >> user_id;

            if (choice == 1) {
                auto it = remove_if(vTea.begin(), vTea.end(), [&](const Teacher &t) { return t.m_id == user_id; });
                if (it != vTea.end()) {
                    vTea.erase(it, vTea.end());
                    save_teacher();
                    cout << "\033[1;32m    Teacher Account Deactivated Successfully!\033[0m" << endl;
                } else {
                    cout << "\033[1;31m    Teacher ID Not Found!\033[0m" << endl;
                }
            } else if (choice == 2) {
                auto it = remove_if(vStu.begin(), vStu.end(), [&](const Student &s) { return s.m_id == user_id; });
                if (it != vStu.end()) {
                    vStu.erase(it, vStu.end());
                    save_student();
                    cout << "\033[1;32m    Student Account Deactivated Successfully!\033[0m" << endl;
                } else {
                    cout << "\033[1;31m    Student ID Not Found!\033[0m" << endl;
                }
            }

            system("pause");
            system("cls");
        } while (true);
    }

    void init_vector() {
        ifstream file("user.txt", ios::in);
        if (!file.is_open()) {
            cout << "File Not Found" << endl;
        }

        while (!file.eof()) {
            string user_type, user_id, user_name, user_password, user_gender, user_class;
            file >> user_type >> user_id >> user_name >> user_password >> user_gender >> user_class;

            if (user_type == "T") {
                Teacher teacher(user_type, user_id, user_name, user_password, user_gender, user_class);
                vTea.push_back(teacher);
            } else if (user_type == "S") {
                Student student(user_type, user_id, user_name, user_password, user_gender, user_class);
                vStu.push_back(student);
            }
        }
    }

    void save_teacher() {
        ofstream ofs("user.txt", ios::out);
        for (auto &teacher : vTea) {
            ofs << teacher.m_type << " " << teacher.m_id << " " << teacher.m_name << " " << teacher.m_password << " " << teacher.m_gender << " " << teacher.m_class << endl;
        }
        ofs.close();
    }

    void save_student() {
        ofstream ofs("user.txt", ios::out);
        for (auto &student : vStu) {
            ofs << student.m_type << " " << student.m_id << " " << student.m_name << " " << student.m_password << " " << student.m_gender << " " << student.m_class << endl;
        }
        ofs.close();
    }

    vector<Teacher> vTea;
    vector<Student> vStu;
};

// 登录功能函数
void Login_in(string file, string &type, string &id, string &name, string &password, string &gender, string &class_id) {
    ifstream input(file, ios::in);
    if (!input.is_open()) {
        cout << "\033[1;31mFile Not Found!\033[0m" << endl;
        return;
    }

    while (!input.eof()) {
        string user_type, user_id, user_name, user_password, user_gender, user_class;
        input >> user_type >> user_id >> user_name >> user_password >> user_gender >> user_class;

        if (user_id == id && user_password == password) {
            type = user_type;
            name = user_name;
            gender = user_gender;
            class_id = user_class;
            input.close();
            return;
        }
    }

    type = "";
    name = "";
    gender = "";
    class_id = "";

    input.close();
}

// 创建管理员用户
void create_admin_user(const string &file, const string &name, const string &password) {
    ofstream output(file, ios::out | ios::app);
    output << "A " << "admin" << " " << name << " " << password << " admin" << " admin" << endl;
    output.close();
}

// 快速排序函数
void quickSort(vector<StudentInfo> &students, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(students, low, high);
        quickSort(students, low, pivotIndex - 1);
        quickSort(students, pivotIndex + 1, high);
    }
}

int partition(vector<StudentInfo> &students, int low, int high) {
    float pivot = calculateAverage(students[high]);
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (calculateAverage(students[j]) > pivot) {
            i++;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}

// 二分查找函数
int binarySearch(const vector<StudentInfo> &students, const string &id) {
    int left = 0;
    int right = students.size() - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;
        if (students[middle].studentId == id) {
            return middle;
        }
        if (students[middle].studentId < id) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return -1;
}

// 计算学生平均成绩
float calculateAverage(const StudentInfo &student) {
    float sum = accumulate(student.grades.begin(), student.grades.end(), 0.0f);
    return sum / student.grades.size();
}

// 计算班级平均成绩
unordered_map<string, float> calculateClassAverage(const vector<StudentInfo> &students) {
    unordered_map<string, float> classAverages;
    unordered_map<string, int> classCounts;

    for (const auto &student : students) {
        float average = calculateAverage(student);
        classAverages[student.studentClass] += average;
        classCounts[student.studentClass]++;
    }

    for (auto &entry : classAverages) {
        entry.second /= classCounts[entry.first];
    }

    return classAverages;
}

// 主函数
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    string user_type, user_id, user_name, user_password, user_gender, user_class;

    cout << "Please Enter Your ID: ";
    cin >> user_id;
    cout << "Please Enter Your Password: ";
    cin >> user_password;

    Login_in("user.txt", user_type, user_id, user_name, user_password, user_gender, user_class);
    if (user_type == "A") {
        Admin admin(user_name, user_password);
        admin.open_menu();
    } else if (user_type == "T") {
        Teacher teacher(user_type, user_id, user_name, user_password, user_gender, user_class);
        teacher.open_menu();
    } else if (user_type == "S") {
        Student student(user_type, user_id, user_name, user_password, user_gender, user_class);
        student.open_menu();
    } else {
        char choice;
        cout << "\033[1;31mInvalid Credentials! Please try again. \033[0m" << endl;
        cout << "Do you want to try again? (Y/N): ";
        cin >> choice;
        while (choice == 'y' || choice == 'Y') {
            system("cls");
            cout << "Please Enter Your ID: ";
            cin >> user_id;
            cout << "Please Enter Your Password: ";
            cin >> user_password;
            Login_in("user.txt", user_type, user_id, user_name, user_password, user_gender, user_class);

            if (user_type == "A") {
                Admin admin(user_name, user_password);
                admin.open_menu();
                break;
            } else if (user_type == "T") {
                Teacher teacher(user_type, user_id, user_name, user_password, user_gender, user_class);
                teacher.open_menu();
                break;
            } else if (user_type == "S") {
                Student student(user_type, user_id, user_name, user_password, user_gender, user_class);
                student.open_menu();
                break;
            } else {
                cout << "\033[1;31mInvalid Credentials! Please try again. \033[0m" << endl;
                cout << "Do you want to try again? (Y/N): ";
                cin >> choice;
            }
        }
    }
    return 0;
}
