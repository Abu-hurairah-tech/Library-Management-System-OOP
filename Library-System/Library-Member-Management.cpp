#include "Books.h"
#include "members.h"
#include "Library-Member-Management.h"
#include "DateUtils.h"
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
using namespace std;

bool checkEmail(const string &e)
{
    size_t at = e.find('@');
    return at != string::npos && e.find('.', at) != string::npos;
}

bool checkPhone(const string &p)
{
    if (p.length() != 12)
        return false;

    for (char ch : p)
    {
        if (!isdigit(ch))
            return false;
    }

    return true;
}

MemberManager::MemberManager() { loadMembers(); }

MemberManager::~MemberManager()
{
    saveMembers();
    for (auto m : members)
        delete m;
    members.clear();
}

void MemberManager::loadMembers()
{
    ifstream inFile("Data/Members.csv");
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
        getline(ss, booksBorrowedStr, ',');
        getline(ss, extra);

        int memberId = memberIdStr.empty() ? 0 : stoi(memberIdStr);
        int borrowed = booksBorrowedStr.empty() ? 0 : stoi(booksBorrowedStr);

        if (fieldtypeStr == "Student")
        {
            members.push_back(new Student(nameStr, emailStr, phoneStr, memberId, borrowed, membershipDateStr, extra));
        }
        else if (fieldtypeStr == "Faculty")
        {
            members.push_back(new Faculty(nameStr, emailStr, phoneStr, memberId, borrowed, membershipDateStr, extra));
        }
    }
    inFile.close();
}

void MemberManager::saveMembers()
{
    ofstream outputFile("Data/Members.csv");
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
    bool idExists;
    cout << "1. Student\n2. Faculty\n";
    cout << "Enter Choice: ";
    do
    {
        cin >> choice;
        if (cin.fail() || (choice != 1 && choice != 2))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Choice! Try Again: ";
        }
    } while (choice != 1 && choice != 2);

    int id;
    do
    {
        cout << "Enter Member ID: ";
        idExists = false;
        do
        {
            id = getValidInteger();
        } while (cin.fail() || id <= 0);

        // Clear buffer ONCE before getline
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (auto m : members)
        {
            if (m->getMemberID() == id)
            {
                cout << "Member with this ID already exists!\n";
                idExists = true;
                break;
            }
        }
    } while (idExists);
    string name, email, phone, date, extra;

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Email: ";
    while (!checkEmail(email))
    {
        getline(cin, email);
        if (!checkEmail(email))
            cout << "Invalid Email! Try Again: ";
    }

    cout << "Enter Phone: ";
    while (!checkPhone(phone))
    {
        getline(cin, phone);
        if (!checkPhone(phone))
            cout << "Invalid Phone! Try Again: ";
    }

    cout << "Enter Membership Date (DD MM YYYY): ";
    while (!checkDate(date))
    {
        getline(cin, date);
        if (!checkDate(date))
            cout << "Invalid Date! Try Again: ";
    }

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
        return nullptr;
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

void MemberManager::updateMember()
{
    LibraryMember *m = searchMember();
    if (m == nullptr)
        return;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n-- Update Member --\n";

    // ===== Name =====
    string name;
    cout << "Current Name: " << m->getName() << endl;
    cout << "Enter Name (leave empty to keep same): ";
    getline(cin, name);

    if (!name.empty())
        m->setName(name);

    // ===== Email =====
    string email;
    cout << "Current Email: " << m->getEmail() << endl;

    do
    {
        cout << "Enter Email (leave empty to keep same): ";
        getline(cin, email);

        if (email.empty())
            break;

        if (!checkEmail(email))
            cout << "Invalid Email! Try Again.\n";
        else
            m->setEmail(email);

    } while (!email.empty() && !checkEmail(email));

    // ===== Phone =====
    string phone;
    cout << "Current Phone: " << m->getPhone() << endl;

    do
    {
        cout << "Enter Phone (leave empty to keep same): ";
        getline(cin, phone);

        if (phone.empty())
            break;

        if (!checkPhone(phone))
            cout << "Invalid Phone! Try Again.\n";
        else
            m->setPhone(phone);

    } while (!phone.empty() && !checkPhone(phone));

    // ===== Membership Date =====
    string date;
    cout << "Current Membership Date: " << m->getMembershipDate() << endl;

    do
    {
        cout << "Enter Membership Date (DD MM YYYY) (leave empty to keep same): ";
        getline(cin, date);

        if (date.empty())
            break;

        if (!checkDate(date))
            cout << "Invalid Date! Try Again.\n";
        else
            m->setMembershipDate(date);

    } while (!date.empty() && !checkDate(date));

    // ===== Books Borrowed =====
    int borrowed;

    cout << "Current Books Borrowed: " << m->getNumberOfBooksBorrowed() << endl;

    while (true)
    {
        cout << "Enter Books Borrowed (-1 to keep same): ";
        cin >> borrowed;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter a number.\n";
            continue;
        }

        if (borrowed == -1)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break; // keep same
        }

        if (borrowed < 0)
        {
            cout << "Books borrowed cannot be negative.\n";
            continue;
        }

        if (borrowed > m->getBorrowLimit())
        {
            cout << "Error: This member can borrow at most "
                 << m->getBorrowLimit() << " books.\n";
            continue;
        }

        m->setNumberOfBooksBorrowed(borrowed);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    // ===== Student / Faculty Specific =====
    string input;
    cout << "Current Degree/Department Info: " << m->getExtra() << endl;
    cout << "Enter New Value (leave empty to keep same): ";
    getline(cin, input);

    if (!input.empty())
        m->setExtra(input);

    saveMembers();
    cout << "Member updated successfully.\n";
}

void MemberManager::displayMembers()
{
    if (members.empty())
    {
        cout << "No members registered.\n";
        return;
    }

    cout << string(58, '=');
    cout << "Member Details";
    cout << string(58, '=') << endl;
    
    cout
        << left
        << setw(10) << "Member ID" << "| "
        << setw(20) << "Name" << "| "
        << setw(20) << "Email" << "| "
        << setw(20) << "Phone" << "| "
        << setw(22) << "No. Of Books Borrowed" << "| "
        << setw(20) << "Degree/Department" << "| "
        << endl;

    cout << string(123, '-') << endl;

    for (const auto &m : members)
    {
        if (!m)
            continue;

        cout << left
             << setw(10) << m->getMemberID() << "| "
             << setw(20) << m->getName() << "| "
             << setw(20) << m->getEmail() << "| "
             << setw(20) << m->getPhone() << "| "
             << setw(22) << m->getNumberOfBooksBorrowed() << "| "
             << setw(20) << m->getExtra() << "| "
             << endl;
    }
}
