/*
 * ============================================================================
 * Project: Library Management System (OOPs in C++)
 * 
 * Created By:
 * - Anjalee          (Roll No: 25egjcc006)
 * - Ankit Saini      (Roll No: 25egjcc007)
 * - Bhanu Pratap     (Roll No: 25egjcc008)
 * - Bhuvnesh Vaisnav (Roll No: 25egjcc009)
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <cctype>

using namespace std;

// ============================================================================
// OOP CONCEPT: Abstraction & Base Class (LibraryItem)
// ============================================================================
class LibraryItem {
protected:
    int id;
    string title;
    string author;
    bool isIssued;
    string issuedTo;
    int issueDurationDays;

public:
    LibraryItem(int itemId, const string &itemTitle, const string &itemAuthor)
        : id(itemId), title(itemTitle), author(itemAuthor),
          isIssued(false), issuedTo(""), issueDurationDays(0) {}

    virtual ~LibraryItem() {}

    // Pure virtual method (Abstraction & Polymorphism)
    virtual void display() const = 0;
    virtual double calculateFine(int actualDaysKept) const = 0;

    // Encapsulation: Getters and Setters
    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getIsIssued() const { return isIssued; }
    string getIssuedTo() const { return issuedTo; }
    int getIssueDurationDays() const { return issueDurationDays; }

    void setTitle(const string &newTitle) { title = newTitle; }
    void setAuthor(const string &newAuthor) { author = newAuthor; }

    void issueItem(const string &studentName, int days) {
        isIssued = true;
        issuedTo = studentName;
        issueDurationDays = days;
    }

    void returnItem() {
        isIssued = false;
        issuedTo = "";
        issueDurationDays = 0;
    }
};

// ============================================================================
// OOP CONCEPT: Inheritance & Derived Class (Book)
// ============================================================================
class Book : public LibraryItem {
private:
    static const int STANDARD_ALLOWED_DAYS = 14;     // Allowed borrowing period
    static constexpr double FINE_PER_DAY = 5.0;      // Late fine: 5 rupees/day

public:
    Book(int bookId, const string &bookTitle, const string &bookAuthor)
        : LibraryItem(bookId, bookTitle, bookAuthor) {}

    // Polymorphic display override
    void display() const override {
        cout << "| " << setw(8) << left << id
             << "| " << setw(32) << left << title
             << "| " << setw(22) << left << author
             << "| " << setw(12) << left << (isIssued ? "Issued" : "Available")
             << "| " << setw(18) << left << (isIssued ? issuedTo : "-") << " |\n";
    }

    // Polymorphic fine calculation override
    double calculateFine(int actualDaysKept) const override {
        if (actualDaysKept > STANDARD_ALLOWED_DAYS) {
            int lateDays = actualDaysKept - STANDARD_ALLOWED_DAYS;
            return lateDays * FINE_PER_DAY;
        }
        return 0.0;
    }

    int getAllowedDays() const { return STANDARD_ALLOWED_DAYS; }
    double getFineRate() const { return FINE_PER_DAY; }
};

// ============================================================================
// Helper Utilities for Safe Terminal Input
// ============================================================================
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getIntInput(const string &prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cout << "  [Error] Invalid number! Please enter an integer.\n";
        clearInput();
    }
}

string getStringInput(const string &prompt) {
    string val;
    while (true) {
        cout << prompt;
        getline(cin, val);
        // Trim leading and trailing spaces
        size_t start = val.find_first_not_of(" \t\r\n");
        size_t end = val.find_last_not_of(" \t\r\n");
        if (start != string::npos && end != string::npos) {
            return val.substr(start, end - start + 1);
        }
        cout << "  [Error] Input cannot be blank! Please re-enter.\n";
    }
}

bool caseInsensitiveSubstring(const string &haystack, const string &needle) {
    auto it = search(
        haystack.begin(), haystack.end(),
        needle.begin(), needle.end(),
        [](char ch1, char ch2) { return tolower(static_cast<unsigned char>(ch1)) == tolower(static_cast<unsigned char>(ch2)); }
    );
    return (it != haystack.end());
}

// ============================================================================
// OOP CONCEPT: System Class (LibraryManagementSystem)
// ============================================================================
class LibraryManagementSystem {
private:
    vector<Book> books;
    double totalFinesCollected;

    // Linear Search helper
    int findBookIndexById(int bookId) const {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getId() == bookId) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    void printTableHeader() const {
        cout << "===================================================================================================\n";
        cout << "| " << setw(8) << left << "Book ID"
             << "| " << setw(32) << left << "Title"
             << "| " << setw(22) << left << "Author"
             << "| " << setw(12) << left << "Status"
             << "| " << setw(18) << left << "Issued To" << " |\n";
        cout << "===================================================================================================\n";
    }

    void printTableFooter() const {
        cout << "===================================================================================================\n";
    }

public:
    LibraryManagementSystem() : totalFinesCollected(0.0) {
        // Pre-load default sample records for instant testing
        books.emplace_back(101, "Introduction to Algorithms", "CLRS");
        books.emplace_back(102, "OOP with C++", "E. Balagurusamy");
        books.emplace_back(103, "Clean Code", "Robert C. Martin");
        books.emplace_back(104, "The C Programming Language", "Kernighan & Ritchie");
        books.emplace_back(105, "Data Structures Using C++", "D. S. Malik");

        // Set initial issue states
        books[2].issueItem("Rahul Sharma", 14);
        books[4].issueItem("Priya Singh", 14);
    }

    // ------------------------------------------------------------------------
    // MODULE 1: Add, Update, and Delete Books
    // ------------------------------------------------------------------------
    void addBook() {
        cout << "\n--- [Module 1] Add New Book ---\n";
        int id = getIntInput("Enter Book ID: ");

        if (findBookIndexById(id) != -1) {
            cout << "  [Error] Book with ID " << id << " already exists! Duplicate ID not allowed.\n";
            return;
        }

        string title = getStringInput("Enter Book Title: ");
        string author = getStringInput("Enter Author Name: ");

        books.emplace_back(id, title, author);
        cout << "  [Success] Book \"" << title << "\" (ID: " << id << ") added to the library.\n";
    }

    void updateBook() {
        cout << "\n--- [Module 1] Update Book Details ---\n";
        if (books.empty()) {
            cout << "  [Notice] No books available to update.\n";
            return;
        }

        int id = getIntInput("Enter Book ID to update: ");
        int idx = findBookIndexById(id);

        if (idx == -1) {
            cout << "  [Error] Book with ID " << id << " not found!\n";
            return;
        }

        cout << "Current Details:\n";
        cout << "  Title : " << books[idx].getTitle() << "\n";
        cout << "  Author: " << books[idx].getAuthor() << "\n";

        string newTitle = getStringInput("Enter New Title: ");
        string newAuthor = getStringInput("Enter New Author: ");

        books[idx].setTitle(newTitle);
        books[idx].setAuthor(newAuthor);
        cout << "  [Success] Book ID " << id << " updated successfully!\n";
    }

    void deleteBook() {
        cout << "\n--- [Module 1] Delete Book ---\n";
        if (books.empty()) {
            cout << "  [Notice] No books available to delete.\n";
            return;
        }

        int id = getIntInput("Enter Book ID to delete: ");
        int idx = findBookIndexById(id);

        if (idx == -1) {
            cout << "  [Error] Book with ID " << id << " not found!\n";
            return;
        }

        if (books[idx].getIsIssued()) {
            cout << "  [Warning] Book is currently issued to \"" << books[idx].getIssuedTo()
                 << "\". Please return the book before deleting.\n";
            return;
        }

        string title = books[idx].getTitle();
        books.erase(books.begin() + idx);
        cout << "  [Success] Book \"" << title << "\" (ID: " << id << ") deleted successfully.\n";
    }

    // ------------------------------------------------------------------------
    // MODULE 2: Display and Search Books
    // ------------------------------------------------------------------------
    void displayAllBooks() const {
        cout << "\n--- [Module 2] Complete Library Catalog ---\n";
        if (books.empty()) {
            cout << "  [Notice] Library catalog is empty.\n";
            return;
        }

        printTableHeader();
        for (const auto &book : books) {
            book.display();
        }
        printTableFooter();
        cout << "Total Books in Catalog: " << books.size() << "\n";
    }

    void searchBooks() const {
        cout << "\n--- [Module 2] Search Books ---\n";
        if (books.empty()) {
            cout << "  [Notice] Library catalog is empty.\n";
            return;
        }

        cout << "  1. Search by Book ID\n";
        cout << "  2. Search by Book Title\n";
        int choice = getIntInput("Choose search method (1-2): ");

        if (choice == 1) {
            int id = getIntInput("Enter Book ID to search: ");
            int idx = findBookIndexById(id);
            if (idx != -1) {
                cout << "\n[Book Found!]\n";
                printTableHeader();
                books[idx].display();
                printTableFooter();
            } else {
                cout << "  [Record Not Found] No book found with ID " << id << ".\n";
            }
        } else if (choice == 2) {
            string query = getStringInput("Enter Book Title keyword to search: ");
            bool found = false;
            cout << "\nSearch Results for \"" << query << "\":\n";
            printTableHeader();
            for (const auto &book : books) {
                if (caseInsensitiveSubstring(book.getTitle(), query)) {
                    book.display();
                    found = true;
                }
            }
            printTableFooter();
            if (!found) {
                cout << "  [Record Not Found] No books match the title \"" << query << "\".\n";
            }
        } else {
            cout << "  [Error] Invalid search option.\n";
        }
    }

    // ------------------------------------------------------------------------
    // MODULE 3: Issue and Return Books
    // ------------------------------------------------------------------------
    void issueBook() {
        cout << "\n--- [Module 3] Issue Book ---\n";
        int id = getIntInput("Enter Book ID to issue: ");
        int idx = findBookIndexById(id);

        if (idx == -1) {
            cout << "  [Error] Book with ID " << id << " does not exist in library.\n";
            return;
        }

        if (books[idx].getIsIssued()) {
            cout << "  [Error] Book is already issued to: " << books[idx].getIssuedTo() << "!\n";
            return;
        }

        string studentName = getStringInput("Enter Student / Borrower Name: ");
        books[idx].issueItem(studentName, 14);

        cout << "  [Success] Book \"" << books[idx].getTitle()
             << "\" issued to " << studentName << " for 14 days.\n";
    }

    void returnBook() {
        cout << "\n--- [Module 3] Return Book ---\n";
        int id = getIntInput("Enter Book ID to return: ");
        int idx = findBookIndexById(id);

        if (idx == -1) {
            cout << "  [Error] Book with ID " << id << " does not exist.\n";
            return;
        }

        if (!books[idx].getIsIssued()) {
            cout << "  [Error] Book \"" << books[idx].getTitle() << "\" is not currently issued.\n";
            return;
        }

        int daysKept = getIntInput("Enter total number of days book was kept: ");
        double fine = books[idx].calculateFine(daysKept);

        cout << "\n--- Return Summary ---\n";
        cout << "Book Title        : " << books[idx].getTitle() << "\n";
        cout << "Borrowed By       : " << books[idx].getIssuedTo() << "\n";
        cout << "Allowed Duration  : " << books[idx].getAllowedDays() << " days\n";
        cout << "Days Kept         : " << daysKept << " days\n";

        if (fine > 0.0) {
            int overdueDays = daysKept - books[idx].getAllowedDays();
            cout << "Overdue Status    : OVERDUE by " << overdueDays << " days!\n";
            cout << "Late Fine (Rs. " << books[idx].getFineRate() << "/day): Rs. " << fixed << setprecision(2) << fine << "\n";
            cout << "  [Fine Collected] Rs. " << fine << " added to library accounts.\n";
            totalFinesCollected += fine;
        } else {
            cout << "Overdue Status    : Returned on time. No late fine applied.\n";
        }

        books[idx].returnItem();
        cout << "  [Success] Book returned successfully and marked Available!\n";
    }

    // ------------------------------------------------------------------------
    // MODULE 4: Calculate Late Fines and Generate Reports
    // ------------------------------------------------------------------------
    void calculateFineCalculator() const {
        cout << "\n--- [Module 4] Late Fine Calculator Tool ---\n";
        cout << "Standard Policy: 14 days free borrowing. Rs. 5.00 per day thereafter.\n";
        int days = getIntInput("Enter number of borrowing days: ");
        if (days <= 14) {
            cout << "Days kept: " << days << " (Within 14-day limit). Late Fine = Rs. 0.00\n";
        } else {
            int lateDays = days - 14;
            double fine = lateDays * 5.0;
            cout << "Days kept: " << days << " (Late by " << lateDays << " days).\n";
            cout << "Total Late Fine = " << lateDays << " x Rs. 5.00 = Rs. " << fixed << setprecision(2) << fine << "\n";
        }
    }

    void generateReports() const {
        cout << "\n===================================================================================================\n";
        cout << "                               LIBRARY STATISTICAL REPORT & SUMMARY                                \n";
        cout << "===================================================================================================\n";

        int totalCount = static_cast<int>(books.size());
        int issuedCount = 0;
        int availableCount = 0;

        for (const auto &b : books) {
            if (b.getIsIssued()) issuedCount++;
            else availableCount++;
        }

        cout << " Total Books in Library    : " << totalCount << "\n";
        cout << " Currently Available Books : " << availableCount << "\n";
        cout << " Currently Issued Books    : " << issuedCount << "\n";
        cout << " Total Late Fines Collected: Rs. " << fixed << setprecision(2) << totalFinesCollected << "\n";
        cout << "---------------------------------------------------------------------------------------------------\n";

        cout << "\n--- LIST OF CURRENTLY ISSUED BOOKS ---\n";
        if (issuedCount == 0) {
            cout << "  No books are currently issued.\n";
        } else {
            printTableHeader();
            for (const auto &b : books) {
                if (b.getIsIssued()) {
                    b.display();
                }
            }
            printTableFooter();
        }

        cout << "\n--- LIST OF AVAILABLE BOOKS ---\n";
        if (availableCount == 0) {
            cout << "  No books are currently available.\n";
        } else {
            printTableHeader();
            for (const auto &b : books) {
                if (!b.getIsIssued()) {
                    b.display();
                }
            }
            printTableFooter();
        }
    }
};

// ============================================================================
// Main Function & Interactive Terminal Menu
// ============================================================================
int main() {
    LibraryManagementSystem library;
    int choice;

    while (true) {
        cout << "\n============================================================\n";
        cout << "           LIBRARY MANAGEMENT SYSTEM (OOPs in C++)          \n";
        cout << "============================================================\n";
        cout << " [Module 1: Book Management]\n";
        cout << "   1. Add New Book\n";
        cout << "   2. Update Book Details\n";
        cout << "   3. Delete Book\n";
        cout << "\n [Module 2: Catalog & Search]\n";
        cout << "   4. Display All Books\n";
        cout << "   5. Search Books (by ID or Title)\n";
        cout << "\n [Module 3: Circulation]\n";
        cout << "   6. Issue Book to Student\n";
        cout << "   7. Return Book\n";
        cout << "\n [Module 4: Fines & Reports]\n";
        cout << "   8. Late Fine Calculator Tool\n";
        cout << "   9. Generate Comprehensive Library Report\n";
        cout << "\n   0. Exit System\n";
        cout << "============================================================\n";

        choice = getIntInput("Enter your choice (0-9): ");

        switch (choice) {
            case 1: library.addBook(); break;
            case 2: library.updateBook(); break;
            case 3: library.deleteBook(); break;
            case 4: library.displayAllBooks(); break;
            case 5: library.searchBooks(); break;
            case 6: library.issueBook(); break;
            case 7: library.returnBook(); break;
            case 8: library.calculateFineCalculator(); break;
            case 9: library.generateReports(); break;
            case 0:
                cout << "\nExiting Library Management System. Thank you!\n";
                return 0;
            default:
                cout << "  [Error] Invalid choice! Please select an option between 0 and 9.\n";
        }
    }

    return 0;
}
