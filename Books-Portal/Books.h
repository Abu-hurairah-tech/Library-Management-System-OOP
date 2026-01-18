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
    int copies_;

public:
    Book(int i, string t, string a, int isbn);
    void displaydetails() const;
    int getID() const;
    string getTitle() const;
    string getAuthor() const;
    int getISBN() const;
    void setID(int i);
    void setTitle(string t);
    void setAuthor(string a);
    void setISBN(int isbn);
    bool operator==(int id);
    bool operator==(int isbn);
    bool operator==(string t);
    bool operator==(string a);
    string toCSV();
    void writeToFile(ofstream &outFile);
    ~Book();
};

#endif