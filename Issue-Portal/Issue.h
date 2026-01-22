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
#include <fstream>
#include <algorithm>

class IssueRecords
{
private:
    int memberID_;
    int bookID_;
    string dateOfIssue_;
    bool returnStatus_;

public:
    IssueRecords(int mid = 0, int bid = 0, const string &doi = "", bool returned = false);
    int getMemberID() const;
    int getBookID() const;
    string getDateOfIssue() const;
    bool isReturned() const;

    void setReturned(bool r);
    bool setDateOfIssue(const string &d);
    string toCSV() const;
    ~IssueRecords();
};
#endif