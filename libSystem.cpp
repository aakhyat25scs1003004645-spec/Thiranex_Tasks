#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ================= BOOK CLASS =================
class Book {
private:
    int bookId;
    string title;
    string author;
    bool available;

public:
    Book(int id, string t, string a) {
        bookId = id;
        title = t;
        author = a;
        available = true;
    }

    int getBookId() {
        return bookId;
    }

    string getTitle() {
        return title;
    }

    string getAuthor() {
        return author;
    }

    bool isAvailable() {
        return available;
    }

    void issueBook() {
        available = false;
    }

    void returnBook() {
        available = true;
    }

    void displayBook() {
        cout << "Book ID   : " << bookId << endl;
        cout << "Title     : " << title << endl;
        cout << "Author    : " << author << endl;
        cout << "Status    : "
             << (available ? "Available" : "Issued") << endl;
        cout << "-----------------------------" << endl;
    }
};


// ================= MEMBER CLASS =================
class Member {
private:
    int memberId;
    string name;

public:
    Member(int id, string n) {
        memberId = id;
        name = n;
    }

    int getMemberId() {
        return memberId;
    }

    string getName() {
        return name;
    }

    void displayMember() {
        cout << "Member ID : " << memberId << endl;
        cout << "Name      : " << name << endl;
        cout << "-----------------------------" << endl;
    }
};


// ================= LIBRARY CLASS =================
class Library {
private:
    vector<Book> books;
    vector<Member> members;

public:

    // Add a new book
    void addBook() {
        int id;
        string title, author;

        cout << "\nEnter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        books.push_back(Book(id, title, author));

        cout << "\nBook added successfully!\n";
    }


    // Add a new member
    void addMember() {
        int id;
        string name;

        cout << "\nEnter Member ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Member Name: ";
        getline(cin, name);

        members.push_back(Member(id, name));

        cout << "\nMember added successfully!\n";
    }


    // Display all books
    void displayBooks() {
        if (books.empty()) {
            cout << "\nNo books available.\n";
            return;
        }

        cout << "\n========== ALL BOOKS ==========\n";

        for (int i = 0; i < books.size(); i++) {
            books[i].displayBook();
        }
    }


    // Display all members
    void displayMembers() {
        if (members.empty()) {
            cout << "\nNo members registered.\n";
            return;
        }

        cout << "\n========== ALL MEMBERS ==========\n";

        for (int i = 0; i < members.size(); i++) {
            members[i].displayMember();
        }
    }


    // Search book by title or author
    void searchBook() {
        if (books.empty()) {
            cout << "\nNo books available.\n";
            return;
        }

        int choice;
        string search;

        cout << "\nSearch Book By:\n";
        cout << "1. Title\n";
        cout << "2. Author\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        cout << "Enter search text: ";
        getline(cin, search);

        bool found = false;

        for (int i = 0; i < books.size(); i++) {

            if (choice == 1 && books[i].getTitle() == search) {
                books[i].displayBook();
                found = true;
            }
            else if (choice == 2 && books[i].getAuthor() == search) {
                books[i].displayBook();
                found = true;
            }
        }

        if (!found) {
            cout << "\nBook not found.\n";
        }
    }


    // Issue a book
    void issueBook() {
        int bookId, memberId;

        cout << "\nEnter Book ID: ";
        cin >> bookId;

        cout << "Enter Member ID: ";
        cin >> memberId;

        // Check whether member exists
        bool memberFound = false;

        for (int i = 0; i < members.size(); i++) {
            if (members[i].getMemberId() == memberId) {
                memberFound = true;
                break;
            }
        }

        if (!memberFound) {
            cout << "\nMember not found!\n";
            return;
        }

        // Find book
        for (int i = 0; i < books.size(); i++) {

            if (books[i].getBookId() == bookId) {

                if (books[i].isAvailable()) {
                    books[i].issueBook();

                    cout << "\nBook issued successfully to Member ID "
                         << memberId << ".\n";
                }
                else {
                    cout << "\nBook is already issued.\n";
                }

                return;
            }
        }

        cout << "\nBook not found!\n";
    }


    // Return a book
    void returnBook() {
        int bookId;

        cout << "\nEnter Book ID to return: ";
        cin >> bookId;

        for (int i = 0; i < books.size(); i++) {

            if (books[i].getBookId() == bookId) {

                if (!books[i].isAvailable()) {
                    books[i].returnBook();

                    cout << "\nBook returned successfully!\n";
                }
                else {
                    cout << "\nThis book was not issued.\n";
                }

                return;
            }
        }

        cout << "\nBook not found!\n";
    }
};


// ================= MAIN FUNCTION =================
int main() {

    Library library;
    int choice;

    do {
        cout << "\n\n====================================\n";
        cout << "       LIBRARY MANAGEMENT SYSTEM\n";
        cout << "====================================\n";

        cout << "1. Add Book\n";
        cout << "2. Add Member\n";
        cout << "3. Display All Books\n";
        cout << "4. Display All Members\n";
        cout << "5. Search Book\n";
        cout << "6. Issue Book\n";
        cout << "7. Return Book\n";
        cout << "8. Exit\n";

        cout << "------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            library.addBook();
            break;

        case 2:
            library.addMember();
            break;

        case 3:
            library.displayBooks();
            break;

        case 4:
            library.displayMembers();
            break;

        case 5:
            library.searchBook();
            break;

        case 6:
            library.issueBook();
            break;

        case 7:
            library.returnBook();
            break;

        case 8:
            cout << "\nThank you for using the Library Management System!\n";
            break;

        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 8);

    return 0;
}