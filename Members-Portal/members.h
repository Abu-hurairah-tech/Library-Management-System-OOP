#ifndef MEMBERS_H
#define MEMBERS_H
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;
class Person
{
protected:
    string name_;
    string email_;
    int phone_;

public:
    Person();
    Person(const string &n = "", const string &e = "", int p = 0);
    Person (const Person& rhs);
    Person& operator=(const Person& rhs);
    string getName() const;
    string getEmail() const;
    int getPhone() const;
    void setName(string n);
    void setEmail(string e);
    void setPhone(int p);
    virtual ~Person();
    virtual void displayDetails() const = 0;
};

class LibraryMember : public Person
{
protected:
    int memberID_;
    int booksBorrowed_;
    string membershipDate_;

public:
    LibraryMember(const string &n = "", const string &e = "", int p = 0, int i = 0, int b = 0, const string &md = "");
    virtual ~LibraryMember();
    LibraryMember(const LibraryMember &rhs);
    LibraryMember &operator=(const LibraryMember &rhs);
    int getMemberID() const;
    int getNumberOfBooksBorrowed() const;
    virtual int getBorrowLimit() const = 0;
    string getMembershipDate() const;
    void setMemberID(int i);
    void setNumberOfBooksBorrowed(int b);
    void setMembershipDate(const string &d);
    virtual double calculateFine(int days) const;
    virtual int getAllowedDays() const = 0;
    bool operator==(int i) const;
    virtual string toCSV() const;
    void writeToFile(ofstream &outFile) const;
    virtual void displayDetails() const override;
};

class Student : public LibraryMember
{
private:
    string degree_;

public:
    Student(const string &n = "", const string &e = "", int p = 0, int i = 0, int b = 0, const string &md = "", const string &d = "");
    ~Student() override;
    Student(const Student &rhs);
    Student &operator=(const Student &rhs);
    double calculateFine(int days) const override;
    int getAllowedDays() const override;
    int getBorrowLimit() const override;
    void displayDetails() const override;
    bool hasDegree(const string &d) const;
    string toCSV() const override;
};

class Faculty : public LibraryMember
{
private:
    string department_;

public:
    Faculty(const string &n = "", const string &e = "", int p = 0, int i = 0, int b = 0, const string &md = "", const string &dept = "");
    ~Faculty() override;
    Faculty(const Faculty &rhs);
    Faculty &operator=(const Faculty &rhs);
    double calculateFine(int days) const override;
    int getAllowedDays() const override;
    bool isFromDept(const string &dept) const;
    void displayDetails() const override;
    string toCSV() const override;
    int getBorrowLimit() const override;
};
#endif