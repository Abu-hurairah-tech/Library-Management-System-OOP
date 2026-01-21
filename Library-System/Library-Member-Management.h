#ifndef LIBRARY_H
#define LIBRARY_H
#include "Books.h"
#include "members.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>

class Library
{
private:
    std::vector<LibraryMember *> members;

public:
    Library();
    ~Library();
    void loadMembers();
    void saveMembers();
    void addMember();
    LibraryMember* searchMember() const;
    void removeMember();
};
#endif