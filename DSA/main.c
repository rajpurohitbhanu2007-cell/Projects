/*
 * ============================================================================
 * Project: Student Record Management System (DSA in C)
 * 
 * Created By:
 * - Anjalee          (Roll No: 25egjcc006)
 * - Ankit Saini      (Roll No: 25egjcc007)
 * - Bhanu Pratap     (Roll No: 25egjcc008)
 * - Bhuvnesh Vaisnav (Roll No: 25egjcc009)
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100

// Student structure definition
typedef struct {
    int rollNo;
    char name[50];
    char branch[30];
    float marks;
} Student;

// Global array of students and counter
Student students[MAX_STUDENTS];
int studentCount = 0;

// Helper: Clear standard input buffer
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Helper: Read an integer safely
int readInt(const char *prompt) {
    int val;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &val) == 1) {
            clearBuffer();
            return val;
        }
        printf("Invalid input! Please enter a valid integer.\n");
        clearBuffer();
    }
}

// Helper: Read a float safely
float readFloat(const char *prompt) {
    float val;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &val) == 1) {
            clearBuffer();
            return val;
        }
        printf("Invalid input! Please enter a valid number for marks.\n");
        clearBuffer();
    }
}

// Helper: Read a string line safely
void readString(const char *prompt, char *buffer, int maxLen) {
    printf("%s", prompt);
    if (fgets(buffer, maxLen, stdin) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0'; // strip newline
    }
}

// Helper: Case-insensitive string comparison
int compareCaseInsensitive(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            return 0;
        }
        s1++;
        s2++;
    }
    return (*s1 == '\0' && *s2 == '\0');
}

// Helper: Find student index by Roll Number (Linear Search)
int findStudentIndexByRoll(int roll) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNo == roll) {
            return i;
        }
    }
    return -1;
}

// ==========================================
// MODULE 1: Student Registration & Storage
// ==========================================

// Add a new student record
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("\n[Error] Database full! Cannot add more students.\n");
        return;
    }

    printf("\n--- Add New Student ---\n");
    int roll = readInt("Enter Roll Number: ");

    // Validation: Duplicate roll number check
    if (findStudentIndexByRoll(roll) != -1) {
        printf("[Error] Student with Roll Number %d already exists! Duplicate not allowed.\n", roll);
        return;
    }

    students[studentCount].rollNo = roll;
    readString("Enter Student Name: ", students[studentCount].name, sizeof(students[studentCount].name));
    readString("Enter Branch (e.g., CSE, IT, ECE): ", students[studentCount].branch, sizeof(students[studentCount].branch));
    students[studentCount].marks = readFloat("Enter Total Marks (0 - 100): ");

    studentCount++;
    printf("\n[Success] Student record added successfully!\n");
}

// Update existing student record
void updateStudent() {
    if (studentCount == 0) {
        printf("\nNo student records available to update.\n");
        return;
    }

    printf("\n--- Update Student Record ---\n");
    int roll = readInt("Enter Roll Number to update: ");
    int index = findStudentIndexByRoll(roll);

    if (index == -1) {
        printf("[Error] Student with Roll Number %d not found!\n", roll);
        return;
    }

    printf("\nCurrent Details:\n");
    printf("Roll No: %d | Name: %s | Branch: %s | Marks: %.2f\n",
           students[index].rollNo, students[index].name, students[index].branch, students[index].marks);
    printf("Enter new details:\n");

    readString("Enter New Name: ", students[index].name, sizeof(students[index].name));
    readString("Enter New Branch: ", students[index].branch, sizeof(students[index].branch));
    students[index].marks = readFloat("Enter New Marks: ");

    printf("\n[Success] Student record updated successfully!\n");
}

// Delete student record
void deleteStudent() {
    if (studentCount == 0) {
        printf("\nNo student records available to delete.\n");
        return;
    }

    printf("\n--- Delete Student Record ---\n");
    int roll = readInt("Enter Roll Number to delete: ");
    int index = findStudentIndexByRoll(roll);

    if (index == -1) {
        printf("[Error] Student with Roll Number %d not found!\n", roll);
        return;
    }

    // Shift elements to the left to delete
    for (int i = index; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--;

    printf("\n[Success] Student record with Roll No %d deleted successfully!\n", roll);
}

// ==========================================
// MODULE 2: Display and Report Module
// ==========================================

// Display all students in tabular form
void displayAllStudents() {
    if (studentCount == 0) {
        printf("\nNo student records found in the system.\n");
        return;
    }

    printf("\n======================================================================\n");
    printf("| %-8s | %-24s | %-12s | %-10s |\n", "Roll No", "Name", "Branch", "Marks");
    printf("======================================================================\n");
    for (int i = 0; i < studentCount; i++) {
        printf("| %-8d | %-24s | %-12s | %-10.2f |\n",
               students[i].rollNo, students[i].name, students[i].branch, students[i].marks);
    }
    printf("======================================================================\n");
    printf("Total Students: %d\n", studentCount);
}

// Generate Branch-wise Report
void branchWiseReport() {
    if (studentCount == 0) {
        printf("\nNo student records available.\n");
        return;
    }

    char targetBranch[30];
    readString("\nEnter Branch to generate report (e.g., CSE, IT, ECE): ", targetBranch, sizeof(targetBranch));

    int count = 0;
    float totalMarks = 0;

    printf("\n======================================================================\n");
    printf("               BRANCH REPORT: %s\n", targetBranch);
    printf("======================================================================\n");
    printf("| %-8s | %-24s | %-12s | %-10s |\n", "Roll No", "Name", "Branch", "Marks");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < studentCount; i++) {
        if (compareCaseInsensitive(students[i].branch, targetBranch)) {
            printf("| %-8d | %-24s | %-12s | %-10.2f |\n",
                   students[i].rollNo, students[i].name, students[i].branch, students[i].marks);
            totalMarks += students[i].marks;
            count++;
        }
    }

    if (count == 0) {
        printf("| No students found in branch '%s'.                            |\n", targetBranch);
        printf("======================================================================\n");
    } else {
        printf("======================================================================\n");
        printf("Branch Total Students : %d\n", count);
        printf("Branch Average Marks  : %.2f\n", totalMarks / count);
    }
}

// Display total count
void countTotalStudents() {
    printf("\n-----------------------------------------------\n");
    printf(" Total Registered Students in System: %d\n", studentCount);
    printf("-----------------------------------------------\n");
}

// ==========================================
// MODULE 3: Searching Module
// ==========================================

// Search student by roll number using Linear Search
void searchByRoll() {
    if (studentCount == 0) {
        printf("\nNo records to search.\n");
        return;
    }

    printf("\n--- Search by Roll Number (Linear Search) ---\n");
    int roll = readInt("Enter Roll Number to search: ");
    int index = findStudentIndexByRoll(roll);

    if (index != -1) {
        printf("\n[Record Found!]\n");
        printf("----------------------------------------\n");
        printf("Roll Number : %d\n", students[index].rollNo);
        printf("Name        : %s\n", students[index].name);
        printf("Branch      : %s\n", students[index].branch);
        printf("Marks       : %.2f\n", students[index].marks);
        printf("----------------------------------------\n");
    } else {
        printf("\n[Record Not Found] No student found with Roll Number %d.\n", roll);
    }
}

// Search student by name (case-insensitive substring or exact match)
void searchByName() {
    if (studentCount == 0) {
        printf("\nNo records to search.\n");
        return;
    }

    char query[50];
    readString("\n--- Search by Name ---\nEnter Student Name to search: ", query, sizeof(query));

    int found = 0;
    printf("\nSearch Results for '%s':\n", query);
    printf("======================================================================\n");
    printf("| %-8s | %-24s | %-12s | %-10s |\n", "Roll No", "Name", "Branch", "Marks");
    printf("======================================================================\n");

    for (int i = 0; i < studentCount; i++) {
        // Compare case insensitive
        if (compareCaseInsensitive(students[i].name, query)) {
            printf("| %-8d | %-24s | %-12s | %-10.2f |\n",
                   students[i].rollNo, students[i].name, students[i].branch, students[i].marks);
            found++;
        }
    }

    if (!found) {
        printf("| Record Not Found: No student matches '%s'             |\n", query);
        printf("======================================================================\n");
    } else {
        printf("======================================================================\n");
        printf("Total matches found: %d\n", found);
    }
}

// ==========================================
// MODULE 4: Sorting & Ranking Module
// ==========================================

// Bubble Sort by Roll Number (Ascending)
void sortByRollNumber() {
    if (studentCount < 2) {
        printf("\nNot enough records to sort.\n");
        return;
    }

    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j].rollNo > students[j + 1].rollNo) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("\n[Success] Students sorted by Roll Number (Ascending).\n");
    displayAllStudents();
}

// Bubble Sort by Name (Alphabetical A-Z)
void sortByName() {
    if (studentCount < 2) {
        printf("\nNot enough records to sort.\n");
        return;
    }

    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (strcmp(students[j].name, students[j + 1].name) > 0) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("\n[Success] Students sorted by Name (Alphabetical A-Z).\n");
    displayAllStudents();
}

// Bubble Sort by Marks (Descending)
void sortByMarks() {
    if (studentCount < 2) {
        printf("\nNot enough records to sort.\n");
        return;
    }

    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j].marks < students[j + 1].marks) { // Highest to lowest
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("\n[Success] Students sorted by Marks (Highest to Lowest).\n");
    displayAllStudents();
}

// Generate Rank List and Highlight Topper
void generateRankList() {
    if (studentCount == 0) {
        printf("\nNo student records available to generate rank list.\n");
        return;
    }

    // Sort descending by marks first using Bubble Sort
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j].marks < students[j + 1].marks) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("\n================================================================================\n");
    printf("                           STUDENT MERIT / RANK LIST                            \n");
    printf("================================================================================\n");
    printf("| %-6s | %-8s | %-24s | %-10s | %-8s | %-8s |\n",
           "Rank", "Roll No", "Name", "Branch", "Marks", "Status");
    printf("================================================================================\n");

    for (int i = 0; i < studentCount; i++) {
        const char *status = (i == 0) ? "TOPPER" : "";
        printf("| %-6d | %-8d | %-24s | %-10s | %-8.2f | %-8s |\n",
               i + 1, students[i].rollNo, students[i].name, students[i].branch, students[i].marks, status);
    }
    printf("================================================================================\n");
    printf("CONGRATULATIONS TO TOPPER: %s with %.2f Marks!\n", students[0].name, students[0].marks);
}

// Pre-load default sample records for easy testing
void loadSampleData() {
    students[0] = (Student){101, "Aarav Sharma", "CSE", 92.5f};
    students[1] = (Student){104, "Diya Patel", "ECE", 88.0f};
    students[2] = (Student){102, "Bhanu Rajput", "CSE", 96.0f};
    students[3] = (Student){105, "Isha Verma", "IT", 79.5f};
    students[4] = (Student){103, "Chetan Gupta", "ECE", 84.5f};
    studentCount = 5;
}

// Main Menu
int main() {
    loadSampleData(); // Pre-load sample data for quick evaluation

    int choice;
    while (1) {
        printf("\n==================================================\n");
        printf("         STUDENT RECORD MANAGEMENT SYSTEM         \n");
        printf("==================================================\n");
        printf(" [Module 1: Registration & Storage]\n");
        printf("   1. Add New Student Record\n");
        printf("   2. Update Student Record\n");
        printf("   3. Delete Student Record\n");
        printf("\n [Module 2: Display & Reports]\n");
        printf("   4. Display All Students (Tabular)\n");
        printf("   5. Branch-wise Report\n");
        printf("   6. Count Total Students\n");
        printf("\n [Module 3: Searching]\n");
        printf("   7. Search by Roll Number (Linear Search)\n");
        printf("   8. Search by Student Name\n");
        printf("\n [Module 4: Sorting & Ranking]\n");
        printf("   9. Sort Students by Roll Number\n");
        printf("  10. Sort Students by Name (A-Z)\n");
        printf("  11. Sort Students by Marks\n");
        printf("  12. Generate Rank List & View Topper\n");
        printf("\n   0. Exit System\n");
        printf("==================================================\n");

        choice = readInt("Enter your choice (0-12): ");

        switch (choice) {
            case 1:  addStudent(); break;
            case 2:  updateStudent(); break;
            case 3:  deleteStudent(); break;
            case 4:  displayAllStudents(); break;
            case 5:  branchWiseReport(); break;
            case 6:  countTotalStudents(); break;
            case 7:  searchByRoll(); break;
            case 8:  searchByName(); break;
            case 9:  sortByRollNumber(); break;
            case 10: sortByName(); break;
            case 11: sortByMarks(); break;
            case 12: generateRankList(); break;
            case 0:
                printf("\nExiting Student Management System. Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid option! Please enter a number between 0 and 12.\n");
        }
    }

    return 0;
}
