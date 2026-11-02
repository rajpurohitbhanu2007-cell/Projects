# Library Management System (OOPs in C++)

A terminal-based **Library Management System** developed in **C++** with a core focus on **Object-Oriented Programming (OOPs)** principles.

---

## 👥 Team Members

| Roll Number | Student Name |
| :--- | :--- |
| `25egjcc006` | Anjalee |
| `25egjcc007` | Ankit Saini |
| `25egjcc008` | Bhanu Pratap |
| `25egjcc009` | Bhuvnesh Vaisnav |

---

## 🏛️ OOP Concepts Demonstrated

| Concept | Implementation in Code |
| :--- | :--- |
| **Abstraction** | `LibraryItem` abstract base class defining pure virtual interfaces (`display()`, `calculateFine()`). |
| **Inheritance** | `Book` inherits publicly from `LibraryItem` (`class Book : public LibraryItem`). |
| **Polymorphism** | Runtime method overriding of `display()` and `calculateFine(int actualDays)` in `Book`. |
| **Encapsulation** | Private & protected member variables (`id`, `title`, `author`, `isIssued`) accessible only via dedicated getters, setters, and member methods. |
| **Classes & Objects**| Clean separation of domain entity (`Book`) and controller/system (`LibraryManagementSystem`). |

---

## 📌 4-Module Breakdown

### Module 1: Add, Update, and Delete Books
- **Add Book**: Validates against duplicate Book IDs and registers new titles.
- **Update Details**: Safely updates book title and author.
- **Delete Book**: Validates that an issued book cannot be removed until returned.

### Module 2: Display and Search Books
- **Display Catalog**: Formatted tabular view of all books with availability status.
- **Search by ID**: Exact ID lookup displaying full record.
- **Search by Title**: Case-insensitive keyword search matching title substrings.

### Module 3: Issue and Return Books
- **Issue Book**: Issues available book to a student/borrower with a standard 14-day borrowing duration.
- **Return Book**: Returns borrowed book and calculates overdue days.

### Module 4: Calculate Late Fines and Generate Reports
- **Late Fine Calculation**: Automatically charges ₹5.00/day for overdue returns beyond the 14-day period.
- **Fine Calculator Tool**: Interactive utility to check fines for any duration.
- **Statistical Reports**:
  - Summary of total, issued, and available books.
  - Total late fines collected.
  - Filtered lists for currently issued and available books.

---

## 🚀 How to Compile and Run

### 1. Prerequisites
- `g++` compiler (MinGW, MSYS2, Clang, or Linux GCC).

### 2. Compilation
Open your terminal in the `OOPs` directory and run:
```bash
g++ main.cpp -o library_management
```

### 3. Execution
- **On Windows**:
  ```cmd
  library_management.exe
  ```
- **On Linux / macOS**:
  ```bash
  ./library_management
  ```

---

## 💻 Sample Program Menu
```text
============================================================
           LIBRARY MANAGEMENT SYSTEM (OOPs in C++)          
============================================================
 [Module 1: Book Management]
   1. Add New Book
   2. Update Book Details
   3. Delete Book

 [Module 2: Catalog & Search]
   4. Display All Books
   5. Search Books (by ID or Title)

 [Module 3: Circulation]
   6. Issue Book to Student
   7. Return Book

 [Module 4: Fines & Reports]
   8. Late Fine Calculator Tool
   9. Generate Comprehensive Library Report

   0. Exit System
============================================================
```
