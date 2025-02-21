#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    string isbn;
    bool isIssued;
};

struct Borrower {
    int id;
    string name;
};

struct Transaction {
    int bookId;
    int borrowerId;
    string date;
    bool returned;
};

vector<Book> books;
vector<Borrower> borrowers;
vector<Transaction> transactions;

void addBook(int id, string title, string author, string isbn) {
    books.push_back({id, title, author, isbn, false});
    cout << "Book added successfully!\n";
}

void addBorrower(int id, string name) {
    borrowers.push_back({id, name});
    cout << "Borrower added successfully!\n";
}

void issueBook(int bookId, int borrowerId, string date) {
    for (auto &book : books) {
        if (book.id == bookId && !book.isIssued) {
            book.isIssued = true;
            transactions.push_back({bookId, borrowerId, date, false});
            cout << "Book issued successfully!\n";
            return;
        }
    }
    cout << "Book not available or does not exist!\n";
}

void returnBook(int bookId, string returnDate) {
    for (auto &book : books) {
        if (book.id == bookId && book.isIssued) {
            book.isIssued = false;
            for (auto &transaction : transactions) {
                if (transaction.bookId == bookId && !transaction.returned) {
                    transaction.returned = true;
                    cout << "Book returned successfully!\n";
                    return;
                }
            }
        }
    }
    cout << "Invalid return attempt!\n";
}

void searchBook(string query) {
    cout << "Search Results:\n";
    for (const auto &book : books) {
        if (book.title.find(query) != string::npos || book.author.find(query) != string::npos || book.isbn == query) {
            cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.isbn;
            cout << (book.isIssued ? " (Issued)" : " (Available)") << "\n";
        }
    }
}

void calculateFine(int daysOverdue) {
    const double finePerDay = 1.0; // Example fine rate
    double totalFine = daysOverdue * finePerDay;
    cout << "Total fine: $" << totalFine << "\n";
}

void displayBooks() {
    cout << "Book List:\n";
    for (const auto &book : books) {
        cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.isbn;
        cout << (book.isIssued ? " (Issued)" : " (Available)") << "\n";
    }
}

int main() {
    addBook(1, "The Great Gatsby", "F. Scott Fitzgerald", "9780743273565");
    addBook(2, "1984", "George Orwell", "9780451524935");
    addBorrower(1, "Alice Johnson");
    issueBook(1, 1, "2025-02-17");
    displayBooks();
    returnBook(1, "2025-02-24");
    displayBooks();
    searchBook("1984");
    calculateFine(5);
    return 0;
}
