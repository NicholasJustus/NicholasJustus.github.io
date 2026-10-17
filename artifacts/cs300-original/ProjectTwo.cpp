// ProjectTwo.cpp
// Nicholas Justus - CS300 Project Two: Advising Assistance Program
// Baseline version reconstructed from the available original source excerpt.
// The original uploaded copy ended during loadCourses(), so this completed
// baseline preserves the documented original features for comparison.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Course {
    string courseId;
    string name;
    vector<string> prerequisites;
};

class HashTable {
private:
    static const unsigned int DEFAULT_SIZE = 179;
    vector<vector<Course>> buckets;
    unsigned int hashFunc(string key) {
        unsigned int sum = 0;
        for (char c : key) sum += c;
        return sum % DEFAULT_SIZE;
    }
public:
    HashTable() { buckets.resize(DEFAULT_SIZE); }
    void Insert(Course course) {
        unsigned int idx = hashFunc(course.courseId);
        buckets[idx].push_back(course);
    }
    Course* Search(string courseId) {
        unsigned int idx = hashFunc(courseId);
        for (auto& course : buckets[idx])
            if (course.courseId == courseId) return &course;
        return nullptr;
    }
    vector<Course> GetAll() {
        vector<Course> allCourses;
        for (auto& bucket : buckets)
            for (auto& course : bucket) allCourses.push_back(course);
        return allCourses;
    }
};

void loadCourses(const string& filename, HashTable& table) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Course course;
        string prerequisite;
        getline(ss, course.courseId, ',');
        getline(ss, course.name, ',');
        while (getline(ss, prerequisite, ','))
            if (!prerequisite.empty()) course.prerequisites.push_back(prerequisite);
        if (!course.courseId.empty() && !course.name.empty()) table.Insert(course);
    }
}

void printCourseList(HashTable& table) {
    vector<Course> courses = table.GetAll();
    sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {
        return a.courseId < b.courseId;
    });
    for (const auto& course : courses)
        cout << course.courseId << ", " << course.name << endl;
}

void printCourse(HashTable& table, string courseId) {
    Course* course = table.Search(courseId);
    if (course == nullptr) {
        cout << "Course not found." << endl;
        return;
    }
    cout << course->courseId << ", " << course->name << endl;
    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    } else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course->prerequisites.size(); ++i) {
            cout << course->prerequisites[i];
            if (i + 1 < course->prerequisites.size()) cout << ", ";
        }
        cout << endl;
    }
}

int main() {
    HashTable courseTable;
    int choice = 0;
    while (choice != 9) {
        cout << "\n1. Load Data Structure\n2. Print Course List\n3. Print Course\n9. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 1) {
            string filename;
            cout << "Enter file name: ";
            cin >> ws;
            getline(cin, filename);
            loadCourses(filename, courseTable);
        } else if (choice == 2) {
            printCourseList(courseTable);
        } else if (choice == 3) {
            string courseId;
            cout << "Enter course ID (e.g. CSCI200): ";
            cin >> courseId;
            printCourse(courseTable, courseId);
        } else if (choice == 9) {
            cout << "Goodbye." << endl;
        } else {
            cout << "Invalid choice." << endl;
        }
    }
    return 0;
}