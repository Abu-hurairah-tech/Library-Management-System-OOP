#include "members.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <limits>
#include <algorithm>
using namespace std;
static constexpr double STUDENT_FINE_RATE = 100.0;
static constexpr double FACULTY_FINE_RATE = 50.0;

Person::Person() : name_(""), email_(""), phone_(0) {}
Person::Person(const string &n, const string &e, const string &p) : name_(n), email_(e), phone_(p) {}
string Person::getName() const { return name_; }
string Person::getEmail() const { return email_; }
string Person::getPhone() const { return phone_; }
void Person::setName(string n) { name_ = n; }
void Person::setEmail(string e) { email_ = e; }
void Person::setPhone(const string &p) { phone_ = p; }
Person::Person(const Person &rhs)
{
    this->name_ = rhs.name_;
    this->email_ = rhs.email_;
    this->phone_ = rhs.phone_;
}
Person &Person::operator=(const Person &rhs)
{
    if (this != &rhs)
    {
        this->name_ = rhs.name_;
        this->email_ = rhs.email_;
        this->phone_ = rhs.phone_;
    }
    return *this;
}
Person::~Person() {}

LibraryMember::LibraryMember(const string &n, const string &e, const string &p, int i, int b, const string &md) : Person(n, e, p), memberID_(i > 0 ? i : 0), booksBorrowed_(b >= 0 ? b : 0), membershipDate_(md) {}
LibraryMember::~LibraryMember() {}
LibraryMember::LibraryMember(const LibraryMember &rhs) : Person(rhs)
{
    this->memberID_ = rhs.memberID_;
    this->booksBorrowed_ = rhs.booksBorrowed_;
    this->membershipDate_ = rhs.membershipDate_;
}
LibraryMember &LibraryMember::operator=(const LibraryMember &rhs)
{
    if (this != &rhs)
    {
        Person::operator=(rhs);
        this->memberID_ = rhs.memberID_;
        this->booksBorrowed_ = rhs.booksBorrowed_;
        this->membershipDate_ = rhs.membershipDate_;
    }
    return *this;
}
int LibraryMember::getMemberID() const { return memberID_; }
int LibraryMember::getNumberOfBooksBorrowed() const { return booksBorrowed_; }
string LibraryMember::getMembershipDate() const { return membershipDate_; }
void LibraryMember::setMemberID(int i)
{
    if (i > 0)
        memberID_ = i;
}
void LibraryMember::setNumberOfBooksBorrowed(int b)
{
    if (b >= 0)
        booksBorrowed_ = b;
}
void LibraryMember::setMembershipDate(const string &md)
{
    if (!md.empty())
        membershipDate_ = md;
}
double LibraryMember::calculateFine(int days) const { return days * 100.0; }
bool LibraryMember::operator==(int i) const { return memberID_ == i; }

string LibraryMember::toCSV() const { return to_string(memberID_) + "," + name_ + "," + email_ + "," + phone_ + "," + membershipDate_ + "," + to_string(booksBorrowed_); }

void LibraryMember::writeToFile(ofstream &outFile) const
{
    if (outFile.is_open())
        outFile << toCSV() << endl;
}


Student::Student(const string &n, const string &e, const string &p, int i, int b, const string &md, const string &d) : LibraryMember(n, e, p, i, b, md), degree_(d) {}
Student::~Student() {}
Student::Student(const Student &rhs) : LibraryMember(rhs), degree_(rhs.degree_) {}
Student &Student::operator=(const Student &rhs)
{
    if (this != &rhs)
    {
        Person::operator=(rhs);
        LibraryMember::operator=(rhs);
        this->degree_ = rhs.degree_;
    }
    return *this;
}
double Student::calculateFine(int days) const { return days * STUDENT_FINE_RATE; }
int Student::getAllowedDays() const { return 14; }
string Student::getExtra() const { return degree_; }
void Student::setExtra(const string &ex) { degree_ = ex; }
bool Student::hasDegree(const string &d) const { return degree_ == d; }
int Student::getBorrowLimit() const { return 3; }
string Student::toCSV() const { return "Student," + LibraryMember::toCSV() + "," + degree_; }
void Student::displayDetails() const
{
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

        cout << left
             << setw(10) << memberID_ << "| "
             << setw(20) << name_ << "| "
             << setw(20) << email_ << "| "
             << setw(20) << phone_ << "| "
             << setw(22) << booksBorrowed_ << "| "
             << setw(20) << degree_ << "| "
             << endl;
    
}

Faculty::Faculty(const string &n, const string &e, const string &p, int i, int b, const string &md, const string &dept) : LibraryMember(n, e, p, i, b, md), department_(dept) {}
Faculty::~Faculty() {}
Faculty::Faculty(const Faculty &rhs) : LibraryMember(rhs), department_(rhs.department_) {}
Faculty &Faculty::operator=(const Faculty &rhs)
{
    if (this != &rhs)
    {
        Person::operator=(rhs);
        LibraryMember::operator=(rhs);
        this->department_ = rhs.department_;
    }
    return *this;
}
double Faculty::calculateFine(int days) const { return days * FACULTY_FINE_RATE; }
int Faculty::getAllowedDays() const { return 30; }
string Faculty::getExtra() const { return department_; }
void Faculty::setExtra(const string &ex) { department_ = ex; }
bool Faculty::isFromDept(const string &dept) const { return department_ == dept; }
int Faculty::getBorrowLimit() const { return 5; }
string Faculty::toCSV() const { return "Faculty," + LibraryMember::toCSV() + "," + department_; }

void Faculty::displayDetails() const
{
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

    cout << left
         << setw(10) << memberID_ << "| "
         << setw(20) << name_ << "| "
         << setw(20) << email_ << "| "
         << setw(20) << phone_ << "| "
         << setw(22) << booksBorrowed_ << "| "
         << setw(20) << department_ << "| "
         << endl;
}