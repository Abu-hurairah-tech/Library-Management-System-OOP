#include "Books.h"
#include "members.h"
#include "Library.h"
#include "Issue.h"
#include "Library-Books-Management.h"
#include "Library-Member-Management.h"
#include "DateUtils.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;

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