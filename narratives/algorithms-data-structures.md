# Enhancement Two: Algorithms and Data Structures

**Nicholas Justus | CS 499 Computer Science Capstone**

## Artifact Description

The artifact is the CS-300 Advising Assistance Program created for the Data Structures and Algorithms: Analysis and Design course. The program is a C++ course-management application that loads course information from a CSV file, stores the records in a hash table, sorts the courses for display, and allows the user to search for a specific course and view its prerequisites.

## Enhancement and Skills Demonstrated

I included this artifact in my ePortfolio because it demonstrates my ability to select and work with data structures and algorithms rather than only focusing on basic program functionality. The original program used a hash table for course storage and lookup and sorting for the course list. For this enhancement, I added a sorted vector and a binary search algorithm so the program can compare two different approaches to course lookup. I also added a search comparison feature and a performance test that performs 100,000 search operations. The program reports the time-complexity characteristics of the approaches: average O(1) for hash-table lookup, O(log n) for binary search, and O(n log n) for sorting.

Testing showed that both search methods successfully found CSCI200. The performance test used eight loaded courses and 100,000 search operations. In that run, the hash-table search took 10,723 microseconds and the binary search took 26,299 microseconds. This result helped demonstrate that theoretical complexity and measured runtime are related but are not the same thing. The hash table was faster in this particular test, while binary search provided an additional search strategy that requires sorted data.

## Course Outcomes

The enhancement addresses the course outcome involving designing and evaluating a computing solution using algorithmic principles while considering trade-offs between different search approaches. It also supports the outcome involving C++ data structures, algorithms, testing, and performance measurement to improve an existing computing solution.

## Reflection

The main thing I learned from this enhancement was that choosing an algorithm involves more than simply selecting the algorithm with the smallest Big-O notation. The existing hash table already provided average constant-time lookup, so adding binary search gave me an opportunity to compare the strengths and requirements of two different approaches. I learned that binary search depends on sorted data and that the cost of sorting needs to be considered when evaluating the overall solution. I also gained more experience using performance testing to compare actual program behavior instead of relying only on theoretical analysis.

The main challenge was adding the new search method without breaking the existing program. I kept the original hash-table search in place and added the binary-search functionality separately, which allowed me to test both approaches. The final program built successfully with zero errors, loaded all eight courses, successfully found CSCI200 using both search methods, and completed the 100,000-operation performance test.

[View the CS-300 project repository](https://github.com/NicholasJustus/Data-Structures-Algorithms-Analysis-and-Design)