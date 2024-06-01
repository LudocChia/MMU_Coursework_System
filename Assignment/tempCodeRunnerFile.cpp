    void ternarySearch(StudentInfo *students, const string &key, int left, int right, int *results, int &resultsCount, bool byName = false)
    {
        if (right >= left)
        {
            int mid1 = left + (right - left) / 3;
            int mid2 = right - (right - left) / 3;

            bool found_mid1 = false;
            for (int i = 0; i < resultsCount; ++i)
            {
                if (results[i] == mid1)
                {
                    found_mid1 = true;
                    break;
                }
            }

            if ((!byName && students[mid1].studentId.find(key) != string::npos && !found_mid1) ||
                (byName && students[mid1].studentName.find(key) != string::npos && !found_mid1))
            {
                results[resultsCount++] = mid1;
            }

            bool found_mid2 = false;
            for (int i = 0; i < resultsCount; ++i)
            {
                if (results[i] == mid2)
                {
                    found_mid2 = true;
                    break;
                }
            }

            if ((!byName && students[mid2].studentId.find(key) != string::npos && !found_mid2) ||
                (byName && students[mid2].studentName.find(key) != string::npos && !found_mid2))
            {
                results[resultsCount++] = mid2;
            }

            ternarySearch(students, key, left, mid1 - 1, results, resultsCount, byName);
            ternarySearch(students, key, mid1 + 1, mid2 - 1, results, resultsCount, byName);
            ternarySearch(students, key, mid2 + 1, right, results, resultsCount, byName);
        }
    }

    void searchByStudentID(StudentInfo *students, int studentCount, const string &id)
    {
        int *results = new int[studentCount];
        int resultsCount = 0;
        ternarySearch(students, id, 0, studentCount - 1, results, resultsCount);

        if (resultsCount > 0)
        {
            string subjects[5] = {"Bahasa Melayu", "English", "Mathematics", "History", "Science"};

            cout << "==============================================================================================" << endl;
            cout << "                                SEARCH RESULTS" << endl;
            cout << "==============================================================================================" << endl;
            cout << "| No. | Student ID      | Student Name       | Class    | Subject         | Mark    | Grade  |" << endl;
            cout << "----------------------------------------------------------------------------------------------" << endl;
            int no = 1;
            for (int i = 0; i < resultsCount; ++i)
            {
                const StudentInfo &student = students[results[i]];
                for (int j = 0; j < 5; ++j)
                {
                    if (j == 2)
                    {
                        cout << "| " << setw(3) << left << no++ << " | " << setw(15) << left << student.studentId << " | " << setw(18) << left << student.studentName << " | " << setw(8) << left << student.className << " | " << setw(15) << left << subjects[j] << " | ";
                    }
                    else
                    {
                        cout << "| " << setw(3) << left << "" << " | " << setw(15) << left << "" << " | " << setw(18) << left << "" << " | " << setw(8) << left << "" << " | " << setw(15) << left << subjects[j] << " | ";
                    }

                    if (student.grades[j] < 40.0f)
                    {
                        cout << "\033[1;31m" << setw(4) << right << fixed << setprecision(1) << student.grades[j] << "   ";
                    }
                    else
                    {
                        cout << "\033[1;32m" << setw(4) << right << fixed << setprecision(1) << student.grades[j] << "   ";
                    }
                    cout << "\033[0m" << " | " << setw(6) << left << getGradeLetter(student.grades[j]) << " |" << endl;
                }
                if (i != resultsCount - 1)
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
        delete[] results;
        system("pause");
        system("cls");
    }

    void searchByStudentName(StudentInfo *students, int studentCount, const string &name)
    {
        int *results = new int[studentCount];
        int resultsCount = 0;
        ternarySearch(students, name, 0, studentCount - 1, results, resultsCount, true);

        if (resultsCount > 0)
        {
            string subjects[5] = {"Bahasa Melayu", "English", "Mathematics", "History", "Science"};

            cout << "==============================================================================================" << endl;
            cout << "                                SEARCH RESULTS" << endl;
            cout << "==============================================================================================" << endl;
            cout << "| No. | Student ID      | Student Name       | Class    | Subject         | Mark    | Grade  |" << endl;
            cout << "----------------------------------------------------------------------------------------------" << endl;
            int no = 1;
            for (int i = 0; i < resultsCount; ++i)
            {
                const StudentInfo &student = students[results[i]];
                for (int j = 0; j < 5; ++j)
                {
                    if (j == 2)
                    {
                        cout << "| " << setw(3) << left << no++ << " | " << setw(15) << left << student.studentId << " | " << setw(18) << left << student.studentName << " | " << setw(8) << left << student.className << " | " << setw(15) << left << subjects[j] << " | ";
                    }
                    else
                    {
                        cout << "| " << setw(3) << left << "" << " | " << setw(15) << left << "" << " | " << setw(18) << left << "" << " | " << setw(8) << left << "" << " | " << setw(15) << left << subjects[j] << " | ";
                    }

                    if (student.grades[j] < 40.0f)
                    {
                        cout << "\033[1;31m" << setw(4) << right << fixed << setprecision(1) << student.grades[j] << "   ";
                    }
                    else
                    {
                        cout << "\033[1;32m" << setw(4) << right << fixed << setprecision(1) << student.grades[j] << "   ";
                    }
                    cout << "\033[0m" << " | " << setw(6) << left << getGradeLetter(student.grades[j]) << " |" << endl;
                }
                if (i != resultsCount - 1)
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
        delete[] results;
        system("pause");
        system("cls");
    }

    void ternarySearchByClass(StudentInfo *students, const string &className, int left, int right, int *results, int &resultsCount)
    {
        if (right >= left)
        {
            int mid1 = left + (right - left) / 3;
            int mid2 = right - (right - left) / 3;

            bool found_mid1 = false;
            for (int i = 0; i < resultsCount; ++i)
            {
                if (results[i] == mid1)
                {
                    found_mid1 = true;
                    break;
                }
            }

            if (students[mid1].className.find(className) != string::npos && !found_mid1)
            {
                results[resultsCount++] = mid1;
            }

            bool found_mid2 = false;
            for (int i = 0; i < resultsCount; ++i)
            {
                if (results[i] == mid2)
                {
                    found_mid2 = true;
                    break;
                }
            }

            if (students[mid2].className.find(className) != string::npos && !found_mid2)
            {
                results[resultsCount++] = mid2;
            }

            ternarySearchByClass(students, className, left, mid1 - 1, results, resultsCount);
            ternarySearchByClass(students, className, mid1 + 1, mid2 - 1, results, resultsCount);
            ternarySearchByClass(students, className, mid2 + 1, right, results, resultsCount);
        }
    }

    void searchByClass(StudentInfo *students, int studentCount, const string &className)
    {
        int *results = new int[studentCount];
        int resultsCount = 0;
        ternarySearchByClass(students, className, 0, studentCount - 1, results, resultsCount);

        if (resultsCount > 0)
        {
            string subjects[5] = {"Bahasa Melayu", "English", "Mathematics", "History", "Science"};

            cout << "==============================================================================================" << endl;
            cout << "                                SEARCH RESULTS" << endl;
            cout << "==============================================================================================" << endl;
            cout << "| No. | Student ID      | Student Name       | Class    | Subject         | Mark    | Grade  |" << endl;
            cout << "----------------------------------------------------------------------------------------------" << endl;
            int no = 1;
            for (int i = 0; i < resultsCount; ++i)
            {
                const StudentInfo &student = students[results[i]];
                for (int j = 0; j < 5; ++j)
                {
                    if (j == 2)
                    {
                        cout << "| " << setw(3) << left << no++ << " | " << setw(15) << left << student.studentId << " | " << setw(18) << left << student.studentName << " | " << setw(8) << left << student.className << " | " << setw(15) << left << subjects[j] << " | ";
                    }
                    else
                    {
                        cout << "| " << setw(3) << left << "" << " | " << setw(15) << left << "" << " | " << setw(18) << left << "" << " | " << setw(8) << left << "" << " | " << setw(15) << left << subjects[j] << " | ";
                    }

                    if (student.grades[j] < 40.0f)
                    {
                        cout << "\033[1;31m" << setw(4) << right << fixed << setprecision(1) << student.grades[j] << "   ";
                    }
                    else
                    {
                        cout << "\033[1;32m" << setw(4) << right << fixed << setprecision(1) << student.grades[j] << "   ";
                    }
                    cout << "\033[0m" << " | " << setw(6) << left << getGradeLetter(student.grades[j]) << " |" << endl;
                }
                if (i != resultsCount - 1)
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
        delete[] results;
        system("pause");
        system("cls");
    }

    void ternarySearchBySubject(StudentInfo *students, const string &subject, int subjectIndex, int left, int right, int *results, int &resultsCount)
    {
        if (right >= left)
        {
            int mid1 = left + (right - left) / 3;
            int mid2 = right - (right - left) / 3;

            bool found_mid1 = false;
            for (int i = 0; i < resultsCount; ++i)
            {
                if (results[i] == mid1)
                {
                    found_mid1 = true;
                    break;
                }
            }

            if (students[mid1].grades[subjectIndex] != -1 && !found_mid1)
            {
                results[resultsCount++] = mid1;
            }

            bool found_mid2 = false;
            for (int i = 0; i < resultsCount; ++i)
            {
                if (results[i] == mid2)
                {
                    found_mid2 = true;
                    break;
                }
            }

            if (students[mid2].grades[subjectIndex] != -1 && !found_mid2)
            {
                results[resultsCount++] = mid2;
            }

            ternarySearchBySubject(students, subject, subjectIndex, left, mid1 - 1, results, resultsCount);
            ternarySearchBySubject(students, subject, subjectIndex, mid1 + 1, mid2 - 1, results, resultsCount);
            ternarySearchBySubject(students, subject, subjectIndex, mid2 + 1, right, results, resultsCount);
        }
    }

    void searchBySubject(StudentInfo *students, int studentCount, const string &subject)
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

        int *results = new int[studentCount];
        int resultsCount = 0;
        ternarySearchBySubject(students, subject, subjectIndex, 0, studentCount - 1, results, resultsCount);

        if (resultsCount > 0)
        {
            cout << "Results for subject \"" << subject << "\":" << endl;
            cout << "==============================================================================================" << endl;
            cout << "| No. | Student ID      | Student Name       | Class    | Subject         | Mark    | Grade  |" << endl;
            cout << "----------------------------------------------------------------------------------------------" << endl;
            int no = 1;
            for (int i = 0; i < resultsCount; ++i)
            {
                const StudentInfo &student = students[results[i]];
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
        delete[] results;
        system("pause");
        system("cls");
    }

    void ternarySearchMenu()
    {
        system("cls");

        StudentInfo *students = nullptr;
        int studentCount = 0;
        loadStudents("students.txt", students, studentCount);

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
            searchByStudentID(students, studentCount, searchStr);
            break;
        case 2:
            cout << "Enter Student Name to search: ";
            cin.ignore();
            getline(cin, searchStr);
            searchByStudentName(students, studentCount, searchStr);
            break;
        case 3:
            cout << "Enter Class to search: ";
            cin.ignore();
            getline(cin, searchStr);
            searchByClass(students, studentCount, searchStr);
            break;
        case 4:
            cout << "Enter Subject to search: ";
            cin.ignore();
            getline(cin, searchStr);
            searchBySubject(students, studentCount, searchStr);
            break;
        default:
            cout << "\033[1;31mInvalid choice.\033[0m" << endl;
            break;
        }

        system("pause");
        system("cls");
    }