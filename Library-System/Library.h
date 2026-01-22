#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H
#include "Books.h"
#include "members.h"
#include "Library-Books-Management.h"
#include "Library-Member-Management.h"
#include "Issue.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>

class Library
{
private:
    BooksManager booksMgr;
    MemberManager membersMgr;
    vector<IssueRecords> issuedBooks;

public:
    void issueBook();
    void returnBooks();
    void saveIssuedBooks();
    void loadIssuedBooks();
    Library();
    ~Library();
};

#endif