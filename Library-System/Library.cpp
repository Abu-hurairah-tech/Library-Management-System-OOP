#include "Books.h"
#include "members.h"
#include "Library.h"
#include "Library-Books-Management.h"
#include "Library-Member-Management.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
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

void Library::loadIssuedBooks()
{
    ifstream inputFile("Issue.csv");
    if (!inputFile)
        return;
    string line;
    getline(inputFile, line);
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        string mid, bid, returned, doi;

        getline(ss, mid, ',');
        getline(ss, bid, ',');
        getline(ss, doi, ',');
        getline(ss, returned);

        int id = mid.empty() ? 0 : stoi(mid);
        int bookid = bid.empty() ? 0 : stoi(bid);
        bool returnStat = returned.empty() ? true : false;

        if (!mid.empty() && !bid.empty())
        {
            IssueRecords i(id, bookid, doi, returnStat);
            issuedBooks.push_back(i);
        }
    }
    inputFile.close();
}

void Library::saveIssuedBooks()
{
    ofstream outputFile("Issue.csv");
    if (!outputFile)
        return;

    outputFile << "Member ID,Book ID,Date Of Issue,Return Status" << endl;
    for (auto &i : issuedBooks)
    {
        i.writeToFile(outputFile);
    }
}

void Library::issueBook()
{
    // Search for member
    LibraryMember *member = membersMgr.searchMember();
    if (!member)
        return;

    // Check borrow limit first
    if (member->getNumberOfBooksBorrowed() >= member->getBorrowLimit())
    {
        cout << "Borrow Limit Reached!\n";
        return;
    }

    // Search for book
    Book *book = booksMgr.searchByID();
    if (!book)
        return;

    // Check if book has copies available
    if (book->getCopies() <= 0)
    {
        cout << "No copies available for this book!\n";
        return;
    }

    for (const auto &record : issuedBooks)
    {
        if (record.getMemberID() == member->getMemberID() &&
            record.getBookID() == book->getID() &&
            !record.isReturned())
        {
            cout << "This book is already issued to this member!\n";
            return;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Get issue date
    string date;
    bool validDate = false;
    cout << "Enter Issue Date (DD MM YYYY): ";
    do
    {
        getline(cin, date);
        if (checkDate(date))
            validDate = true;
        else
            cout << "Invalid Date! Try Again: ";
    } while (!validDate);

    // Update book copies and status
    book->setCopies(book->getCopies() - 1);

    // Update member borrow count
    member->setNumberOfBooksBorrowed(member->getNumberOfBooksBorrowed() + 1);

    // Create issue record
    IssueRecords issue(member->getMemberID(), book->getID(), date, false);
    issuedBooks.push_back(issue);

    // Save all changes
    booksMgr.saveBooks();
    membersMgr.saveMembers();
    saveIssuedBooks();

    cout << "Transaction Successful! Book Issued to Member " << member->getName() << endl;
}
