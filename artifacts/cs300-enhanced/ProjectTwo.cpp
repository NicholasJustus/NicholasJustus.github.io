// ProjectTwo.cpp
// Nicholas Justus \x96 CS300 Project Two: Advising Assistance Program
// Date: October 4, 2026
// CS-499 Enhancement: Database/Data Validation

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>

using namespace std;

// Structure for holding course information
struct Course {
    string courseId;
    string name;
    vector<string> prerequisites;
};

// Simple hash table using vector<Course> buckets
class HashTable {
private:
    static const unsigned int DEFAULT_SIZE = 179;
    vector<vector<Course>> buckets;

    unsigned int hashFunc(const string& key) {
        unsigned int sum = 0;

        for (char c : key) {
            sum += c;
        }

        return sum % DEFAULT_SIZE;
    }

public:
    HashTable() {
        buckets.resize(DEFAULT_SIZE);
    }

    void Insert(const Course& course) {
        unsigned int idx = hashFunc(course.courseId);
        buckets[idx].push_back(course);
    }

    Course* Search(const string& courseId) {
        unsigned int idx = hashFunc(courseId);

        for (auto& course : buckets[idx]) {
            if (course.courseId == courseId) {
                return &course;
            }
        }

        return nullptr;
    }

    vector<Course> GetAll() {
        vector<Course> allCourses;

        for (auto& bucket : buckets) {
            for (auto& course : bucket) {
                allCourses.push_back(course);
            }
        }

        return allCourses;
    }
};

// Loads courses from the input file into the hash table.
// Returns true only when the file was successfully opened and processed.
bool loadCourses(const string& filename, HashTable& table) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open the file '" << filename << "'." << endl;
        cout << "Please check the file name and try again." << endl;
        return false;
    }

    string line;
    int coursesLoaded = 0;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        Course course;
        string prerequisite;

        // Read course ID
        getline(ss, course.courseId, ',');

        // Read course name
        getline(ss, course.name, ',');

        // Read prerequisites
        while (getline(ss, prerequisite, ',')) {
            if (!prerequisite.empty()) {
                course.prerequisites.push_back(prerequisite);
            }
        }

        // Validate that the required course information exists.
        if (course.courseId.empty() || course.name.empty()) {
            cout << "Warning: Skipping an invalid course record." << endl;
            continue;
        }

        table.Insert(course);
        coursesLoaded++;
    }

    file.close();

    if (coursesLoaded == 0) {
        cout << "Error: No valid course records were found in the file." << endl;
        return false;
    }

    cout << "Courses loaded successfully. "
        << coursesLoaded << " courses loaded." << endl;

    return true;
}

// Creates a sorted vector of courses for binary searching.
vector<Course> buildSortedCourses(HashTable& table) {
    vector<Course> courses = table.GetAll();

    sort(courses.begin(), courses.end(),
        [](const Course& a, const Course& b) {
            return a.courseId < b.courseId;
        });

    return courses;
}

// Performs binary search on a sorted vector of courses.
// Returns a pointer to the matching course or nullptr if not found.
Course* binarySearch(vector<Course>& courses, const string& courseId) {
    int left = 0;
    int right = static_cast<int>(courses.size()) - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (courses[middle].courseId == courseId) {
            return &courses[middle];
        }

        if (courses[middle].courseId < courseId) {
            left = middle + 1;
        }
        else {
            right = middle - 1;
        }
    }

    return nullptr;
}

// Prints all courses in alphanumeric order.
void printCourseList(HashTable& table) {
    vector<Course> courses = buildSortedCourses(table);

    for (const auto& course : courses) {
        cout << course.courseId << ", " << course.name << endl;
    }
}

// Prints information for a specific course using hash table search.
void printCourse(HashTable& table, const string& courseId) {
    if (courseId.empty()) {
        cout << "Error: Course ID cannot be empty." << endl;
        return;
    }

    Course* course = table.Search(courseId);

    if (course == nullptr) {
        cout << "Error: Course '" << courseId << "' was not found." << endl;
        return;
    }

    cout << course->courseId << ", " << course->name << endl;

    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";

        for (size_t i = 0; i < course->prerequisites.size(); ++i) {
            cout << course->prerequisites[i];

            if (i < course->prerequisites.size() - 1) {
                cout << ", ";
            }
        }

        cout << endl;
    }
}

// Compares the existing hash-table search with the new binary search.
void compareSearchMethods(HashTable& table) {
    vector<Course> sortedCourses = buildSortedCourses(table);

    if (sortedCourses.empty()) {
        cout << "Error: No courses are available for comparison." << endl;
        return;
    }

    string courseId;

    cout << "Enter course ID to compare (e.g. CSCI200): ";
    getline(cin, courseId);

    if (courseId.empty()) {
        cout << "Error: Course ID cannot be empty." << endl;
        return;
    }

    Course* hashResult = table.Search(courseId);
    Course* binaryResult = binarySearch(sortedCourses, courseId);

    cout << endl;
    cout << "Search comparison for: " << courseId << endl;
    cout << "----------------------------------------" << endl;

    if (hashResult != nullptr) {
        cout << "Hash table search: Found" << endl;
    }
    else {
        cout << "Hash table search: Not found" << endl;
    }

    if (binaryResult != nullptr) {
        cout << "Binary search: Found" << endl;
    }
    else {
        cout << "Binary search: Not found" << endl;
    }

    cout << endl;
    cout << "Algorithm analysis:" << endl;
    cout << "- Hash table search: Average O(1)" << endl;
    cout << "- Binary search: O(log n)" << endl;
    cout << "- Sorting the courses: O(n log n)" << endl;
    cout << endl;
    cout << "The binary search requires sorted data, while the hash table "
        << "provides direct average-case lookup." << endl;
}

