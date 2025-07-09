// book system management.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Book {
    string title;
    string author;
    int year;
};
void addBook() {
    Book book;
    ofstream file("books.txt", ios::app); // append mode

    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, book.title);
    cout << "Enter author name: ";
    getline(cin, book.author);
    cout << "Enter year of publication: ";
    cin >> book.year;

    file << book.title << "|" << book.author << "|" << book.year << endl;
    file.close();
    cout << "Book added successfully!\n";
}
void displayBooks() {
    ifstream file("books.txt");
    Book book;
    string line;

    cout << "\nAll Books:\n";
    while (getline(file, line)) {
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1 + 1);
        book.title = line.substr(0, pos1);
        book.author = line.substr(pos1 + 1, pos2 - pos1 - 1);
        book.year = stoi(line.substr(pos2 + 1));
        cout << "Title: " << book.title << ", Author: " << book.author << ", Year: " << book.year << endl;
    }
    file.close();
}
void searchBook() {
    ifstream file("books.txt");
    Book book;
    string line, titleToSearch;
    bool found = false;

    cin.ignore();
    cout << "Enter title to search: ";
    getline(cin, titleToSearch);

    while (getline(file, line)) {
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1 + 1);
        book.title = line.substr(0, pos1);
        book.author = line.substr(pos1 + 1, pos2 - pos1 - 1);
        book.year = stoi(line.substr(pos2 + 1));

        if (book.title == titleToSearch) {
            cout << "Book found! Title: " << book.title << ", Author: " << book.author << ", Year: " << book.year << endl;
            found = true;
            break;
        }
    }
    file.close();
    if (!found) cout << "Book not found.\n";
}
void deleteBook() {
    ifstream file("books.txt");
    ofstream temp("temp.txt");
    Book book;
    string line, titleToDelete;
    bool deleted = false;

    cin.ignore();
    cout << "Enter title to delete: ";
    getline(cin, titleToDelete);

    while (getline(file, line)) {
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1 + 1);
        string title = line.substr(0, pos1);

        if (title != titleToDelete) {
            temp << line << endl;
        }
        else {
            deleted = true;
        }
    }

    file.close();
    temp.close();
    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (deleted)
        cout << "Book deleted successfully.\n";
    else
        cout << "Book not found.\n";
}
int main() {
    int choice;
    do {
        cout << "\n--- Book Management System ---\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addBook(); break;
        case 2: displayBooks(); break;
        case 3: searchBook(); break;
        case 4: deleteBook(); break;
        case 0: cout << "Exiting program.\n"; break;
        default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
