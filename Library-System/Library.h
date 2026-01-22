#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H
#include "Books.h"
#include "members.h"
#include "Library-Books-Management.h"
#include "Library-Member-Management.h"
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

public:
    void issueBook();
    void saveIssuedBooks();
    Library();
    ~Library();
};

#endif