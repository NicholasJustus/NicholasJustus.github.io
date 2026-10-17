# Enhancement Three: Databases and Data Integrity

**Nicholas Justus | CS 499 Computer Science Capstone**

## Artifact Description

The artifact I used for this milestone is my CS-300 Advising Assistance Program, which I originally created for my Data Structures and Algorithms: Analysis and Design course. It is a C++ program that loads course information from a CSV file, stores the courses in a hash table, and allows the user to sort and search the course information. I chose to continue using this artifact for CS 499 so that I could build on the same project instead of splitting my work across multiple artifacts.

## Enhancement and Skills Demonstrated

I included this project in my ePortfolio because it shows several of the programming skills I have developed through the Computer Science program. The program already used structured course data, a hash table, sorting, and searching. For this enhancement, I added a course data validation feature that checks for duplicate course IDs and prerequisites that do not exist in the loaded course data. I also kept the search comparison and performance testing enhancements from the previous milestone. Together, these changes make the program better at checking the quality and integrity of the data it is working with.

## Course Outcomes

I believe I have made progress toward the course outcomes I planned to address with this artifact. The project demonstrates the use of computing practices and tools to improve an existing solution, while the search comparison and performance testing also support the outcome involving algorithmic principles and trade-offs. The new validation feature gives me additional experience working with structured data and making sure that the information used by a program is consistent.

## Reflection

The main thing I learned from this enhancement was that data validation is an important part of building a reliable program. It is easy to focus on making a program work, but the data going into the program also needs to be checked. I added validation for duplicate course IDs and missing prerequisites without changing the overall design of the project. Testing the program with the existing eight-course data set showed that there were no duplicate course IDs or invalid prerequisites, and the program reported that the course data passed validation.

One challenge was deciding how to add a database-focused improvement without making the project much larger or changing the original program unnecessarily. I wanted to keep the enhancement manageable and still show a meaningful improvement. I also had to make sure the new validation feature did not interfere with the search and performance features I had already added. After making the changes, I built and tested the program successfully.

[View the CS-300 project repository](https://github.com/NicholasJustus/Data-Structures-Algorithms-Analysis-and-Design)