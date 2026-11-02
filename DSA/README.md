# Student Record Management System (C Language)

A terminal-based **Student Record Management System** developed in C using fundamental Data Structures and Algorithms (DSA) concepts: **Arrays**, **Linear Search**, and **Bubble Sort**.

---

## 👥 Team Members

| Roll Number | Student Name |
| :--- | :--- |
| `25egjcc006` | Anjalee |
| `25egjcc007` | Ankit Saini |
| `25egjcc008` | Bhanu Pratap |
| `25egjcc009` | Bhuvnesh Vaisnav |

---

## 📌 Project Overview & Module Breakdown

This project is divided into **4 distinct modules** as per the DSA project curriculum:

### 1. Student Registration and Record Storage
- **Add new student**: Accepts `Roll Number`, `Name`, `Branch`, and `Marks` into a contiguous array of structures.
- **Duplicate Validation**: Checks and prevents adding students with existing roll numbers.
- **Update Records**: Modifies details of an existing student by roll number.
- **Delete Records**: Removes a student record and shifts array elements to preserve order.

### 2. Display and Report Module
- **Tabular Display**: Neatly prints all records in a formatted ASCII table.
- **Branch-wise Report**: Filters and displays students for a given branch along with branch-wise student count and average marks.
- **Count Total Students**: Summarizes the current count of enrolled students.

### 3. Searching Module
- **Search by Roll Number**: Uses **Linear Search** to find and display detailed student information.
- **Search by Name**: Case-insensitive search by student name.
- **Error Handling**: Gracefully handles and reports `Record Not Found` scenarios.

### 4. Sorting and Ranking Module
- **Sort by Roll Number**: Ascending order using **Bubble Sort**.
- **Sort by Name**: Alphabetical order (A-Z) using **Bubble Sort**.
- **Sort by Marks**: Descending order (highest to lowest).
- **Merit / Rank List**: Generates a full rank list from highest to lowest marks and highlights the **TOPPER**.

---

## 🛠️ DSA Concepts Implemented
- **Structures (`struct`)**: For encapsulating heterogeneous student data (`rollNo`, `name`, `branch`, `marks`).
- **Array of Structures**: Contiguous sequential memory storage for student records.
- **Linear Search**: $O(n)$ search algorithm for searching by roll number and name.
- **Bubble Sort**: $O(n^2)$ comparison sorting algorithm with swapping for sorting records.
- **Input Stream Handling**: Safe reading mechanisms preventing infinite input loops or buffer overflow.

---

## 🚀 How to Compile and Run

### 1. Prerequisites
- A C compiler like `gcc` (MinGW / MSYS2 / Clang / Linux GCC).

### 2. Compilation
Open your terminal in the project directory and run:
```bash
gcc main.c -o student_management
```

### 3. Execution
- **On Windows**:
  ```cmd
  student_management.exe
  ```
- **On Linux / macOS**:
  ```bash
  ./student_management
  ```

---

## 💻 Sample Program Menu
```text
==================================================
         STUDENT RECORD MANAGEMENT SYSTEM         
==================================================
 [Module 1: Registration & Storage]
   1. Add New Student Record
   2. Update Student Record
   3. Delete Student Record

 [Module 2: Display & Reports]
   4. Display All Students (Tabular)
   5. Branch-wise Report
   6. Count Total Students

 [Module 3: Searching]
   7. Search by Roll Number (Linear Search)
   8. Search by Student Name

 [Module 4: Sorting & Ranking]
   9. Sort Students by Roll Number
  10. Sort Students by Name (A-Z)
  11. Sort Students by Marks
  12. Generate Rank List & View Topper

   0. Exit System
==================================================
```
