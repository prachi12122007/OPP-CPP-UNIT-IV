#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Book {
private:
    string isbn;
    string title;
    string author;
    string category;
    bool available;

public:
    Book()
        : available(true) {}

    Book(string i, string t, string a,
         string c, bool av = true)
        : isbn(i),
          title(t),
          author(a),
          category(c),
          available(av) {}

    string getISBN() const {
        return isbn;
    }

    bool isAvailable() const {
        return available;
    }

    void issue() {
        available = false;
    }

    void returnBook() {
        available = true;
    }

    void display() const {
        cout << "ISBN: " << isbn << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Category: " << category << endl;
        cout << "Status: "
             << (available ? "Available" : "Issued")
             << endl;
    }

    void saveToFile(ofstream& out) const {
        out << isbn << "|"
            << title << "|"
            << author << "|"
            << category << "|"
            << available << endl;
    }

    bool loadFromLine(const string& line) {

        string availableText;
        stringstream ss(line);

        if (!getline(ss, isbn, '|'))
            return false;

        if (!getline(ss, title, '|'))
            return false;

        if (!getline(ss, author, '|'))
            return false;

        if (!getline(ss, category, '|'))
            return false;

        if (!getline(ss, availableText))
            return false;

        available = (availableText == "1");

        return true;
    }
};

void addBook() {

    ofstream file(
        "library.txt",
        ios::app
    );

    if (!file) {
        cout << "Unable to open file."
             << endl;
        return;
    }

    string isbn, title, author, category;

    cout << "Enter ISBN: ";
    getline(cin, isbn);

    cout << "Enter Title: ";
    getline(cin, title);

    cout << "Enter Author: ";
    getline(cin, author);

    cout << "Enter Category: ";
    getline(cin, category);

    Book book(
        isbn,
        title,
        author,
        category
    );

    book.saveToFile(file);

    file.close();

    cout << "Book added successfully."
         << endl;
}

void searchBook() {

    ifstream file("library.txt");

    if (!file) {
        cout << "Library file not found."
             << endl;
        return;
    }

    string searchISBN;

    cout << "Enter ISBN to search: ";
    getline(cin, searchISBN);

    string line;
    bool found = false;

    while (getline(file, line)) {

        Book book;

        if (book.loadFromLine(line)) {

            if (book.getISBN() == searchISBN) {

                cout << "\nBook Found:\n";
                book.display();

                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "Book not found."
             << endl;
    }

    file.close();
}

void displayAllBooks() {

    ifstream file("library.txt");

    if (!file) {
        cout << "Library file not found."
             << endl;
        return;
    }

    string line;

    cout << "\n=== Library Books ===\n";

    while (getline(file, line)) {

        Book book;

        if (book.loadFromLine(line)) {
            book.display();
            cout << "----------------------"
                 << endl;
        }
    }

    file.close();
}

int main() {

    int choice;

    do {

        cout << "\n=== Library Book Management ==="
             << endl;

        cout << "1. Add Book" << endl;
        cout << "2. Search Book" << endl;
        cout << "3. Display All Books" << endl;
        cout << "4. Exit" << endl;

        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {

        case 1:
            addBook();
            break;

        case 2:
            searchBook();
            break;

        case 3:
            displayAllBooks();
            break;

        case 4:
            cout << "Program ended."
                 << endl;
            break;

        default:
            cout << "Invalid choice."
                 << endl;
        }

    } while (choice != 4);

    return 0;
}
