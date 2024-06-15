struct StudentInfo
{
    string studentId;
    string studentName;
    string className;
    float grades[5]; // 5 grades for 5 subjects

    StudentInfo()
    {
        for (int i = 0; i < 5; ++i)
        {
            grades[i] = 0.0;
        }
    }
}