#include "Books.h"
#include "members.h"
#include "Library.h"
#include "Library-Books-Management.h"
#include "Library-Member-Management.h"
#include "DateUtils.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

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
        if (line.empty())
            continue;
        stringstream ss(line);
        string mid, bid, returned, doi, dor, f;

        getline(ss, mid, ',');
        getline(ss, bid, ',');
        getline(ss, doi, ',');
        getline(ss, dor, ',');
        getline(ss, returned, ',');
        getline(ss, f);

        int id = mid.empty() ? 0 : stoi(mid);
        int bookid = bid.empty() ? 0 : stoi(bid);
        bool returnStat = (returned == "Yes" || returned == "yes");

        double fine = f.empty() ? 0 : stod(f);

        if (!mid.empty() && !bid.empty())
        {
            IssueRecords record(id, bookid, doi, dor, returnStat, fine);
            issuedBooks.push_back(record);
        }
    }
    inputFile.close();
}

void Library::saveIssuedBooks()
{
    ofstream outputFile("Issue.csv");
    if (!outputFile)
        return;

    outputFile << "Member ID,Book ID,Date Of Issue,Date Of Return,Return Status,Fine" << endl;
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
    IssueRecords issue(member->getMemberID(), book->getID(), date);
    issuedBooks.push_back(issue);

    // Save all changes
    booksMgr.saveBooks();
    membersMgr.saveMembers();
    saveIssuedBooks();

    cout << "Transaction Successful! Book Issued to Member " << member->getName() << endl;
}

void Library::returnBooks()
{
    LibraryMember *member = membersMgr.searchMember();
    if (!member)
        return;

    Book *book = booksMgr.searchByID();
    if (!book)
        return;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto &record : issuedBooks)
    {
        if (record.getMemberID() == member->getMemberID() && record.getBookID() == book->getID() && !record.isReturned())
        {

            string returnDate;
            cout << "Enter Return Date (DD MM YYYY): ";
            while (true)
            {
                getline(cin, returnDate);
                if (checkDate(returnDate))
                    break;
                cout << "Invalid Date! Try Again: ";
            }

            record.setDateOfReturn(returnDate);
            record.setReturned(true);

            string dueDate = record.calculateDueDate(member->getAllowedDays());
            int overdue = record.getDaysOverdue(dueDate);
            double fine = member->calculateFine(overdue);
            record.setFine(fine);

            book->setCopies(book->getCopies() + 1);
            member->setNumberOfBooksBorrowed(member->getNumberOfBooksBorrowed() - 1);

            booksMgr.saveBooks();
            membersMgr.saveMembers();
            saveIssuedBooks();

            cout << "Book Returned Successfully!" << endl;
            if (fine > 0)
            {
                cout << "Fine: Rs " << fine << endl;
            }
            return;
        }
    }
    cout << "No active issue record found for this book and member! " << endl;
}

void Library::addBook()
{
    booksMgr.addBook();
}

void Library::removeBook()
{
    booksMgr.removeBook();
}

void Library::displayBooks()
{
    booksMgr.displayBooks();
}

void Library::addMember()
{
    membersMgr.addMember();
}

void Library::removeMember()
{
    membersMgr.removeMember();
}

void Library::displayMembers()
{
    membersMgr.displayMembers();
}
