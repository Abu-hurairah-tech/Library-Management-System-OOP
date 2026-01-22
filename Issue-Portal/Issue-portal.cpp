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

static int dateToDays(const string &date)
{
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    static int daysInMonth[] =
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int totalDays = year * 365 + day;

    for (int i = 0; i < month - 1; i++)
        totalDays += daysInMonth[i];

    return totalDays;
}

int IssueRecords::getDaysOverdue(const string &dueDate) const
{
    if (!returnStatus_)
        return 0;

    int overdue =
        dateToDays(dateOfReturn_) - dateToDays(dueDate);

    return overdue > 0 ? overdue : 0;
}

bool IssueRecords::isOverdue(const string &dueDate) const
{
    if (!returnStatus_)
        return false;

    return dateToDays(dateOfReturn_) > dateToDays(dueDate);
}

string IssueRecords::calculateDueDate(int allowedDays) const
{
    int issueDays = dateToDays(dateOfIssue_);
    int dueDays = issueDays + allowedDays;

    int year = dueDays / 365;
    int remaining = dueDays % 365;

    static int daysInMonth[] =
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int month = 0;
    while (remaining > daysInMonth[month])
    {
        remaining -= daysInMonth[month];
        month++;
    }

    int day = remaining;

    return (day < 10 ? "0" : "") + to_string(day) + " " +
           (month + 1 < 10 ? "0" : "") + to_string(month + 1) + " " +
           to_string(year);
}

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

IssueRecords::IssueRecords(): memberID_(0), bookID_(0),returnStatus_(false), fine_(0.0) {}
IssueRecords::IssueRecords(int mid, int bid, const string &doi, const string &dor, bool returned, double f) : memberID_(mid), bookID_(bid), dateOfIssue_(doi), dateOfReturn_(dor), returnStatus_(returned), fine_(f) {}
IssueRecords ::~IssueRecords() {}
int IssueRecords::getMemberID() const { return memberID_; }
int IssueRecords::getBookID() const { return bookID_; }
string IssueRecords::getDateOfIssue() const { return dateOfIssue_; }
double IssueRecords::getFine() { return fine_; }
string IssueRecords::getDateOfReturn() const { return dateOfReturn_; }
bool IssueRecords::isReturned() const { return returnStatus_; }

bool IssueRecords::setDateOfReturn(const string &d)
{
    if (checkDate(d))
    {
        dateOfReturn_ = d;
        return true;
    }
    else
        return false;
}

void IssueRecords::setFine(double f)
{
    fine_ = f < 0 ? 0 : f;
}
void IssueRecords::setReturned(bool r) { returnStatus_ = r; }
string IssueRecords::toCSV() const { return to_string(memberID_) + "," + to_string(bookID_) + "," + dateOfIssue_ + "," + dateOfReturn_ + "," + (returnStatus_ ? "Yes" : "No") + "," + to_string(fine_); }
void IssueRecords::writeToFile(ofstream &outFile) const
{
    if (outFile.is_open())
        outFile << toCSV() << endl;
}