#include "Books.h"
#include "members.h"
#include "Library-Member-Management.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

bool checkEmail(const string &e)
{
    size_t at = e.find('@');
    return at != string::npos && e.find('.', at) != string::npos;
}

bool checkPhone(int p)
{
    return p >= 1000000000;
}

bool checkDate(const string &date)
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

MemberManager::MemberManager()
{
    loadMembers();
}

MemberManager::~MemberManager()
{
    saveMembers();
    for (auto m : members)
        delete m;
    members.clear();
}


void MemberManager::loadMembers()
{
    ifstream inFile("Members.csv");
    if (!inFile)
        return;
    string line;
    getline(inFile, line);
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string fieldtypeStr, memberIdStr, nameStr, emailStr, phoneStr, membershipDateStr, booksBorrowedStr, extra;

        getline(ss, fieldtypeStr, ',');
        getline(ss, memberIdStr, ',');
        getline(ss, nameStr, ',');
        getline(ss, emailStr, ',');
        getline(ss, phoneStr, ',');
        getline(ss, membershipDateStr, ',');
        getline(ss, booksBorrowedStr);

        int phone = phoneStr.empty() ? 0 : stoi(phoneStr);
        int memberId = memberIdStr.empty() ? 0 : stoi(memberIdStr);
        int borrowed = booksBorrowedStr.empty() ? 0 : stoi(booksBorrowedStr);

        getline(ss, extra, ',');
        if (fieldtypeStr == "Student")
        {
            members.push_back(new Student(nameStr, emailStr, phone, memberId, borrowed, membershipDateStr, extra));
        }
        else if (fieldtypeStr == "Faculty")
        {
            members.push_back(new Faculty(nameStr, emailStr, phone, memberId, borrowed, membershipDateStr, extra));
        }
    }
    inFile.close();
}

void MemberManager::saveMembers()
{
    ofstream outputFile("Members.csv");
    if (!outputFile)
        return;

    outputFile << "Type,ID,Name,Email,Phone,MemberShip Date,Books Borrowed,Degree/Dept\n";

    for (LibraryMember *m : members)
    {
        if (m != nullptr)
            m->writeToFile(outputFile);
    }
    outputFile.close();
}

void MemberManager::addMember()
{
    int choice;
    cout << "1. Student\n2. Faculty" << endl;
    do
    {
        cin >> choice;
        cin.ignore();
        if (choice != 1 && choice != 2)
            cout << "Invalid Choice! Try Again\n";

    } while (choice != 1 && choice != 2);

    string name, email, date, extra;
    int id, phone;

    cout << "Enter Member ID: ";
    do
    {
        cin >> id;

        if (cin.fail() || id <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID. Try again: ";
        }

    } while (cin.fail() || id <= 0);

    for (auto m : members)
    {
        if (m->getMemberID() == id)
        {
            cout << "Member with this ID already exists!" << endl;
            return;
        }
    }

    cout << "Enter Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    bool validEmail = false;
    cout << "Enter Email:";
    do
    {
        getline(cin, email);
        if (checkEmail(email))
            validEmail = true;
        else
            cout << "Invalid Email! Try Again." << endl;
    } while (!validEmail);

    bool validPhone = false;
    cout << "Enter Phone: ";
    do
    {
        cin >> phone;
        if (checkPhone(phone))
            validPhone = true;
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Phone! Try Again." << endl;
        }
    } while (!validPhone);
    cin.ignore();

    bool validDate = false;
    cout << "Enter MemberShip Date (DD MM YYYY):";
    do
    {
        getline(cin, date);
        if (checkDate(date))
            validDate = true;
        else
            cout << "Invalid Date! Try Again." << endl;
    } while (!validDate);

    if (choice == 1)
    {
        cout << "Enter Degree: ";
        getline(cin, extra);
        members.push_back(new Student(name, email, phone, id, 0, date, extra));
    }
    else
    {
        cout << "Enter Department: ";
        getline(cin, extra);
        members.push_back(new Faculty(name, email, phone, id, 0, date, extra));
    }
    saveMembers();
}

LibraryMember *MemberManager::searchMember() const
{
    if (members.empty())
    {
        cout << "No members to search.\n";
        return;
    }

    int id;
    cout << "Enter Member ID to search: ";
    cin >> id;
    while (cin.fail() || id <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID. Try again: ";
        cin >> id;
    }

    for (auto m : members)
    {
        if (*m == id)
        {
            return m;
        }
    }
    return nullptr;
}

void MemberManager::removeMember()
{
    int id;
    cout << "Enter Member ID to search: ";
    cin >> id;
    while (cin.fail() || id <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID. Try again: ";
        cin >> id;
    }

    for (auto m = members.begin(); m != members.end(); m++)
    {
        if ((*m)->getMemberID() == id)
        {
            delete *m;
            members.erase(m);
            std::cout << "Member ID " << id << " successfully removed from system.\n";
            saveMembers();
            return;
        }
    }
    cout << "Error: Member ID " << id << " not found.\n";
    return;
}

void MemberManager::displayMembers() const
{
    if (members.empty())
    {
        cout << "No members registered.\n";
        return;
    }

    cout << left << setw(10) << "ID"
         << setw(25) << "Name"
         << setw(10) << "Borrowed" << endl;

    for (const auto &m : members)
    {
        cout << left << setw(10) << m->getMemberID()
             << setw(25) << m->getName()
             << setw(10) << m->getNumberOfBooksBorrowed() << endl;
    }
}
