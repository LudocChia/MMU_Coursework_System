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
#include <unordered_map>
#include <conio.h>
#include <windows.h>
#include <sstream>

using namespace std;

struct AwardNode
{
    string award;
    AwardNode *next;

    AwardNode(const string &a) : award(a), next(nullptr) {}
    // Constructor initializes the award and sets the next pointer to null.
};

struct AwardLinkedList
{
    AwardNode *head;

    AwardLinkedList() : head(nullptr) {}
    // Constructor initializes the award and sets the next pointer to null.

    void addAward(const string &newAward)
    {
        AwardNode *newNode = new AwardNode(newAward);
        newNode->next = head;
        head = newNode;
        // Adds a new award to the start of the linked list.
    }

    void printAwards() const
    {
        AwardNode *current = head;
        while (current != nullptr)
        {
            cout << current->award << endl;
            current = current->next;
            // Prints all awards in the linked list.
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
                // Deletes an award from the linked list if it matches the targetAward.
            }
            prev = current;
            current = current->next;
        }
        return false;
        // Returns false if the award is not found.
    }

    ~AwardLinkedList()
    {
        while (head != nullptr)
        {
            AwardNode *temp = head;
            head = head->next;
            delete temp;
            // Destructor deallocates all nodes in the linked list.
        }
    }
};

struct CommentNode
{
    string comment;
    CommentNode *next;

    CommentNode(const string &c) : comment(c), next(nullptr) {}
    // Constructor initializes the comment and sets the next pointer to null.
};

struct CommentLinkedList
{
    CommentNode *head;

    CommentLinkedList() : head(nullptr) {}
    // Constructor initializes the head pointer to null.

    void addComment(const string &newComment)
    {
        CommentNode *newNode = new CommentNode(newComment);
        newNode->next = head;
        head = newNode;
        // Adds a new comment to the start of the linked list.
    }

