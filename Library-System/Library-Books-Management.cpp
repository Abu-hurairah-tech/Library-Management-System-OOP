#include "Books.h"
#include "members.h"
#include "Library-Books-Management.h"
#include "DateUtils.h"
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

bool checkISBN(const string &i)
{
    // 1. Check for exact length (10 digits)
    if (i.length() != 10)
    {
        return false;
    }

    // 2. Ensure every character is a digit '0'-'9'
    for (char c : i)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }

    return true;
}

BooksManager::BooksManager() { loadBooks(); }
BooksManager::~BooksManager() {}

void BooksManager::loadBooks()
{
    ifstream inputFile("Data/Books.csv");
    if (!inputFile)
        return;
    string line;
    getline(inputFile, line);
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        string idStr, titleStr, authorStr, isbnStr, statusStr, copiesStr;

        getline(ss, idStr, ',');
        getline(ss, titleStr, ',');
        getline(ss, authorStr, ',');
        getline(ss, isbnStr, ',');
        getline(ss, statusStr, ',');
        getline(ss, copiesStr);

        int id = idStr.empty() ? 0 : stoi(idStr);
        int copies = copiesStr.empty() ? 0 : stoi(copiesStr);

        if (!idStr.empty())
        {
            Book b(id, titleStr, authorStr, isbnStr);
            if (!statusStr.empty())
                b.setStatus(statusStr);
            if (copies > 0)
                b.setCopies(copies);
            books.push_back(b);
        }
    }
    inputFile.close();
}
void BooksManager::saveBooks()
{
    ofstream outputFile("Data/Books.csv");
    if (!outputFile)
        return;

    outputFile << "ID,Title,Author,ISBN,Status,Copies\n";

    for (auto &b : books)
    {
        b.writeToFile(outputFile);
    }

    outputFile.close();
}

void BooksManager::addBook()
{

    string title, author, isbn;
    int id;
    bool idExists, isbnExists;
    do
    {
        idExists = false;
        cout << "Enter Book ID: ";

        id = getValidInteger();

        if (id <= 0)
        {
            cout << "ID must be a positive number!\n";
            idExists = true;
            continue;
        }

        for (const auto &b : books)
        {
            if (b.getID() == id)
            {
                cout << "Book with this ID already exists! Try a different ID.\n";
                idExists = true;
                break;
            }
        }
    } while (idExists);

    if (cin.peek() == '\n')
        cin.ignore();
    cout << "Enter Book Title: ";
    getline(cin, title);
    cout << "Enter Book Author: ";
    getline(cin, author);
    bool validISBN = false;
    do
    {
        cout << "Enter ISBN: ";
        getline(cin, isbn);

        // 2. Uniqueness Check: Ensure another book doesn't already have this ISBN
        bool isDuplicate = false;
        for (const auto &b : books)
        {
            if (b.getISBN() == isbn)
            {
                cout << "Book with this ISBN already exists! Try again.\n";
                isDuplicate = true;
                break;
            }
        }

        if (isDuplicate)
            continue; // Restart loop if it's a duplicate

        // 3. Format Check: Use your existing checkISBN logic (range check)
        if (checkISBN(isbn))
        {
            validISBN = true; // All checks passed!
        }
        else
        {
            cout << "Invalid ISBN format! (Must be 10 digits). Try Again.\n";
        }

    } while (!validISBN);

    Book newBook(id, title, author, isbn);
    int copies;
    do
    {
        cout << "Enter number of copies: ";
        copies = getValidInteger();

        if (copies <= 0)
        {
            cout << "Copies must be a positive number!\n";
            continue;
        }
    } while (copies <= 0);
    newBook.setCopies(copies);
    books.push_back(newBook);
    saveBooks();
    cout << "Book added successfully.\n";
}

Book *BooksManager::searchByID()
{
    if (books.empty())
    {
        cout << "No books to search.\n";
        return nullptr;
    }

    int id;
    cout << "Enter Book ID to search: ";
    id = getValidInteger();
    for (auto &b : books)
    {
        if (b.getID() == id)
        {
            return &b;
        }
    }
    cout << "Book Not Found" << endl;
    return nullptr;
}

