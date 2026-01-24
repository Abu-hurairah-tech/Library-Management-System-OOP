#ifndef ISSUE_H
#define ISSUE_H
#include "Books.h"
#include "members.h"
#include "Library.h"
#include "Library-Books-Management.h"
#include "Library-Member-Management.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <fstream>
#include <algorithm>

class IssueRecords
{
private:
    int memberID_;
    int bookID_;
    string dateOfIssue_;
    string dateOfReturn_;
    bool returnStatus_;
    double fine_;

public:
    IssueRecords();
    IssueRecords(int mid = 0, int bid = 0, const string &doi = "", const string &dor = "", bool returned = false, double f = 0.0);
    int getMemberID() const;
    int getBookID() const;
    string getDateOfIssue() const;
    string getDateOfReturn() const;
    double getFine() const;
    bool isReturned() const;

    void setReturned(bool r);
    bool setDateOfReturn(const string &d);
    void setFine(double f);
    int getDaysOverdue(const string &returnDate) const;
    bool isOverdue(const string &returnDate) const;
    string calculateDueDate(int allowedDays) const;
    string toCSV() const;
    void writeToFile(ofstream &outFile) const;
    ~IssueRecords();
};
#endif