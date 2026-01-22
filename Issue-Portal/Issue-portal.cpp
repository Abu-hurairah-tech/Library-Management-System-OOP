#include "Books.h"
#include "members.h"
#include "Library.h"
#include "Issue.h"
#include "Library-Books-Management.h"
#include "Library-Member-Management.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;

static bool checkDate(const string &date)
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

IssueRecords::IssueRecords(int mid, int bid, const string &doi, bool returned) : memberID_(mid), bookID_(bid), dateOfIssue_(doi), returnStatus_(returned) {}
IssueRecords ::~IssueRecords() {}
int IssueRecords::getMemberID() const { return memberID_; }
int IssueRecords::getBookID() const { return bookID_; }
string IssueRecords::getDateOfIssue() const { return dateOfIssue_; }
bool IssueRecords::setDateOfIssue(const string& d)
{
    if (checkDate(d))
    {
        dateOfIssue_ = d;
        return true;
    }
    else
        return false;
}
bool IssueRecords::isReturned() const { return returnStatus_; }

void IssueRecords::setReturned(bool r) { returnStatus_ = r; }
string IssueRecords::toCSV() const { return to_string(memberID_) + "," + to_string(bookID_) + "," + dateOfIssue_ + "," + (returnStatus_ ? "Yes" : "No"); }
void IssueRecords::writeToFile(ofstream &outFile) const
{
    if (outFile.is_open())
        outFile << toCSV() << endl;
}