void BooksManager::searchByTitle()
{
    if (books.empty())
    {
        cout << "No books to search.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string title;
    cout << "Enter Book Title to search: ";
    getline(cin, title);

    bool found = false;

    cout << "\n==================Matching Books:==================\n";
    cout << left << setw(10) << "ID"
         << setw(25) << "Title"
         << setw(25) << "Author"
         << setw(15) << "ISBN"
         << endl;

    cout << string(75, '-') << endl;

    for (const auto &b : books)
    {
        if (b.getTitle() == title)
        {
            found = true;
            cout << left << setw(10) << b.getID()
                 << setw(25) << b.getTitle()
                 << setw(25) << b.getAuthor()
                 << setw(15) << b.getISBN()
                 << endl;
        }
    }

    if (!found)
        cout << "No books found with this title.\n";
}

void BooksManager::searchByAuthor()
{
    if (books.empty())
    {
        cout << "No books to search.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string author;
    cout << "Enter Book Author to search: ";
    getline(cin, author);

    bool found = false;

    cout << "\n==================Matching Books:==================\n";
    cout << left << setw(10) << "ID"
         << setw(25) << "Title"
         << setw(25) << "Author"
         << setw(15) << "ISBN"
         << endl;

    cout << string(75, '-') << endl;

    for (const auto &b : books)
    {
        if (b.getAuthor() == author)
        {
            found = true;
            cout << left << setw(10) << b.getID()
                 << setw(25) << b.getTitle()
                 << setw(25) << b.getAuthor()
                 << setw(15) << b.getISBN()
                 << endl;
        }
    }

    if (!found)
        cout << "No books found for this author.\n";
}

Book *BooksManager::searchByISBN()
{
    if (books.empty())
    {
        cout << "No books to search.\n";
        return nullptr;
    }

    string isbn;
    bool validFormat = false;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do
    {
        cout << "Enter Book ISBN to search: ";
        getline(cin, isbn);

        if (checkISBN(isbn))
        {
            validFormat = true;
        }
        else
        {
            cout << "Invalid format! ISBN must be exactly 10 digits. Try again.\n";
        }
    } while (!validFormat);

    for (auto &b : books)
    {
        if (b.getISBN() == isbn)
        {
            return &b;
        }
    }

    cout << "Book Not Found" << endl;
    return nullptr;
}

void BooksManager::removeBook()
{
    int id;
    cout << "Enter Book ID to search: ";
    cin >> id;
    while (cin.fail() || id <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID. Try again: ";
        cin >> id;
    }

    for (auto it = books.begin(); it != books.end(); ++it)
    {
        if (it->getID() == id)
        {
            books.erase(it);
            cout << "Book ID " << id << " successfully removed from system.\n";
            saveBooks();
            return;
        }
    }
    cout << "Error: Book ID " << id << " not found.\n";
    return;
}

int BooksManager::getTotalBooks()
{
    return books.size();
}

int BooksManager::getAvailableBooks()
{
    int totalCopies = 0;
    for (const auto &b : books)
    {
        totalCopies += b.getCopies();
    }
    return totalCopies;
}

void BooksManager::updateBook()
{
    Book *b = searchByID();
    if (b == nullptr)
        return;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string title, author;
    string isbn;

    cout << "--Update Book--" << endl;
    cout << "Current Title: " << b->getTitle() << endl;
    cout << "Enter Book title (leave empty to keep the same): ";
    getline(cin, title);

    if (!title.empty())
        b->setTitle(title);

    cout << "Current Author: " << b->getAuthor() << endl;
    cout << "Enter Book Author (leave empty to keep the same): ";
    getline(cin, author);

    if (!author.empty())
        b->setAuthor(author);

    cout << "Current ISBN: " << b->getISBN() << endl;

    string newIsbn;
    bool validUpdate = false;

    do
    {
        cout << "Enter Book ISBN (leave empty to keep the same): ";
        getline(cin, newIsbn);

        if (newIsbn.empty())
        {
            validUpdate = true;
            break;
        }

        if (!checkISBN(newIsbn))
        {
            cout << "Invalid ISBN format! Must be 10 digits. Try again.\n";
            continue;
        }

        bool isDuplicate = false;
        for (const auto &bk : books)
        {
            if (bk.getISBN() == newIsbn && bk.getID() != b->getID())
            {
                cout << "Another book already has this ISBN! Try again.\n";
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate)
        {
            b->setISBN(newIsbn);
            validUpdate = true;
        }

    } while (!validUpdate);
    saveBooks();
    cout << "Book updated successfully.\n";
}

void BooksManager::displayBooks()
{
    loadBooks();
    if (books.empty())
    {
        cout << "No books available.\n";
        return;
    }

    cout << "============================================== Book Details ==============================================" << endl;

    cout << left
         << setw(5) << "ID" << "| "
         << setw(20) << "Title" << "| "
         << setw(20) << "Author(s)" << "| "
         << setw(15) << "ISBN" << "| "
         << setw(20) << "Status" << "| "
         << setw(15) << "Copies" << "|\n";

    cout << string(106, '-') << endl;

    for (const auto &b : books)
    {
        cout << left
             << setw(5) << b.getID() << "| "
             << setw(20) << b.getTitle() << "| "
             << setw(20) << b.getAuthor() << "| "
             << setw(15) << b.getISBN() << "| "
             << setw(20) << b.getStatus() << "| "
             << setw(15) << b.getCopies() << endl;
    }
}