// Runs repeated searches to provide a simple performance comparison.
void performanceTest(HashTable& table) {
    vector<Course> sortedCourses = buildSortedCourses(table);

    if (sortedCourses.empty()) {
        cout << "Error: No courses are available for testing." << endl;
        return;
    }

    const string testCourse = sortedCourses[sortedCourses.size() / 2].courseId;
    const int searchCount = 100000;

    auto hashStart = chrono::high_resolution_clock::now();

    for (int i = 0; i < searchCount; ++i) {
        table.Search(testCourse);
    }

    auto hashEnd = chrono::high_resolution_clock::now();

    auto binaryStart = chrono::high_resolution_clock::now();

    for (int i = 0; i < searchCount; ++i) {
        binarySearch(sortedCourses, testCourse);
    }

    auto binaryEnd = chrono::high_resolution_clock::now();

    auto hashTime =
        chrono::duration_cast<chrono::microseconds>(hashEnd - hashStart).count();

    auto binaryTime =
        chrono::duration_cast<chrono::microseconds>(binaryEnd - binaryStart).count();

    cout << endl;
    cout << "Performance Test" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Courses loaded: " << sortedCourses.size() << endl;
    cout << "Search operations: " << searchCount << endl;
    cout << "Test course: " << testCourse << endl;
    cout << endl;
    cout << "Hash table search time: " << hashTime << " microseconds" << endl;
    cout << "Binary search time: " << binaryTime << " microseconds" << endl;
    cout << endl;
    cout << "Time complexity:" << endl;
    cout << "- Hash table search: Average O(1)" << endl;
    cout << "- Binary search: O(log n)" << endl;
    cout << "- Sorting: O(n log n)" << endl;
}

// Validates course data for duplicate course IDs and missing prerequisites.
void validateCourseData(HashTable& table) {
    vector<Course> courses = table.GetAll();

    if (courses.empty()) {
        cout << "Error: No courses are available for validation." << endl;
        return;
    }

    int duplicateIds = 0;
    int invalidPrerequisites = 0;

    // Check for duplicate course IDs.
    for (size_t i = 0; i < courses.size(); ++i) {
        for (size_t j = i + 1; j < courses.size(); ++j) {
            if (courses[i].courseId == courses[j].courseId) {
                duplicateIds++;
            }
        }
    }

    // Check that every prerequisite exists as a course.
    for (const auto& course : courses) {
        for (const auto& prerequisite : course.prerequisites) {
            bool prerequisiteFound = false;

            for (const auto& possibleCourse : courses) {
                if (possibleCourse.courseId == prerequisite) {
                    prerequisiteFound = true;
                    break;
                }
            }

            if (!prerequisiteFound) {
                cout << "Warning: " << course.courseId
                    << " has an invalid prerequisite: "
                    << prerequisite << endl;

                invalidPrerequisites++;
            }
        }
    }

    cout << endl;
    cout << "Course Data Validation" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Courses checked: " << courses.size() << endl;
    cout << "Duplicate course IDs: " << duplicateIds << endl;
    cout << "Invalid prerequisites: " << invalidPrerequisites << endl;
    cout << endl;

    if (duplicateIds == 0 && invalidPrerequisites == 0) {
        cout << "Course data passed validation." << endl;
    }
    else {
        cout << "Course data contains validation issues." << endl;
    }
}

int main() {
    HashTable courseTable;
    int choice = 0;
    bool dataLoaded = false;

    while (choice != 9) {
        cout << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "4. Compare Search Methods" << endl;
        cout << "5. Run Performance Test" << endl;
        cout << "6. Validate Course Data" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter choice: ";

        string choiceInput;
        getline(cin, choiceInput);

        try {
            choice = stoi(choiceInput);
        }
        catch (const invalid_argument&) {
            cout << "Error: Please enter a valid menu number." << endl;
            continue;
        }
        catch (const out_of_range&) {
            cout << "Error: Menu selection is out of range." << endl;
            continue;
        }

        if (choice == 1) {
            string filename;

            cout << "Enter file name: ";
            getline(cin, filename);

            if (filename.empty()) {
                cout << "Error: File name cannot be empty." << endl;
                continue;
            }

            dataLoaded = loadCourses(filename, courseTable);
        }
        else if (choice == 2) {
            if (!dataLoaded) {
                cout << "Error: Please load the data structure first." << endl;
            }
            else {
                printCourseList(courseTable);
            }
        }
        else if (choice == 3) {
            if (!dataLoaded) {
                cout << "Error: Please load the data structure first." << endl;
            }
            else {
                string courseId;

                cout << "Enter course ID (e.g. CSCI200): ";
                getline(cin, courseId);

                printCourse(courseTable, courseId);
            }
        }
        else if (choice == 4) {
            if (!dataLoaded) {
                cout << "Error: Please load the data structure first." << endl;
            }
            else {
                compareSearchMethods(courseTable);
            }
        }
        else if (choice == 5) {
            if (!dataLoaded) {
                cout << "Error: Please load the data structure first." << endl;
            }
            else {
                performanceTest(courseTable);
            }
        }
        else if (choice == 6) {
            if (!dataLoaded) {
                cout << "Error: Please load the data structure first." << endl;
            }
            else {
                validateCourseData(courseTable);
            }
        }
        else if (choice == 9) {
            cout << "Goodbye." << endl;
        }
        else {
            cout << "Error: Invalid menu choice. Please select 1, 2, 3, 4, 5, 6, or 9."
                << endl;
        }
    }

    return 0;
}