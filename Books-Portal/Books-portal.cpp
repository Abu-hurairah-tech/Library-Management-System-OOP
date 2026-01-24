#include "Books.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;

Book::Book(int i, const string &t, const string &a, const string &isbn) : id_(i), title_(t), author_(a), ISBN_(isbn), status_("Available"), copies_(1) {}
Book::~Book() {}
int Book::getID() const { return id_; }
string Book::getTitle() const { return title_; }
string Book::getAuthor() const { return author_; }
string Book::getISBN() const { return ISBN_; }
void Book::setID(int i) { id_ = i; }
void Book::setTitle(const string &t) { title_ = t; }
void Book::setAuthor(const string &a) { author_ = a; }
void Book::setISBN(const string& isbn) { ISBN_ = isbn; }
string Book::getStatus() const { return status_; }
void Book::setStatus(const string &status) { status_ = status; }
bool Book::operator==(int id) const { return this->id_ == id; }

string Book::toCSV() const
{
    return to_string(id_) + "," + title_ + "," + author_ + "," + ISBN_ + "," + status_ + "," + to_string(copies_);
}

void Book::writeToFile(ofstream &outFile) const
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
         << setw(15) << "ISBN" << "| "
         << setw(20) << "Status" << "| "
         << setw(15) << "Copies" << "|\n";

    cout << string(90, '-') << endl;

    cout << left
         << setw(5) << id_ << "| "
         << setw(20) << title_ << "| "
         << setw(20) << author_ << "| "
         << setw(15) << ISBN_ << "| "
         << setw(20) << status_ << "| "
         << setw(15) << copies_ << endl;
}

int Book::getCopies() const { return copies_; }
void Book::setCopies(int c)
{
    if (c >= 0)
        copies_ = c;
}
void Book::incrementCopies() { copies_++; }
void Book::decrementCopies()
{
    if (copies_ > 0)
        copies_--;

    if (copies_ == 0)
        status_ = "Unavailable";
}

std::ostream &operator<<(std::ostream &os, const Book &b)
{
    os << "ID: " << b.id_
       << "\nTitle: " << b.title_
       << "\nAuthor: " << b.author_
       << "\nISBN: " << b.ISBN_
       << "\nCopies: " << b.copies_;
    return os;
}