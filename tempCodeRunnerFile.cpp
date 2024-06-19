    while (true) {
            int sortChoice;
            cout << "Would you like to sort the students? [1] Yes [2] No: ";
            cin >> sortChoice;
            if (sortChoice != 1) {
                int viewOtherTerm;
                cout << "Would you like to view marks for another term? [1] Yes [2] No: ";
                cin >> viewOtherTerm;
                if (viewOtherTerm == 1) {
                    return;
                } else {
                    break;
                }
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
            if (criterionChoice == 4) {
                clearScreen();
                cout << "Choose the subject to sort by:\n";
                for (size_t i = 0; i < subjectsForClass.size(); ++i) {
                    cout << "[" << (i + 1) << "] " << subjectsForClass[i].second << endl;
                }
                cout << "Enter your choice: ";
                cin >> subjectChoice;
                if (subjectChoice < 1 || subjectChoice > static_cast<int>(subjectsForClass.size())) {
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
            for (const auto& student : students) {
                if (student.studentClass == this->m_class) {
                    bool firstSubject = true;
                    for (size_t i = 0; i < subjectsForClass.size(); ++i) {
                        if (criterionChoice == 4 && i != subjectChoice) continue; // Show only the selected subject

                        if (firstSubject) {
                            cout << setw(5) << studentNo << setw(15) << student.studentId << setw(25) << studentNames[student.studentId] << setw(10) << student.studentClass << setw(15) << subjectsForClass[i].second;
                            firstSubject = false;
                        } else {
                            cout << setw(5) << "" << setw(15) << "" << setw(25) << "" << setw(10) << "" << setw(15) << subjectsForClass[i].second;
                        }

                        int gradeIndex = (termChoice - 1) * subjectsForClass.size() + i;
                        if (student.grades.size() > gradeIndex && student.grades[gradeIndex] == -1) {
                            cout << setw(15) << "-" << setw(10) << "-";
                        } else if (student.grades.size() > gradeIndex) {
                            if (student.grades[gradeIndex] >= 40) {
                                cout << "\033[1;32m";  // Green color for grades >= 40
                            } else {
                                cout << "\033[1;31m";  // Red color for grades < 40
                            }
                            cout << setw(15) << student.grades[gradeIndex] << setw(10) << getGradeLetter(student.grades[gradeIndex]);
                            cout << "\033[0m";  // Reset color
                        } else {
                            cout << setw(15) << "-" << setw(10) << "-";
                        }

                        if (i == 0 || criterionChoice == 4) {
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