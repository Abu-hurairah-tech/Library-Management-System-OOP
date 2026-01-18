#include "Books.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;

Book::Book(int i, string t, string a, int isbn) : id_(i), title_(t), author_(a), ISBN_(isbn) {}
Book::~Book() {}
int Book::getID() const { return id_; }
string Book::getTitle() const { return title_; }
string Book::getAuthor() const { return author_; }
int Book::getISBN() const { return ISBN_; }
void Book::setID(int i) { id_ = i; }
void Book::setTitle(string t) { title_ = t; }
void Book::setAuthor(string a) { author_ = a; }
void Book::setISBN(int isbn) { ISBN_ = isbn; }
bool Book::operator==(int id) { return this->id_ == id; }
bool Book::operator==(int isbn) { return this->id_ == isbn; }
bool Book::operator==(string t) { return this->title_ == t; }
bool Book::operator==(string a) { return this->author_ == a; }

string Book::toCSV()
{
    return to_string(id_) + "," + title_ + "," + author_ + "," + to_string(ISBN_);
}

void Book::writeToFile(ofstream &outFile)
{
    if (outFile.is_open())
        outFile << toCSV() << endl;
}

void Book::displaydetails() const
{
    cout << "==================== Book Details ====================" << endl;

    cout << left
         << setw(5) << "ID" << "| "
         << setw(20) << "Title" << "| "
         << setw(20) << "Author(s)" << "| "
         << setw(15) << "ISBN" << endl;

    cout << string(65, '-') << endl;

    cout << left
         << setw(5) << id_ << "| "
         << setw(20) << title_ << "| "
         << setw(20) << author_ << "| "
         << setw(15) << ISBN_ << endl;
}
