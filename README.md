# 🎓 Student Management System in C

## 📌 Project Overview
A lightweight, menu-driven **Command-Line Interface (CLI)** application developed in **C** for efficient student record-keeping. The system uses binary file handling (`students.dat`) to store data persistently across sessions, allowing users to add, view, search, update, and delete student details quickly.

## ✨ Key Features
- **Add Student Records:** Store Roll Number, Full Name, Department, and CGPA.
- **Tabular Record Display:** View all saved students in a clean, formatted CLI table.
- **Fast Search:** Instantly look up student details by Roll Number.
- **In-Place Record Updates:** Modify existing student details using file pointers (`fseek`).
- **Safe Record Deletion:** Remove outdated entries cleanly using temporary file swapping.
- **Persistent Storage:** Automatically saves all records to a local binary file (`students.dat`).

## 🛠️ Technical Concepts Used
- **Language:** C (Standard C99/C11)
- **Data Structures:** `struct` and `typedef` for modeling student entities
- **File I/O Operations:** `fopen`, `fread`, `fwrite`, `fseek`, `remove`, and `rename`
- **Input Validation:** Buffer clearing and safe multi-word string reading (`scanf` scansets)

## 🖥️ Sample CLI Output
```text
============================================
       STUDENT MANAGEMENT SYSTEM (CLI)      
============================================
  1. Add New Student Record
  2. Display All Student Records
  3. Search Student by Roll Number
  4. Update Student Record
  5. Delete Student Record
  6. Exit
--------------------------------------------
Enter your choice (1-6): 2

------------------------------------------------------------------
Roll No    Name                      Department         CGPA    
------------------------------------------------------------------
101        Aarav Sharma              Computer Science   8.95    
102        Priya Patel               Electronics        9.10    
103        Rohan Verma               Information Tech   8.40    
------------------------------------------------------------------
Total Records: 3
