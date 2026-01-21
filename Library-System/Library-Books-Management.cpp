#include "Books.h"
#include "members.h"
#include "Library-Books-Management.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

bool checkISBN(int i)
{
    return i >= 1000000000 && i <= 9999999999;
}

BooksManager::BooksManager() {}
BooksManager::~BooksManager() {}

void BooksManager::loadBooks()
{
    ifstream inputFile("Books.csv");
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
        int isbn = isbnStr.empty() ? 0 : stoi(isbnStr);
        int copies = copiesStr.empty() ? 0 : stoi(copiesStr);

        if (!idStr.empty())
        {
            Book b(id, titleStr, authorStr, isbn);
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
    ofstream outputFile("Books.csv");
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

    string title, author;
    int id, isbn;

    cout << "Enter Book ID: ";
    do
    {
        cin >> id;

        if (cin.fail() || id <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID. Try again: ";
        }

    } while (cin.fail() || id <= 0);

    for (const auto &b : books)
    {
        if (b.getID() == id)
        {
            cout << "Book with this ID already exists!" << endl;
            return;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Book Title: ";
    getline(cin, title);
    cout << "Enter Book Author: ";
    getline(cin, author);
    bool validISBN = false;
    cout << "Enter ISBN:";
    do
    {
        cin >> isbn;
        for (const auto &b : books)
        {
            if (b.getISBN() == isbn)
            {
                cout << "Book with this ISBN already exists!" << endl;
                return;
            }
        }
        if (checkISBN(isbn))
            validISBN = true;
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ISBN! Try Again." << endl;
        }
    } while (!validISBN);
    cin.ignore();

    Book newBook(id, title, author, isbn);
    int copies;
    cout << "Enter number of copies: ";
    do
    {
        cin >> copies;

        if (cin.fail() || copies <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid copies. Try again: ";
        }

    } while (cin.fail() || copies <= 0);
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
    cin >> id;
    while (cin.fail() || id <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID. Try again: ";
        cin >> id;
    }

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

Book *BooksManager::searchByTitle()
{
    if (books.empty())
    {
        cout << "No books to search.\n";
        return nullptr;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string title;
    cout << "Enter Book title to search: ";
    getline(cin, title);

    for (auto &b : books)
    {
        if (b.getTitle() == title)
        {
            return &b;
        }
    }
    cout << "Book Not Found" << endl;
    return nullptr;
}
Book *BooksManager::searchByAuthor()
{
    if (books.empty())
    {
        cout << "No books to search.\n";
        return nullptr;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string author;
    cout << "Enter Book Author to search: ";
    getline(cin, author);

    for (auto &b : books)
    {
        if (b.getAuthor() == author)
        {
            return &b;
        }
    }
    cout << "Book Not Found" << endl;
    return nullptr;
}
Book *BooksManager::searchByISBN()
{
    if (books.empty())
    {
        cout << "No books to search.\n";
        return nullptr;
    }

    int isbn;
    cout << "Enter Book ISBN to search: ";
    cin >> isbn;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ISBN. Try again: ";
        cin >> isbn;
    }

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
    int isbn;

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
    cout << "Enter Book ISBN (Enter 0 to keep the same): ";
    cin >> isbn;
    if (!cin.fail() && isbn != 0)
    {
        for (const auto &bk : books)
        {
            if (bk.getISBN() == isbn && bk.getID() != b->getID())
            {
                cout << "Another book already has this ISBN!\n";
                return;
            }
        }

        if (checkISBN(isbn))
            b->setISBN(isbn);
        else
        {
            cout << "Invalid ISBN. Update cancelled.\n";
            return;
        }
    }
    saveBooks();
    cout << "Book updated successfully.\n";
}
