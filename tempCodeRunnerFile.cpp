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
    string hashSearch(const unordered_map<float, string> &gradesMap, float target) 
    {
        auto it = gradesMap.find(target);
        if (it != gradesMap.end())
            return it->second;
        return "";
    }

    void student_attendance_and_grades() 
    {
        vector<StudentInfo> students;
        SubjectLinkedList subjects;
        loadStudentGradeAttendance("gradeAttendance.txt", students, subjects);

        vector<Teacher> teachers;
        loadUsers("user.txt", teachers);

        cout << "=======================================================================================================" << endl;
        cout << "                                       View Grades and Attendance" << endl;
        cout << "=======================================================================================================" << endl;
        cout << "List of students in your class (" << this->m_class << "):" << endl;
        vector<string> studentIdsInClass;
        for (const auto& teacher : teachers) 
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
        {
            return s.studentId == studentId;
        });

        if (it == students.end() || it->studentClass != this->m_class) 
        {
            do 
            {
                cout << "\033[1;31m    Student not found or not in your class. Please make sure you enter the correct student ID. \033[0m" << endl;
                cout << "=======================================================================================================" << endl;
                cout << "    Enter the correct student ID : ";
                cin >> studentId;
                it = find_if(students.begin(), students.end(), [&](const StudentInfo &s) 
                {
                    return s.studentId == studentId;
                });
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
        cout << "Enter 1 for Merge Sort, 2 for Hash Search, or 4 to go back to menu: ";
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
            unordered_map<float, string> gradesMap;
            for (const auto& grade : allTermGrades)
            {
                gradesMap[grade.first] = grade.second;
            }

            float target;
            cout << "Enter the grade to search for: ";
            cin >> target;
            string result = hashSearch(gradesMap, target);
            if (!result.empty()) 
            {
                cout << "Grade found: " << target << " in subject " << result << endl;
            } 
            else 
            {
                cout << "Grade not found" << endl;
            }
        }
        else 
        {
            return;
        }
        system("pause");
        system("cls");
    }