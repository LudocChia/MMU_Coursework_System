    void addStudentActivity(ActivityList& activityList) {
    string activity;
    cout << "Enter the activity: ";
    cin.ignore();
    getline(cin, activity);
    activityList.addActivity(activity);
    cout << "Activity added successfully!" << endl;
}


void displayStudentActivities(const ActivityList& activityList) {
    cout << "List of Student Activities:" << endl;
    activityList.displayActivities();
}