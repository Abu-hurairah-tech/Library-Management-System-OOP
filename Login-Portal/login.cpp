#include <conio.h> // Required for _getch()
#include <string>
#include <sstream>
#include "login.h"

std::string AuthManager::getMaskedPassword()
{
    std::string password = "";
    char ch;
    while ((ch = _getch()) != '\r')
    { // '\r' is the Enter key
        if (ch == '\b')
        { // Handle Backspace
            if (!password.empty())
            {
                password.pop_back();
                std::cout << "\b \b"; // Erase the * from screen
            }
        }
        else
        {
            password += ch;
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}

void AuthManager::registerUser()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string user, pass;
    std::cout << "Enter new username: ";
    getline(std::cin, user);

    // Check if username exists
    for (const auto &u : users)
    {
        if (u.username == user)
        {
            std::cout << "Username already taken!\n";
            return;
        }
    }

    std::cout << "Enter new password: ";
    pass = getMaskedPassword();

    users.push_back({user, pass});
    saveUsers();
    std::cout << "Registration successful!\n";
}

bool AuthManager::login()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string user, pass;
    std::cout << "Username: ";
    getline(std::cin, user);
    std::cout << "Password: ";
    pass = getMaskedPassword();

    for (const auto &u : users)
    {
        if (u.username == user && u.password == pass)
        {
            return true;
        }
    }
    return false;
}

void AuthManager::loadUsers()
{
    users.clear();
    std::ifstream inFile(filename);
    if (!inFile)
        return;

    std::string line;
    getline(inFile, line); // skip header

    while (getline(inFile, line))
    {
        std::stringstream ss(line);
        std::string user, pass;

        getline(ss, user, ',');
        getline(ss, pass);

        users.push_back({user, pass});
    }
}

void AuthManager::saveUsers()
{
    std::ofstream outFile(filename);
    outFile << "Username,Password\n"; // Proper Header
    for (const auto &u : users)
    {
        outFile << u.username << "," << u.password << "\n";
    }
    outFile.close();
}

AuthManager::AuthManager()
{
    loadUsers();
}
