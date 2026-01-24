#ifndef LIBRARY_BOOKS_H
#define LIBRARY_BOOKS_H
#include "Books.h"
#include "members.h"
#include "DateUtils.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <fstream>
#include <algorithm>

class BooksManager
{
private:
    std::vector<Book> books;

public:
    BooksManager();
    ~BooksManager();
    void loadBooks();
    void saveBooks();
    void addBook();
    Book *searchByID();
    void searchByTitle();
    void searchByAuthor();
    Book *searchByISBN();
    void removeBook();
    void updateBook();
    int getTotalBooks();
    int getAvailableBooks();

    void displayBooks();
};

#endif