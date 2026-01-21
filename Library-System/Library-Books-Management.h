#ifndef LIBRARY_BOOKS_H
#define LIBRARY_BOOKS_H
#include "Books.h"
#include "members.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
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
    Book *searchByTitle();
    Book *searchByAuthor();
    Book *searchByISBN();
    void removeBook();
    void updateBook();
    int getTotalBooks();
    int getAvailableBooks();
};

#endif