    void printComments() const
    {
        CommentNode *current = head;
        while (current != nullptr)
        {
            cout << current->comment << endl;
            current = current->next;
            // Prints all comments in the linked list.
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
                // Deletes a comment from the linked list if it matches the targetComment.
            }
            prev = current;
            current = current->next;
        }
        return false;
        // Returns false if the comment is not found.
    }

    ~CommentLinkedList()
    {
        while (head != nullptr)
        {
            CommentNode *temp = head;
            head = head->next;
            delete temp;
            // Destructor deallocates all nodes in the linked list.
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
    unordered_map<string, SubjectNode *> codeMap;
    unordered_map<string, SubjectNode *> nameMap;

    SubjectLinkedList() : head(nullptr) {}

    void addSubject(const string &code, const string &name, const vector<string> &classes)
    {
        SubjectNode *newNode = new SubjectNode(code, name, classes);
        newNode->next = head;
        head = newNode;
        codeMap[code] = newNode;
        nameMap[name] = newNode;
    }

    void printSubjects() const
    {
        SubjectNode *current = head;
        while (current != nullptr)
        {
            cout << left << setw(15) << current->subjectCode << setw(20) << current->subjectName;
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
                codeMap.erase(current->subjectCode);
                nameMap.erase(current->subjectName);
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

    void mergeSort(int criteria, bool ascending)
    {
        head = mergeSortRec(head, criteria, ascending);
    }

    SubjectNode *mergeSortRec(SubjectNode *node, int criteria, bool ascending)
    {
        if (!node || !node->next)
            return node;

        SubjectNode *middle = getMiddle(node);
        SubjectNode *nextOfMiddle = middle->next;

        middle->next = nullptr;

        SubjectNode *left = mergeSortRec(node, criteria, ascending);
        SubjectNode *right = mergeSortRec(nextOfMiddle, criteria, ascending);

        return merge(left, right, criteria, ascending);
    }

    SubjectNode *merge(SubjectNode *left, SubjectNode *right, int criteria, bool ascending)
    {
        if (!left)
            return right;

        if (!right)
            return left;

        bool condition;
        switch (criteria)
        {
        case 1:
            condition = ascending ? (left->subjectCode < right->subjectCode) : (left->subjectCode > right->subjectCode);
            break;
        case 2:
            condition = ascending ? (left->subjectName < right->subjectName) : (left->subjectName > right->subjectName);
            break;
        default:
            condition = true;
            break;
        }

        SubjectNode *result = nullptr;
        if (condition)
        {
            result = left;
            result->next = merge(left->next, right, criteria, ascending);
        }
        else
        {
            result = right;
            result->next = merge(left, right->next, criteria, ascending);
        }
        return result;
    }

    SubjectNode *getMiddle(SubjectNode *node)
    {
        if (!node)
            return node;

        SubjectNode *slow = node;
        SubjectNode *fast = node->next;

        while (fast != nullptr)
        {
            fast = fast->next;
            if (fast != nullptr)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }
        return slow;
    }

    bool search(int criteria, const string &target)
    {
        SubjectNode *result = nullptr;
        switch (criteria)
        {
        case 1:
            if (codeMap.find(target) != codeMap.end())
                result = codeMap[target];
            break;
        case 2:
            if (nameMap.find(target) != nameMap.end())
                result = nameMap[target];
            break;
        }

        if (result)
        {
            cout << left << setw(15) << result->subjectCode << setw(20) << result->subjectName;
            for (const auto &cls : result->subjectClasses)
            {
                cout << cls << " ";
            }
            cout << endl;
            return true;
        }
        return false;
    }
};

struct StudentInfo
{
    string studentId;
    string studentClass;
    string studentName;
    CommentLinkedList comments;
    AwardLinkedList awards;
    vector<float> grades;
    float attendancePercentage;

    StudentInfo() : attendancePercentage(0.0)
    {
        grades.resize(21, 0.0);
        // Constructor initializes attendancePercentage to 0.0 and resizes grades vector to 21 with all elements set to 0.0.
    }
};

void clearInputStream()
{
    cin.clear();
    while (cin.get() != '\n')
        ;
    // Clears the input stream to handle invalid inputs.
}

class Identity
{
public:
    virtual void open_menu() = 0;
    // Pure virtual function to open a menu. Must be overridden by derived classes.

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
    // Virtual destructor to ensure proper cleanup in derived classes.
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
        // Constructor to initialize a Teacher object with given parameters.
    }

    void loadStudentGradeAttendance(const string &filename, vector<StudentInfo> &students, SubjectLinkedList &subjects)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Failed to open " << filename << endl;
            return;
            // Opens the file and reads student grades and attendance data.
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            StudentInfo student;
            string gradeStr;

            getline(ss, student.studentId, '|');
            getline(ss, student.studentClass, '|');

            // Load the subjects for the student's class
            vector<pair<string, string>> subjectsForClass;
            loadSubjectsForClass(student.studentClass, subjectsForClass);

            // Read the grades for each subject and term
            student.grades.clear();
            for (size_t i = 0; i < subjectsForClass.size() * 3; ++i)
            { // 3 terms (First Term, Midterm, Final)
                if (getline(ss, gradeStr, '|'))
                {
                    if (gradeStr == "-1")
                    {
                        student.grades.push_back(-1.0f);
                    }
                    else
                    {
                        student.grades.push_back(stof(gradeStr));
                    }
                }
            }

            // Read the attendance percentage
            if (getline(ss, gradeStr, '|'))
            {
                student.attendancePercentage = stof(gradeStr);
            }

            students.push_back(student);
        }

        file.close();
    }

    void saveStudentGradeAttendance(const vector<StudentInfo> &students, const string &filename, const SubjectLinkedList &subjects)
    {
        ofstream file(filename);

        for (const auto &student : students)
        {
            file << student.studentId << "|" << student.studentClass;
            vector<pair<string, string>> subjectsForClass;
            loadSubjectsForClass(student.studentClass, subjectsForClass);
            size_t gradeIndex = 0;

            // Write the grades for each subject and term
            for (size_t i = 0; i < subjectsForClass.size() * 3; ++i)
            { // 3 terms (First Term, Midterm, Final)
                if (gradeIndex < student.grades.size())
                {
                    file << "|" << student.grades[gradeIndex++];
                }
                else
                {
                    file << "|-1"; // if there are no grades, use -1 as placeholder
                }
            }

            file << "|" << student.attendancePercentage << "\n";
        }

        file.close();
    }

    void saveStudentComments(const vector<StudentInfo> &students, const string &filename)
    {
        ofstream file(filename);

        // Writes all comments for each student to the file.
        for (const auto &student : students)
        {
            CommentNode *current = student.comments.head;
            while (current != nullptr)
            {
                file << student.studentId << "|" << student.studentClass << "|" << current->comment << "\n";
                current = current->next;
            }
        }

        file.close();
        // Closes the file after saving.
    }

    // Opens the file and reads student comments.
    void loadStudentComments(const string &filename, vector<StudentInfo> &students)
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
            getline(ss, comment, '|');

            auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                              { return s.studentId == studentId; });

            // Adds the comment to the corresponding student.
            if (it != students.end())
            {
                it->comments.addComment(comment);
            }
        }
        // Closes the file after reading.
        file.close();
    }

    // Opens the file and reads student awards.
    void loadStudentAwards(const string &filename, vector<StudentInfo> &students)
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
            getline(ss, award, '|');

            auto it = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                              { return s.studentId == studentId; });

            // Adds the award to the corresponding student.
            if (it != students.end())
            {
                it->awards.addAward(award);
            }
        }
        // Closes the file after reading.
        file.close();
    }

    // Writes all awards for each student to the file.
    void saveStudentAwards(const vector<StudentInfo> &students, const string &filename)
    {
        ofstream file(filename);

        for (const auto &student : students)
        {
            AwardNode *current = student.awards.head;
            while (current != nullptr)
            {
                file << student.studentId << "|" << current->award << "\n";
                current = current->next;
            }
        }

        file.close();
    }

    // Converts numerical grade to letter grade.
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

    // Provides a menu for teachers to update student information, view grades and attendance, and manage comments and awards.
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

    // Loads subjects that belong to the specified class from a file.
    void loadSubjectsForClass(const string &className, vector<pair<string, string>> &subjectsForClass)
    {
        ifstream subjectsFile("subjects.txt");
        string line;
        while (getline(subjectsFile, line))
        {
            stringstream ss(line);
            string subjectCode, subjectName, classList;
            getline(ss, subjectCode, '|');
            getline(ss, subjectName, '|');
            while (getline(ss, classList, '|'))
            {
                if (classList == className)
                {
                    subjectsForClass.push_back({subjectCode, subjectName});
                    break;
                }
            }
        }
    }
    // Converts a vector of subjects to a linked list of subjects.
    void convertSubjectsForClassToLinkedList(const vector<pair<string, string>> &subjectsForClass, SubjectLinkedList &subjectsLinkedList)
    {
        subjectsLinkedList.head = nullptr;
        SubjectNode *current = nullptr;

        for (const auto &subject : subjectsForClass)
        {
            SubjectNode *newNode = new SubjectNode(subject.first, subject.second, vector<string>());
            newNode->next = nullptr;

            if (subjectsLinkedList.head == nullptr)
            {
                subjectsLinkedList.head = newNode;
            }
            else
            {
                current->next = newNode;
            }

            current = newNode;
        }
    }

    // Loads users from a file and stores them in the teachers vector and studentNames map.
    void loadUsers(const string &filename, vector<Teacher> &teachers, unordered_map<string, string> &studentNames)
    {
        ifstream file(filename);
        string line, userType, id, name, password, gender, classId;
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, userType, '|');
            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, password, '|');
            getline(ss, gender, '|');
            getline(ss, classId, '|');
            if (userType == "1")
            { // Teacher
                teachers.emplace_back(userType, id, name, password, gender, classId);
            }
            else if (userType == "2")
            { // Student
                studentNames[id] = name;
                teachers.emplace_back(userType, id, name, password, gender, classId);
            }
        }
        file.close();
    }

    void update_student_grades()
    {
        vector<StudentInfo> students;
        SubjectLinkedList subjects;
        Teacher::loadStudentGradeAttendance("gradeAttendance.txt", students, subjects);

        string studentId;
        bool studentFound = false;

        while (!studentFound)
        {
            system("cls");
            cout << "============================================================================" << endl;
            cout << "                            UPDATE STUDENT MARKS" << endl;
            cout << "============================================================================" << endl;
            cout << "Enter the student ID to update: ";
            cin >> studentId;

            auto studentIt = find_if(students.begin(), students.end(), [&](const StudentInfo &s)
                                     { return s.studentId == studentId && s.studentClass == this->m_class; });//search student
            if (studentIt == students.end())
            {
                cout << "\033[1;31mStudent not found or not in your class. Please try again.\033[0m\n";
                char tryAgain;
                cout << "Do you want to try again? (Y/N): ";
                cin >> tryAgain;
                if (tryAgain != 'y' && tryAgain != 'Y')
                {
                    return;
                }
            }
            else
            {
                studentFound = true;

                vector<pair<string, string>> subjectsForClass;
                loadSubjectsForClass(this->m_class, subjectsForClass);//search subject for certain class

                bool continueUpdating = true;
                while (continueUpdating)
                {
                    system("cls");
                    cout << "============================================================================" << endl;
                    cout << "                            UPDATE STUDENT MARKS" << endl;
                    cout << "============================================================================" << endl;
                    cout << "Select the term to update marks\n";
                    cout << "[1] First Term Exam\n";
                    cout << "[2] Midterm Exam\n";
                    cout << "[3] Final Exam\n";
                    cout << "[4] Back to Main Menu\n";
                    cout << "----------------------------------------------------------------------------" << endl;
                    cout << "Enter your choice: ";
                    int termChoice;
                    cin >> termChoice;

                    int gradeOffset;
                    switch (termChoice)
                    {
                    case 1:
                        gradeOffset = 0;//set at zero
                        break;
                    case 2:
                        gradeOffset = subjectsForClass.size();//set to num of subject 
                        break;
                    case 3:
                        gradeOffset = 2 * subjectsForClass.size();//set twice
                        break;
                    case 4:
                        return;
                    default:
                        cout << "\033[1;31mInvalid choice. Please enter a number between 1 and 4.\033[0m\n";
                        return;
                    }

                    StudentInfo &student = *studentIt;// get a reference to the student object from the iterator
                    system("cls");
                    cout << "============================================================================" << endl;
                    cout << "                            UPDATE STUDENT MARKS" << endl;
                    cout << "============================================================================" << endl;
                    cout << "Current grades for " << studentId << ":\n";
                    for (size_t i = 0; i < subjectsForClass.size(); ++i)
                    {
                        int index = gradeOffset + i;// calculate the grade index based on the offset
                        cout << "[" << (i + 1) << "] " << subjectsForClass[i].second << ": ";
                        if (index < student.grades.size())// check if the index is within the student's grades size
                        {
                            if (student.grades[index] == -1.0f)
                            {
                                cout << "-\n";
                            }
                            else
                            {
                                cout << student.grades[index] << "\n";
                            }
                        }
                        else
                        {
                            cout << "N/A\n";
                        }
                    }

                    cout << "----------------------------------------------------------------------------" << endl;
                    cout << "Select the number to update the mark of the subject (1-" << subjectsForClass.size() << ") : ";
                    int subjectChoice;
                    cin >> subjectChoice;

                    while (cin.fail() || subjectChoice < 1 || subjectChoice > static_cast<int>(subjectsForClass.size()))
                    {
                        cout << "\033[1;31mInvalid subject choice. Please enter a number between 1 and " << subjectsForClass.size() << ".\033[0m\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Select the correct subject code to update the marks (1-" << subjectsForClass.size() << ") : ";
                        cin >> subjectChoice;
                    }

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Enter the new mark (or press Enter to skip): ";
                    string input;
                    getline(cin, input);

                    if (input.empty())
                    {
                        cout << "\033[1;33mUpdate skipped.\033[0m\n";
                    }
                    else
                    {
                        float newGrade;
                        stringstream ss(input);
                        ss >> newGrade;

                        while (ss.fail() || newGrade < 0 || newGrade > 100)
                        {
                            cout << "\033[1;31mInvalid marks. Please enter a valid number between 0 and 100.\033[0m\n";
                            ss.clear();
                            ss.str("");
                            getline(cin, input);
                            if (input.empty())
                            {
                                cout << "\033[1;33mUpdate skipped.\033[0m\n";
                                break;
                            }
                            ss.str(input);
                            ss >> newGrade;
                        }

                        if (!ss.fail() && newGrade >= 0 && newGrade <= 100)
                        {
                            student.grades[gradeOffset + subjectChoice - 1] = newGrade;
                            cout << "\033[1;32mMarks updated successfully!\033[0m\n";
                        }
                    }

                    SubjectLinkedList subjectsLinkedList;
                    convertSubjectsForClassToLinkedList(subjectsForClass, subjectsLinkedList);
                    saveStudentGradeAttendance(students, "gradeAttendance.txt", subjectsLinkedList);

                    char updateAnother;
                    cout << "Do you want to update another subject mark for this student? (Y/N): ";
                    cin >> updateAnother;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    while (updateAnother != 'y' && updateAnother != 'Y' && updateAnother != 'n' && updateAnother != 'N')
                    {
                        cout << "\033[1;31mPlease enter Y or N only.\033[0m\n\nPlease enter again (Y/N): ";
                        cin >> updateAnother;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    if (updateAnother != 'y' && updateAnother != 'Y')
                    {
                        continueUpdating = false;
                    }
                }
            }
        }
    } // end of student grade

    void update_student_attendance()
    {
        vector<StudentInfo> students;
        SubjectLinkedList subjects;
        loadStudentGradeAttendance("gradeAttendance.txt", students, subjects);

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
                saveStudentGradeAttendance(students, "gradeAttendance.txt", subjects);
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
        SubjectLinkedList subjects;
        vector<Teacher> teachers;
        unordered_map<string, string> studentNames;
        loadStudentGradeAttendance("gradeAttendance.txt", students, subjects);
        loadUsers("user.txt", teachers, studentNames);

        while (true)
        {
            clearScreen();
            int termChoice;
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

                if (termChoice < 1 || termChoice > 4)
                {
                    cout << "\033[1;31m    Invalid choice. Please enter again. \033[0m" << endl;
                }
            } while (termChoice < 1 || termChoice > 4);

            if (termChoice == 4)
            {
                clearScreen();
                return;
            }

            vector<pair<string, string>> subjectsForClass;
            loadSubjectsForClass(this->m_class, subjectsForClass);

            clearScreen();
            cout << "===================================================================================================================================" << endl;
            cout << "                                                    CLASS " << this->m_class << " MARKS AND ATTENDANCE" << endl;
            cout << "===================================================================================================================================" << endl;

            cout << left << setw(5) << "No." << setw(15) << "Student ID" << setw(25) << "Student Name" << setw(10) << "Class" << setw(15) << "Subject" << setw(15) << "Mark" << setw(10) << "Grade" << setw(20) << "Attendance (%)" << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;

            int studentNo = 1;
            for (const auto &student : students)
            {
                if (student.studentClass == this->m_class)
                {
                    bool firstSubject = true;
                    for (size_t i = 0; i < subjectsForClass.size(); ++i)
                    {
                        if (firstSubject)
                        {
                            cout << setw(5) << studentNo << setw(15) << student.studentId << setw(25) << studentNames[student.studentId] << setw(10) << student.studentClass << setw(15) << subjectsForClass[i].second;
                            firstSubject = false;
                        }
                        else
                        {
                            cout << setw(5) << "" << setw(15) << "" << setw(25) << "" << setw(10) << "" << setw(15) << subjectsForClass[i].second;
                        }

                        int gradeIndex = (termChoice - 1) * subjectsForClass.size() + i;
                        if (student.grades.size() > gradeIndex && student.grades[gradeIndex] == -1)
                        {
                            cout << setw(15) << "-" << setw(10) << "-";
                        }
                        else if (student.grades.size() > gradeIndex)
                        {
                            if (student.grades[gradeIndex] >= 40)
                            {
                                cout << "\033[1;32m"; // Green color for grades >= 40
                            }
                            else
                            {
                                cout << "\033[1;31m"; // Red color for grades < 40
                            }
                            cout << setw(15) << student.grades[gradeIndex] << setw(10) << getGradeLetter(student.grades[gradeIndex]);
                            cout << "\033[0m"; // Reset color
                        }
                        else
                        {
                            cout << setw(15) << "-" << setw(10) << "-";
                        }

                        if (i == 0)
                        {
                            cout << setw(20) << student.attendancePercentage;
                        }
                        cout << endl;
                    }
                    cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                    studentNo++;
                }
            }
            cout << "-----------------------------------------------------------------------------------------------------------------------------" << endl;

            sortAndDisplayStudents(students, studentNames, subjectsForClass, termChoice);
        }
    } // end of view class and attendance

    void sortAndDisplayStudents(vector<StudentInfo> &students, unordered_map<string, string> &studentNames, const vector<pair<string, string>> &subjectsForClass, int termChoice)
    {
        while (true)
        {
            int sortChoice;
            cout << "Would you like to sort the students? [1] Yes [2] No: ";
            cin >> sortChoice;
            if (sortChoice != 1)
            {
                return;
            }

            clearScreen();
            int criterionChoice;
            cout << "Choose criterion for sorting:" << endl;
            cout << "[1] Student ID" << endl;
            cout << "[2] Student Name" << endl;
            cout << "[3] Attendance Percentage" << endl;
            cout << "[4] Subject" << endl;
            cout << "Enter your choice: ";
            cin >> criterionChoice;

            int subjectChoice = -1;
            if (criterionChoice == 4)
            {
                clearScreen();
                cout << "Choose the subject to sort by:\n";
                for (size_t i = 0; i < subjectsForClass.size(); ++i)
                {
                    cout << "[" << (i + 1) << "] " << subjectsForClass[i].second << endl;
                }
                cout << "Enter your choice: ";
                cin >> subjectChoice;
                if (subjectChoice < 1 || subjectChoice > static_cast<int>(subjectsForClass.size()))
                {
                    cout << "\033[1;31mInvalid subject choice. Please enter a number between 1 and " << subjectsForClass.size() << ".\033[0m\n";
                    continue;
                }
                subjectChoice--; // to make it zero-based index
            }

            quickSort(students, 0, students.size() - 1, criterionChoice, true, studentNames, termChoice, subjectChoice, subjectsForClass.size());

            clearScreen();
            cout << "===================================================================================================================================" << endl;
            cout << "                                                    CLASS " << this->m_class << " MARKS AND ATTENDANCE (Sorted)" << endl;
            cout << "===================================================================================================================================" << endl;

            cout << left << setw(5) << "No." << setw(15) << "Student ID" << setw(25) << "Student Name" << setw(10) << "Class" << setw(15) << "Subject" << setw(15) << "Mark" << setw(10) << "Grade" << setw(20) << "Attendance (%)" << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;

            int studentNo = 1;
            for (const auto &student : students)
            {
                if (student.studentClass == this->m_class)
                {
                    bool firstSubject = true;
                    for (size_t i = 0; i < subjectsForClass.size(); ++i)
                    {
                        if (criterionChoice == 4 && i != subjectChoice)
                            continue; // Show only the selected subject

                        if (firstSubject)
                        {
                            cout << setw(5) << studentNo << setw(15) << student.studentId << setw(25) << studentNames[student.studentId] << setw(10) << student.studentClass << setw(15) << subjectsForClass[i].second;
                            firstSubject = false;
                        }
                        else
                        {
                            cout << setw(5) << "" << setw(15) << "" << setw(25) << "" << setw(10) << "" << setw(15) << subjectsForClass[i].second;
                        }

                        int gradeIndex = (termChoice - 1) * subjectsForClass.size() + i;
                        if (student.grades.size() > gradeIndex && student.grades[gradeIndex] == -1)
                        {
                            cout << setw(15) << "-" << setw(10) << "-";
                        }
                        else if (student.grades.size() > gradeIndex)
                        {
                            if (student.grades[gradeIndex] >= 40)
                            {
                                cout << "\033[1;32m"; // Green color for grades >= 40
                            }
                            else
                            {
                                cout << "\033[1;31m"; // Red color for grades < 40
                            }
                            cout << setw(15) << student.grades[gradeIndex] << setw(10) << getGradeLetter(student.grades[gradeIndex]);
                            cout << "\033[0m"; // Reset color
                        }
                        else
                        {
                            cout << setw(15) << "-" << setw(10) << "-";
                        }

                        if (i == 0 || criterionChoice == 4)
                        {
                            cout << setw(20) << student.attendancePercentage;
                        }
                        cout << endl;
                    }
                    cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                    studentNo++;
                }
            }
            cout << "-----------------------------------------------------------------------------------------------------------------------------" << endl;
        }
    }

    void quickSort(vector<StudentInfo> &students, int left, int right, int criterion, bool ascending, unordered_map<string, string> &studentNames, int termChoice, int subjectChoice, int numSubjects)
    {
        if (left < right)
        {
            // partition the array to get the pivot
            int pivotIndex = partition(students, left, right, criterion, ascending, studentNames, termChoice, subjectChoice, numSubjects);

            // repeat sort elements before and after partition
            quickSort(students, left, pivotIndex - 1, criterion, ascending, studentNames, termChoice, subjectChoice, numSubjects);
            quickSort(students, pivotIndex + 1, right, criterion, ascending, studentNames, termChoice, subjectChoice, numSubjects);
        }
    }

    int partition(vector<StudentInfo> &students, int left, int right, int criterion, bool ascending, unordered_map<string, string> &studentNames, int termChoice, int subjectChoice, int numSubjects)
    {
        // choose the rightmost element as the pivot
        StudentInfo pivot = students[right];
        // index of smaller element
        int i = left - 1;

        // calculate grade index for the current term and subject
        int gradeIndexJ = (termChoice - 1) * numSubjects + subjectChoice;
        int gradeIndexPivot = (termChoice - 1) * numSubjects + subjectChoice;

        // loop through the array and rearrange element based on the pivot
        for (int j = left; j < right; j++)
        {
            bool compare = false;
            switch (criterion)
            {
            case 1: // student id
                compare = (ascending ? students[j].studentId < pivot.studentId : students[j].studentId > pivot.studentId);
                break;
            case 2: // student name
                compare = (ascending ? studentNames[students[j].studentId] < studentNames[pivot.studentId] : studentNames[students[j].studentId] > studentNames[pivot.studentId]);
                break;
            case 3: // percentage
                compare = (ascending ? students[j].attendancePercentage < pivot.attendancePercentage : students[j].attendancePercentage > pivot.attendancePercentage);
                break;
            case 4: // grade
                compare = (ascending ? students[j].grades[gradeIndexJ] < pivot.grades[gradeIndexPivot] : students[j].grades[gradeIndexJ] > pivot.grades[gradeIndexPivot]);
                break;
            default:
                break;
            }

            // if the element should be on the left of the pivot, swap it
            if (compare)
            {
                i++;
                swap(students[i], students[j]);
            }
        }
        swap(students[i + 1], students[right]);
        return i + 1; // return the index of the pivot
    }

    void clearScreen()
    {
        cout << "\033[2J\033[1;1H";
    }

    // for 4, hash search not complete yet, still fixing
    void merge(vector<pair<float, string>> &grades, int left, int mid, int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<pair<float, string>> L(n1);
        vector<pair<float, string>> R(n2);

        for (int i = 0; i < n1; i++)
            L[i] = grades[left + i];
        for (int i = 0; i < n2; i++)
            R[i] = grades[mid + 1 + i];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2)
        {
            if (L[i].first <= R[j].first)
            {
                grades[k] = L[i];
                i++;
            }
            else
            {
                grades[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            grades[k] = L[i];
            i++;
            k++;
        }

        while (j < n2)
        {
            grades[k] = R[j];
            j++;
            k++;
        }
    }

    // Function to perform merge sort
    void mergeSort(vector<pair<float, string>> &grades, int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;
            mergeSort(grades, left, mid);
            mergeSort(grades, mid + 1, right);
            merge(grades, left, mid, right);
        }
    }

    // Function to perform hash-based search
    void hashSearchSubject(const StudentInfo &student, const vector<pair<string, string>> &subjectsForClass)
    {
        unordered_map<string, vector<float>> subjectGradesMap;

        // Populate the hash map with subject grades
        for (size_t i = 0; i < subjectsForClass.size(); ++i)
        {
            vector<float> grades;
            for (int term = 0; term < 3; ++term)
            {
                grades.push_back(student.grades[term * subjectsForClass.size() + i]);
            }
            subjectGradesMap[subjectsForClass[i].second] = grades;
        }

        string subjectName;
        cout << "Enter the subject name to search: ";
        cin.ignore();
        getline(cin, subjectName);

        auto it = subjectGradesMap.find(subjectName);
        if (it != subjectGradesMap.end())
        {
            cout << "----------------------------------------------------------------------------" << endl;
            cout << "Subject: " << subjectName << endl;
            cout << "First Term: " << fixed << setprecision(2) << (it->second[0] == -1 ? "-" : to_string(it->second[0])) << endl;
            cout << "Midterm: " << fixed << setprecision(2) << (it->second[1] == -1 ? "-" : to_string(it->second[1])) << endl;
            cout << "Final: " << fixed << setprecision(2) << (it->second[2] == -1 ? "-" : to_string(it->second[2])) << endl;
        }
        else
        {
            cout << "Subject not found." << endl;
        }
    }

    void student_attendance_and_grades()
    {
        vector<StudentInfo> students;
        SubjectLinkedList subjects;
        unordered_map<string, string> studentNames;
        loadStudentGradeAttendance("gradeAttendance.txt", students, subjects);

        vector<Teacher> teachers;
        loadUsers("user.txt", teachers, studentNames);

        cout << "=======================================================================================================" << endl;
        cout << "                                       View Grades and Attendance" << endl;
        cout << "=======================================================================================================" << endl;
        cout << "List of students in your class (" << this->m_class << "):" << endl;
        vector<string> studentIdsInClass;
        for (const auto &teacher : teachers)
        {
            if (teacher.m_type == "2" && teacher.m_class == this->m_class)
            {
                cout << "    ID: " << teacher.m_id << " | Name: " << teacher.m_name << endl;
                studentIdsInClass.push_back(teacher.m_id);
            }
        }
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
                cout << "\033[1;31m    Student not found or not in your class. Please make sure you enter the correct student ID. \033[0m" << endl;
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

        vector<pair<string, string>> subjectsForClass;
        loadSubjectsForClass(it->studentClass, subjectsForClass);

        string terms[3] = {"First Term Exam", "Midterm Exam", "Final Exam"};
        vector<pair<float, string>> allTermGrades; // Store all term grades here

        for (int term = 0; term < 3; ++term)
        {
            cout << "----------------------------------------------------------------------------" << endl;
            cout << "                       \033[1;34m" << "Marks for " << terms[term] << "\033[0m" << endl;
            cout << "----------------------------------------------------------------------------" << endl;
            cout << "    No.  " << left << setw(35) << "Subject" << setw(10) << "Marks" << setw(10) << "Grades " << endl;

            int gradeOffset = term * subjectsForClass.size();
            vector<pair<float, string>> termGrades;
            for (size_t i = 0; i < subjectsForClass.size(); ++i)
            {
                float grade = it->grades[gradeOffset + i];

                cout << "    " << i + 1 << ".   " << setw(36) << subjectsForClass[i].second << setw(11);
                if (grade == -1)
                {
                    cout << "-";
                }
                else
                {
                    cout << grade;
                }
                cout << setw(10) << getGradeLetter(grade) << endl;
                termGrades.push_back({grade, subjectsForClass[i].second});
            }
            allTermGrades.insert(allTermGrades.end(), termGrades.begin(), termGrades.end());
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

        // Ask user for sorting or searching
        cout << "Enter 1 for Merge Sort, 2 for Hash Search, or 3 to go back to menu: ";
        int sortChoice;
        cin >> sortChoice;

        if (sortChoice == 1)
        {
            cout << "Sorted Grades:" << endl;
            for (int term = 0; term < 3; ++term)
            {
                cout << "----------------------------------------------------------------------------" << endl;
                cout << "                       Sorted Marks for " << terms[term] << endl;
                cout << "----------------------------------------------------------------------------" << endl;
                cout << "    No.  " << left << setw(35) << "Subject" << setw(10) << "Marks" << setw(10) << "Grades " << endl;

                int gradeOffset = term * subjectsForClass.size();
                vector<pair<float, string>> termGrades;
                for (size_t i = 0; i < subjectsForClass.size(); ++i)
                {
                    float grade = it->grades[gradeOffset + i];
                    termGrades.push_back({grade, subjectsForClass[i].second});
                }

                mergeSort(termGrades, 0, termGrades.size() - 1);

                for (size_t i = 0; i < termGrades.size(); ++i)
                {
                    cout << "    " << i + 1 << ".   " << setw(36) << termGrades[i].second << setw(11) << termGrades[i].first << setw(10) << getGradeLetter(termGrades[i].first) << endl;
                }
            }

            // Ask user for comparison
            cout << "Do you want to compare marks across terms for the same subjects? (y/n): ";
            char compareChoice;
            cin >> compareChoice;
            if (compareChoice == 'y' || compareChoice == 'Y')
            {
                cout << "----------------------------------------------------------------------------" << endl;
                cout << "                Comparison of Marks across Terms for Same Subjects" << endl;
                cout << "----------------------------------------------------------------------------" << endl;
                cout << "    No.  " << left << setw(20) << "Subject" << setw(20) << "First Term" << setw(21.2) << "Midterm" << setw(21.2) << "Final" << endl;

                for (size_t i = 0; i < subjectsForClass.size(); ++i)
                {
                    cout << "    " << i + 1 << ".   " << setw(23) << subjectsForClass[i].second;
                    for (int term = 0; term < 3; ++term)
                    {
                        int gradeOffset = term * subjectsForClass.size();
                        float grade = it->grades[gradeOffset + i];
                        if (grade == -1)
                        {
                            cout << setw(20) << "-";
                        }
                        else
                        {
                            cout << setw(20) << grade;
                        }
                    }
                    cout << endl;
                }
            }
        }
        else if (sortChoice == 2)
        {
            hashSearchSubject(*it, subjectsForClass);
        }
        else
        {
            return;
        }

        system("pause");
    }
    // end of 4

    void update_student_comment()
    {
        vector<StudentInfo> students;
        SubjectLinkedList subjects;
        loadStudentGradeAttendance("gradeAttendance.txt", students, subjects);
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
        SubjectLinkedList subjects;
        loadStudentGradeAttendance("gradeAttendance.txt", students, subjects);
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

    // Constructor to initialize a Student object with given parameters.
    Student(string user_type, string user_id, string user_name, string user_password, string user_gender, string user_class)
    {
        this->m_type = user_type;
        this->m_id = user_id;
        this->m_name = user_name;
        this->m_password = user_password;
        this->m_gender = user_gender;
        this->m_class = user_class;
    }

    // Converts a numerical grade to a letter grade.
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

    // Displays the student menu and handles user input.
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

    // Loads subjects for a specific class from the file "subjects.txt".
    void loadSubjectsForClass(const string &className, vector<pair<string, string>> &subjectsForClass)
    {
        ifstream subjectsFile("subjects.txt");
        string line;
        while (getline(subjectsFile, line))
        {
            stringstream ss(line);
            string subjectCode, subjectName, classList;
            getline(ss, subjectCode, '|');
            getline(ss, subjectName, '|');
            while (getline(ss, classList, '|'))
            {
                if (classList == className)
                {
                    subjectsForClass.push_back({subjectCode, subjectName});
                    break;
                }
            }
        }
    }
    // Loads grades and attendance for a specific student from the file "gradeAttendance.txt".
    bool loadGradesForStudent(const string &studentId, vector<float> &grades, float &attendance)
    {
        ifstream gradesFile("gradeAttendance.txt");
        string line;
        while (getline(gradesFile, line))
        {
            stringstream ss(line);
            string id, studentClass;
            getline(ss, id, '|');
            if (id == studentId)
            {
                getline(ss, studentClass, '|');
                string gradeStr;
                while (getline(ss, gradeStr, '|'))
                {
                    if (gradeStr.find('.') != string::npos)
                    { // If it contains a dot, it's a float (attendance)
                        attendance = stof(gradeStr);
                    }
                    else
                    {
                        grades.push_back(stof(gradeStr));
                    }
                }
                return true;
            }
        }
        return false;
    }
    // Displays the exam result slip for the student.
    void view_exam_result_slip()
    {
        vector<pair<string, string>> subjectsForClass;
        loadSubjectsForClass(this->m_class, subjectsForClass);

        vector<float> grades;
        float attendance;
        bool found = loadGradesForStudent(this->m_id, grades, attendance);

        if (!found)
        {
            cout << "No data found for student." << endl;
            return;
        }

        int termChoice;
        cout << "============================================================================" << endl;
        cout << "                             VIEW EXAM RESULT SLIP " << endl;
        cout << "============================================================================" << endl;
        cout << "    Select the term to view results" << endl;
        cout << "    [1] First Term Exam" << endl;
        cout << "    [2] Midterm Exam" << endl;
        cout << "    [3] Final Exam" << endl;
        cout << "    [4] Back to Menu" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "    Enter your choice: ";
        cin >> termChoice;

        if (termChoice < 1 || termChoice > 4)
        {
            cout << "\033[1;31mInvalid choice. Returning to menu.\033[0m" << endl;
            system("pause");
            system("cls");
            return;
        }

        if (termChoice == 4)
        {
            return;
        }
        system("cls");
        cout << "============================================================================" << endl;
        cout << "                         EXAM RESULT SLIP                              " << endl;
        cout << "============================================================================" << endl;
        cout << "    Name : " << left << setw(30) << this->m_name << "Gender : " << this->m_gender << endl;
        cout << "    ID   : " << left << setw(30) << this->m_id << "Class  : " << this->m_class << endl;

        int termStartIndex = (termChoice - 1) * subjectsForClass.size();

        string terms[] = {"First Term Exam", "Midterm Exam", "Final Exam"};
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "\033[1;34m                     Marks for " << terms[termChoice - 1] << "\033[0m" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "No.  " << left << setw(20) << "Subject" << setw(10) << "Marks" << "Grades " << endl;
        cout << "----------------------------------------------------------------------------" << endl;

        float totalMarks = 0;
        for (size_t i = 0; i < subjectsForClass.size(); ++i)
        {
            int gradeIndex = termStartIndex + i;
            cout << i + 1 << ".   " << setw(20) << subjectsForClass[i].second;
            if (gradeIndex < grades.size())
            {
                string displayMark = (grades[gradeIndex] == -1.0f) ? "-" : to_string(static_cast<int>(grades[gradeIndex]));
                cout << setw(10) << displayMark << getGradeLetter(grades[gradeIndex]) << endl;
                if (grades[gradeIndex] != -1.0f)
                {
                    totalMarks += grades[gradeIndex];
                }
            }
            else
            {
                cout << setw(10) << "-" << "-" << endl;
            }
        }
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "Total marks for " << terms[termChoice - 1] << " : " << totalMarks << "/" << subjectsForClass.size() * 100 << endl;

        float termPercentage = (totalMarks / (subjectsForClass.size() * 100)) * 100;
        cout << "Percentage for " << terms[termChoice - 1] << "  : ";

        if (termPercentage < 50)
        {
            cout << "\033[1;31m";
        }
        else
        {
            cout << "\033[1;32m";
        }
        cout << fixed << setprecision(0) << termPercentage << "%" << "\033[0m" << endl;

        cout << "============================================================================" << endl;
        system("pause");
        system("cls");
    }
    // Loads all comments for a specific student from the file "comment.txt".
    vector<string> loadStudentComments_All(const string &studentId)
    {
        ifstream file("comment.txt");
        vector<string> comments;
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id, className, comment;
            getline(ss, id, '|');
            getline(ss, className, '|');
            getline(ss, comment, '|');
            if (id == studentId)
            {
                comments.push_back(comment);
            }
        }
        return comments;
    }
    // Loads all awards for a specific student from the file "awards.txt".
    vector<string> loadStudentAwards_New(const string &studentId)
    {
        ifstream file("awards.txt");
        vector<string> awards;
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id, award;
            getline(ss, id, '|');
            getline(ss, award, '|');
            if (id == studentId)
            {
                awards.push_back(award);
            }
        }
        return awards;
    }

    // Displays the report card for the student, including grades, attendance, comments, and awards.
    void view_report_card()
    {
        vector<pair<string, string>> subjectsForClass;
        loadSubjectsForClass_New(this->m_class, subjectsForClass);

        vector<float> grades;
        float attendance;
        bool found = loadGradesForStudent_New(this->m_id, grades, attendance);

        if (!found)
        {
            cout << "No data found for student." << endl;
            return;
        }

        vector<string> comments = loadStudentComments_All(this->m_id);

        vector<string> awards = loadStudentAwards_New(this->m_id);

        string terms[] = {"First Term Exam", "Midterm Exam", "Final Exam"};

        system("cls");
        cout << "========================================================================================" << endl;
        cout << "                                       REPORT CARD                                      " << endl;
        cout << "========================================================================================" << endl;
        cout << "    Name : " << left << setw(50) << this->m_name << "Gender : " << this->m_gender << endl;
        cout << "    ID   : " << left << setw(50) << this->m_id << "Class  : " << this->m_class << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "         " << left << setw(24) << " " << "| " << setw(15) << "\033[1;34mFirst Term Exam\033[0m " << "| " << setw(15) << " \033[1;34mMidterm Exam\033[0m" << "   | " << setw(15) << "   \033[1;34mFinal Exam\033[0m" << "   |" << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "    No.  " << left << setw(24) << "Subject" << "| " << setw(9) << "Marks" << setw(7) << "Grades" << "| " << setw(9) << "Marks" << setw(7) << "Grades " << "| " << setw(9) << "Marks" << setw(7) << "Grades " << "|" << endl;

        float termTotalMarks[3] = {0.0f};
        float termTotalPossibleMarks[3] = {0.0f};

        for (size_t i = 0; i < subjectsForClass.size(); ++i)
        {
            cout << "    " << i + 1 << ".   " << left << setw(24) << subjectsForClass[i].second;

            for (int term = 0; term < 3; ++term)
            {
                int gradeIndex = term * subjectsForClass.size() + i;
                float grade = grades[gradeIndex];

                if (grade != -1)
                {
                    termTotalMarks[term] += grade;
                    termTotalPossibleMarks[term] += 100.0f;
                }

                string displayMark = (grade == -1) ? "-" : to_string(static_cast<int>(grade));
                cout << "|  " << setw(10) << displayMark << setw(5) << getGradeLetter_New(grade);
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
        if (attendance < 80.0f)
        {
            cout << "\033[1;31m" << attendance << "%\033[0m" << endl;
        }
        else
        {
            cout << "\033[1;32m" << attendance << "%\033[0m" << endl;
        }

        cout << "    Teacher's Comments : ";
        if (!comments.empty())
        {
            for (const auto &comment : comments)
            {
                cout << "- " << comment << endl;
            }
        }
        else
        {
            cout << "No comments available." << endl;
        }

        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "    Awards : ";
        if (!awards.empty())
        {
            for (const auto &award : awards)
            {
                cout << "- " << award << endl;
            }
        }
        else
        {
            cout << "No awards available." << endl;
        }
        cout << "-----------------------------------------------------------------------------------------" << endl;
        system("pause");
        system("cls");
    }
    // Loads subjects for a specific class from the file "subjects.txt".
    void loadSubjectsForClass_New(const string &className, vector<pair<string, string>> &subjectsForClass)
    {
        ifstream subjectsFile("subjects.txt");
        string line;
        while (getline(subjectsFile, line))
        {
            stringstream ss(line);
            string subjectCode, subjectName, classList;
            getline(ss, subjectCode, '|');
            getline(ss, subjectName, '|');
            while (getline(ss, classList, '|'))
            {
                if (classList == className)
                {
                    subjectsForClass.push_back({subjectCode, subjectName});
                    break;
                }
            }
        }
    }
    // Loads grades and attendance for a specific student from the file "gradeAttendance.txt".
    bool loadGradesForStudent_New(const string &studentId, vector<float> &grades, float &attendance)
    {
        ifstream gradesFile("gradeAttendance.txt");
        if (!gradesFile.is_open())
        {
            cerr << "Failed to open the file." << endl;
            return false;
        }

        string line;
        while (getline(gradesFile, line))
        {
            stringstream ss(line);
            string id;
            getline(ss, id, '|');

            // Check if the current line is for the desired student
            if (id == studentId)
            {
                string token;
                vector<string> tokens;

                // Read all tokens in the line
                while (getline(ss, token, '|'))
                {
                    tokens.push_back(token);
                }

                // The last token is assumed to be attendance
                if (!tokens.empty())
                {
                    attendance = stof(tokens.back());
                    tokens.pop_back(); // Remove the last token
                }

                // Convert the remaining tokens to grades
                for (const string &gradeStr : tokens)
                {
                    grades.push_back(stof(gradeStr));
                }

                gradesFile.close();
                return true;
            }
        }

        gradesFile.close();
        return false; // Return false if the student ID was not found
    }

    // Converts a numerical grade to a letter grade (overloaded version).
    string getGradeLetter_New(float grade)
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

    // Constructor to initialize an Admin object with given parameters and load subjects from a file.
    Admin(string name, string password)
    {
        this->m_name = name;
        this->m_password = password;
        this->init_vector();
        loadSubjects("subjects.txt");
    }

    // Displays the admin menu and handles user input.
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
                clearInputStream();
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
    // Displays details of a teacher.
    void display_teacher_details(const Teacher &teacher)
    {
        cout << "============================================================================" << endl;
        cout << "                           EDIT TEACHER PROFILE                             " << endl;
        cout << "============================================================================" << endl;
        cout << "    Name     : " << left << setw(30) << teacher.m_name << "Gender : " << setw(15) << teacher.m_gender << endl;
        cout << "    Password : " << left << setw(30) << teacher.m_password << "Class  : " << setw(15) << teacher.m_class << endl;
    }

    // Displays details of a student.
    void display_student_details(const Student &student)
    {
        cout << "============================================================================" << endl;
        cout << "                           EDIT STUDENT PROFILE                             " << endl;
        cout << "============================================================================" << endl;
        cout << "    Name     : " << left << setw(30) << student.m_name << "Gender : " << setw(15) << student.m_gender << endl;
        cout << "    Password : " << left << setw(30) << student.m_password << "Class  : " << setw(15) << student.m_class << endl;
    }

    // Allows the admin to edit a user profile.
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
            clearInputStream();
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
                itTea = findTeacherById(vTea, user_id);
                userFound = itTea != vTea.end();
            }
            else
            {
                cout << "    Please Enter Student ID: ";
                cin >> user_id;
                itStu = findStudentById(vStu, user_id);
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
                clearInputStream();
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
    // Activates a new user account.
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
                clearInputStream();
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
                            for (size_t i = 0; i < subjectCodes.size() * 3; ++i)
                            {
                                gradeFile << "|-1";
                            }
                            gradeFile << "|0" << endl; // attendance is at the last
                            gradeFile.close();
                        }
                        else
                        {
                            cout << "Unable to open gradeAttendance.txt for writing" << endl;
                        }

                        ofstream commentFile("comment.txt", ios::out | ios::app);
                        if (commentFile.is_open())
                        {
                            commentFile << user_id << "|" << user_class << "|" << endl;
                            commentFile.close();
                        }
                        else
                        {
                            cout << "Unable to open comment.txt for writing" << endl;
                        }

                        ofstream awardsFile("awards.txt", ios::out | ios::app);
                        if (awardsFile.is_open())
                        {
                            awardsFile << user_id << "|" << endl;
                            awardsFile.close();
                        }
                        else
                        {
                            cout << "Unable to open awards.txt for writing" << endl;
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

    // Deactivates an existing user account.
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
                clearInputStream();
                goto RECHOICE;
            }

            if (choice == 1)
            {
                cout << "    Please Enter Teacher ID: ";
                cin >> user_id;
                auto it = findTeacherById(vTea, user_id);
                if (it != vTea.end())
                {
                    vTea.erase(it);
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
                auto it = findStudentById(vStu, user_id);
                if (it != vStu.end())
                {
                    vStu.erase(it);
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

    // Removes a student's data from a file.
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

    // Prints details of a teacher.
    void print_teacher(Teacher &t)
    {
        cout << "    " << left << setw(15) << t.m_id << setw(30) << t.m_name << setw(20) << t.m_password << endl;
    }

    // Prints details of a student.
    void print_student(Student &s)
    {
        cout << "    " << left << setw(15) << s.m_id << setw(30) << s.m_name << setw(20) << s.m_password << endl;
    }

    // Displays the list of teachers or students.
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
                clearInputStream();
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

    void display_class_info(const string &className, const string &teacherName, int studentCount, int grade)
    {
        system("cls");
        cout << "============================================================================" << endl;
        cout << "                             CLASS INFORMATION                              " << endl;
        cout << "============================================================================" << endl;
        cout << "    " << left << setw(10) << "Grade" << setw(10) << "Class" << setw(30) << "Teacher Name" << setw(20) << "Student Quantity" << endl;
        cout << "    " << left << setw(10) << grade << setw(10) << className << setw(30) << teacherName << setw(20) << studentCount << endl;
        cout << "----------------------------------------------------------------------------" << endl;
    }

    // Displays the list of all classes.
    int binary_search(const vector<pair<string, pair<string, int>>> &classes, const string &target)
    {
        int left = 0;
        int right = classes.size() - 1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (classes[mid].first == target)
            {
                return mid;
            }
            else if (classes[mid].first < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return -1;
    }

    void view_all_classes_list()
    {
        vector<pair<string, pair<string, int>>> classes;
        unordered_map<string, pair<string, int>> classMap;

        for (const auto &teacher : vTea)
        {
            if (classMap.find(teacher.m_class) == classMap.end())
            {
                int studentCount = countStudentsInClass(vStu, teacher.m_class);
                classMap[teacher.m_class] = make_pair(teacher.m_name, studentCount);
            }
        }

        for (const auto &entry : classMap)
        {
            classes.push_back(make_pair(entry.first, entry.second));
        }

        sort(classes.begin(), classes.end());

        int choice;
        do
        {
            cout << "============================================================================" << endl;
            cout << "                             VIEW ALL CLASSES LIST                          " << endl;
            cout << "============================================================================" << endl;
            cout << right << setw(70) << "Total Class: " << classes.size() << endl;
            cout << "    " << left << setw(10) << "Grade" << setw(10) << "Class" << setw(30) << "Teacher Name" << setw(20) << "Student Quantity" << endl;

            for (const auto &classInfo : classes)
            {
                int grade = 0;
                if (isdigit(classInfo.first[0]))
                {
                    grade = classInfo.first[0] - '0';
                }
                cout << "    " << left << setw(10) << grade << setw(10) << classInfo.first << setw(30) << classInfo.second.first << setw(20) << classInfo.second.second << endl;
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
                // Already sorted, no action needed
                system("pause");
                system("cls");
                break;
            case 2:
            {
                system("cls");
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

                    int index = binary_search(classes, className);
                    if (index != -1)
                    {
                        const auto &classInfo = classes[index];
                        int grade = 0;
                        if (isdigit(classInfo.first[0]))
                        {
                            grade = classInfo.first[0] - '0';
                        }
                        display_class_info(classInfo.first, classInfo.second.first, classInfo.second.second, grade);
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
                    for (const auto &classInfo : classes)
                    {
                        if (classInfo.second.first == teacherName)
                        {
                            int grade = 0;
                            if (isdigit(classInfo.first[0]))
                            {
                                grade = classInfo.first[0] - '0';
                            }
                            display_class_info(classInfo.first, classInfo.second.first, classInfo.second.second, grade);
                            found = true;
                            break;
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
                break;
            }
            case 3:
                return;
            default:
                cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
            }
        } while (choice != 3);
    }
    // sort using selection sort, and will base on class
    void selection_sort(vector<string> &arr)
    {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++)
        {
            int min_idx = i;
            for (int j = i + 1; j < n; j++)
            {
                if (arr[j] < arr[min_idx])
                {
                    min_idx = j;
                }
            }
            swap(arr[min_idx], arr[i]);
        }
    }

    // Adds a new subject to the system.
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

    // Deletes a subject from the system.
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

    // Reinitializes grades after a subject deletion.
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

    // Reinitializes grades for new classes.
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

    // Displays the list of subjects.
    void view_subjects()
    {
        int choice;
        do
        {
            cout << "============================================================================" << endl;
            cout << "                               VIEW SUBJECTS                                " << endl;
            cout << "============================================================================" << endl;
            cout << left << setw(15) << "Subject Code" << setw(20) << "Subject Name" << "Classes" << endl;
            cout << "----------------------------------------------------------------------------" << endl;
            subjects.printSubjects();
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
            {
                int sortCriteria;
                char sortOrder;
                cout << "    Choose Sorting Criteria: " << endl;
                cout << "    [1] Code" << endl;
                cout << "    [2] Name" << endl;
                cout << "    Enter Choice: ";
                cin >> sortCriteria;
                cout << "    Choose Sorting Order (A for Ascending, D for Descending): ";
                cin >> sortOrder;
                bool ascending = (sortOrder == 'A' || sortOrder == 'a');
                subjects.mergeSort(sortCriteria, ascending);
                system("cls");
                break;
            }
            case 2:
                searchSubjects();
                system("cls");
                break;
            case 3:
                system("cls");
                return;
            default:
                cout << "\033[1;31m    Invalid Choice. Please Try Again.\033[0m" << endl;
            }
        } while (choice != 3);
    }

    void searchSubjects()
    {
        int searchCriteria;
        string target;
        cout << "    Choose Searching Criteria: " << endl;
        cout << "    [1] Code" << endl;
        cout << "    [2] Name" << endl;
        cout << "    Enter Choice: ";
        cin >> searchCriteria;
        cin.ignore();
        cout << "    Enter Search Target: ";
        getline(cin, target);

        bool found = subjects.search(searchCriteria, target);
        if (!found)
        {
            cout << "\033[1;31m    No match found.\033[0m" << endl;
        }

        system("pause");
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

    // Updates the user file with current data.
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

    // Updates the comment file with new class data.
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

    // Updates the grade and attendance file with new class data.
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

    // Checks if an ID or subject code is repeated.
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

    // Loads subjects from a file.
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

    // Saves subjects to a file.
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

    vector<Student> vStu;       // Vector to store students.
    vector<Teacher> vTea;       // Vector to store teachers.
    SubjectLinkedList subjects; // List to store subjects.

    // Finds a teacher by ID.
    vector<Teacher>::iterator findTeacherById(vector<Teacher> &teachers, const string &id)
    {
        for (auto it = teachers.begin(); it != teachers.end(); ++it)
        {
            if (it->m_id == id)
            {
                return it;
            }
        }
        return teachers.end();
    }

    // Finds a student by ID.
    vector<Student>::iterator findStudentById(vector<Student> &students, const string &id)
    {
        for (auto it = students.begin(); it != students.end(); ++it)
        {
            if (it->m_id == id)
            {
                return it;
            }
        }
        return students.end();
    }

    // Counts the number of students in a class.
    int countStudentsInClass(const vector<Student> &students, const string &className)
    {
        int count = 0;
        for (const auto &student : students)
        {
            if (student.m_class == className)
            {
                ++count;
            }
        }
        return count;
    }
};

void login();
void idm();
void change_password();
void view_my_account();

int main()
{
    int choice = 0;

    // Array to store names of weekdays.
    std::string weekdays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    do
    {
        cout << "============================================================================" << endl;
        cout << "                      Secondary Report Card System                          " << endl;
        cout << "============================================================================" << endl;
        time_t now = time(NULL);
        tm *local = localtime(&now);
        int weekday = local->tm_wday;

        // Display current day and date.
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