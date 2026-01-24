#include "DateUtils.h"
#include <cctype>
#include <string>
#include <limits>
#include <iostream>
using namespace std;

bool checkDate(const std::string &date)
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

int dateToDays(const std::string &date)
{
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    static int daysInMonth[] =
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int totalDays = year * 365 + day;

    for (int i = 0; i < month - 1; i++)
        totalDays += daysInMonth[i];

    return totalDays;
}

int getValidInteger()
{
    int input;
    while (!(cin >> input))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number: ";
    }

    return input;
}