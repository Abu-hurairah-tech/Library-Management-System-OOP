#include "Books.h"
#include "members.h"
#include "Library.h"
#include "Library-Books-Management.h"
#include "Library-Member-Management.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;

bool checkDate(const string &date)
{
    // Must be exactly "DD MM YYYY" → 10 characters
    if (date.length() != 10)
        return false;

    // Check spaces
    if (date[2] != ' ' || date[5] != ' ')
        return false;

    // Check digits
    for (int i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5)
            continue;
        if (!isdigit(date[i]))
            return false;
    }

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    // Basic range checks
    if (day < 1 || day > 31)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (year < 1000)
        return false;

    return true;
}

Library::Library() {}
Library::~Library() {}

void Library::saveIssuedBooks()
{
    ofstream outputFile("Issue.csv");
    if (!outputFile)
        return;

    outputFile << "Member ID,Book ID,Date Of Issue,Return Status" << endl;
    
}

void Library::issueBook()
{
    int memberID, bookID;
    string date;
    cout << "Enter Member ID: ";
    cin >> memberID;

    LibraryMember *member = membersMgr.searchMember();
    if (!member)
        return;

    cout << "Enter Book ID: ";
    cin >> bookID;
    Book *book = booksMgr.searchByID();
    if (!book)
        return;

    bool validDate = false;
    cout << "Enter Issue Date (DD MM YYYY):";
    do
    {
        getline(cin, date);
        if (checkDate(date))
            validDate = true;
        else
            cout << "Invalid Date! Try Again." << endl;
    } while (!validDate);

    if (book->getCopies() > 0)
    {
        book->setCopies(book->getCopies() - 1);
        member->setNumberOfBooksBorrowed(member->getNumberOfBooksBorrowed() + 1);
        booksMgr.saveBooks();
        membersMgr.saveMembers();

        cout << "Transaction Successful! Book Issued to Member " << member->getName() << endl;
    }
    else
    {
        if(member->getNumberOfBooksBorrowed() >= member->getBorrowLimit())
        {
            cout << "Borrow Limit Reached!";
            return;
        }
    }
}