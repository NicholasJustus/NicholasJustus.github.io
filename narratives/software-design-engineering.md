# Enhancement One: Software Design and Engineering

**Nicholas Justus | CS 499 Computer Science Capstone**

## Artifact Description

The artifact selected for this milestone is my CS-300 Advising Assistance Program. I originally created the program as part of my Data Structures, Algorithms, and Design coursework. The program is a C++ console application that loads course information from a CSV file, stores the courses in a hash table, displays the course list in alphanumeric order, and allows the user to search for an individual course and view its prerequisites.

## Justification and Improvements

I selected this artifact because it demonstrates several software development skills from my computer science coursework, including C++ programming, file input, data structures, searching, sorting, and modular program design. The original program provided the core functionality, but its input handling could be improved to make the application more reliable and easier for a user to understand.

For this enhancement, I improved input validation and error handling throughout the program. The program now validates menu input before converting it to a number, handles invalid and out-of-range menu selections, checks for empty file names, reports file-opening failures with a clear message, detects files that contain no valid course records, and provides clearer feedback when a requested course does not exist or when an empty course ID is entered. I also updated function parameters to use const references where appropriate and added clearer comments and documentation to improve maintainability.

## Course Outcome Coverage

This enhancement demonstrates progress toward the course outcome requiring the use of well-founded techniques, skills, and tools in computing practices to implement computer solutions that accomplish their intended goals. The changes improve the reliability, maintainability, and usability of the application while preserving its original data-structure functionality.

My original Module One plan identified the Rescue Animal Dashboard as the artifact for the enhancement categories. During implementation, I changed the artifact for this milestone to the CS-300 Advising Assistance Program because the original dashboard depended on a course-hosted MongoDB environment that was no longer available in my local development environment. The CS-300 project provided a working, local artifact that could be tested and enhanced directly.

## Reflection

The enhancement process reinforced the importance of testing software beyond its normal successful path. I tested valid and invalid file names, successful course loading, invalid course searches, empty course IDs, invalid menu selections, and normal course lookups. These tests showed me how small validation changes can make a program much easier to use and troubleshoot.

One challenge was getting the older course project running again in a current local development environment. I also had to verify the correct input file name and rebuild the Visual Studio project before testing the enhanced program. Working through those issues helped me practice debugging and step-by-step validation rather than assuming that existing code would work without modification. Overall, this enhancement helped me move beyond simply making a program function and toward making it more dependable, maintainable, and understandable for another user or developer.

[View the CS-300 project repository](https://github.com/NicholasJustus/Data-Structures-Algorithms-Analysis-and-Design)