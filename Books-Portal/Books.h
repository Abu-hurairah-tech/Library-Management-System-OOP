#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class Book
{
private:
    int id_;
    string title_;
    string author_;
    int ISBN_;
    string status_;
    int copies_;

public:
    Book(int i, const string &t, const string &a, int isbn);
    void displaydetails() const;
    int getID() const;
    string getTitle() const;
    string getAuthor() const;
    int getISBN() const;
    void setID(int i);
    void setTitle(const string &t);
    void setAuthor(const string &a);
    void setISBN(int isbn);
    string getStatus() const;
    void setStatus(const string &status);
    bool operator==(int id) const;
    string toCSV() const;
    void writeToFile(ofstream &outFile) const;
    int getCopies() const;
    void setCopies(int c);
    void incrementCopies();
    void decrementCopies();
    ~Book();
};

#endif