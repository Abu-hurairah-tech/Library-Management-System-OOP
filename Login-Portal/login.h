#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <iostream>

struct User
{
    std::string username;
    std::string password;
};

class AuthManager
{
private:
    std::vector<User> users;
    const std::string filename = "Data/login.csv";
    void loadUsers();
    std::string getMaskedPassword(); // The masking logic

public:
    AuthManager();
    bool login();
    void registerUser();
    void saveUsers();
};

#endif