void loadUsers(const string& filename, vector<Teacher>& teachers, vector<StudentInfo>& studentInfo) {
    ifstream file(filename);
    string line, userType, id, name, password, gender, classId;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, userType, '|');
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, password, '|');
        getline(ss, gender, '|');
        getline(ss, classId, '|');
        if (userType == "1") {  // Teacher
            teachers.emplace_back(userType, id, name, password, gender, classId);
        } else if (userType == "2") { // Student
            StudentInfo student;
            student.studentId = id;
            student.studentName = name;
            student.studentClass = classId;
            studentInfo.push_back(student);
        }
    }
    file.close();

    // Debug: Print loaded student names to ensure they are loaded
    cout << "Loaded student names:\n";
    for (const auto& student : studentInfo) {
        cout << student.studentId << ": " << student.studentName << " (" << student.studentClass << ")\n";
    }
}