#ifndef LIBRARY_H
#define LIBRARY_H
#include "Books.h"
#include "members.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <limits>
#include <algorithm>

class MemberManager
{
private:
    std::vector<LibraryMember *> members;

public:
    MemberManager();
    ~MemberManager();
    void loadMembers();
    void saveMembers();
    void addMember();
    LibraryMember *searchMember() const;
    void removeMember();
    void updateMember();
    void displayMembers();
};
#endif