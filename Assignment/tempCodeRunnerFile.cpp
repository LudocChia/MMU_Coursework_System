    void stringSearch()
    {
        vector<StudentInfo> students;
        loadStudents("students.txt", students);

        int searchChoice;
        system("cls");
        cout << "================================================================================" << endl;
        cout << "                                 Search Category                                " << endl;
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
                        match = true;
                        break;
                    }
                }
            }

            if (match)
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