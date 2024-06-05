void printStudents(const StudentInfo s[], int n, int choice = -1, int s_index = -1) {
        printHeader();
        string subjects[] = {"Bahasa Melayu", "English", "Mathematics", "History", "Science"};

        for (int i = 0; i < n; ++i) {
            cout << "| " << left << setw(3) << (i + 1) << " | "
                << left << setw(15) << s[i].studentId << " | "
                << left << setw(17) << s[i].studentName << " | "
                << left << setw(8) << s[i].className << " |";

            if (choice == 4 && s_index >= 0) {
                if (s[i].grades[s_index] < 40) {
                    cout << " " << left << setw(16) << subjects[s_index] << " | "
                        << "\033[1;31m" << left << setw(10) << s[i].grades[s_index] << "\033[0m | "
                        << left << setw(7) << getGrade(s[i].grades[s_index]) << " |\n";
                } else {
                    cout << " " << left << setw(16) << subjects[s_index] << " | "
                        << "\033[1;32m" << left << setw(10) << s[i].grades[s_index] << "\033[0m | "
                        << left << setw(7) << getGrade(s[i].grades[s_index]) << " |\n";
                }
            } else {
                for (int j = 0; j < 5; ++j) {
                    if (s[i].grades[j] < 40) {
                        if (j > 0) {
                            cout << "|     |                 |                   |          | ";
                        }
                        cout << left << setw(16) << subjects[j] << " | "
                            << "\033[1;31m" << left << setw(8) << s[i].grades[j] << "\033[0m | "
                            << left << setw(7) << getGrade(s[i].grades[j]) << " |\n";
                    } else {
                        if (j > 0) {
                            cout << "|     |                 |                   |          | ";
                        }
                        cout << left << setw(16) << subjects[j] << " | "
                            << "\033[1;32m" << left << setw(8) << s[i].grades[j] << "\033[0m | "
                            << left << setw(7) << getGrade(s[i].grades[j]) << " |\n";
                    }
                }
            }

            cout << "----------------------------------------------------------------------------------------------\n";
        }

        cout << "==============================================================================================\n";
    }