#include <iostream>
#include "Login-Portal/login.h"
#include "Library-System/Library.h"
#include "Utilities\DateUtils.h"
#include <limits>

using namespace std;

void booksMenu(Library &library)
{
    int choice;

    while (true)
    {
        cout << "\n----- BOOKS MANAGEMENT -----\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Search Book\n";
        cout << "4. View Books\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";

        choice = getValidInteger();

        switch (choice)
        {
        case 1:
            library.getBooksManager().addBook();
            break;
        case 2:
            library.getBooksManager().removeBook();
            break;
        case 3:
        {
            cout << "\n--- Search By ---\n";
            cout << "1. ID\n2. Title\n3. Author\n4. ISBN\n0. Cancel\n";
            cout << "Enter choice: ";
            int sChoice = getValidInteger();

            Book *found = nullptr;
            if (sChoice == 1)
                found = library.getBooksManager().searchByID();
            else if (sChoice == 2)
                library.getBooksManager().searchByTitle();
            else if (sChoice == 3)
                library.getBooksManager().searchByAuthor();
            else if (sChoice == 4)
                found = library.getBooksManager().searchByISBN();
            else if (sChoice == 0)
                break;
            else
            {
                cout << "Invalid option!\n";
                break;
            }

            if (found)
                cout << "\nBook Found:\n"
                     << *found << endl;
            break;
        }
        case 4:
            library.getBooksManager().displayBooks();
            break;
        case 0:
            return;
        default:
            cout << "Invalid option!\n";
        }
    }
}

void membersMenu(Library &library)
{
    int choice;
    while (true)
    {
        cout << "\n----- MEMBERS MANAGEMENT -----\n";
        cout << "1. Add Member\n";
        cout << "2. Remove Member\n";
        cout << "3. Update Member\n";
        cout << "4. View Members\n";
        cout << "5. Show Member History\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";

        choice = getValidInteger();

        switch (choice)
        {
        case 1:
            library.getMemberManager().addMember();
            break;
        case 2:
            library.getMemberManager().removeMember();
            break;
        case 3:
            library.getMemberManager().updateMember();
            break;
        case 4:
            library.getMemberManager().displayMembers();
            break;
        case 5:
            library.showMemberHistory();
            break;
        case 0:
            return;
        default:
            cout << "Invalid option!\n";
        }
    }
}

int main()
{
    AuthManager auth;
    Library library;
    library.loadIssuedBooks();

    int loginChoice;

    cout << "=============================\n";
    cout << "  LIBRARY MANAGEMENT SYSTEM  \n";
    cout << "=============================\n";

    // ---------- LOGIN FLOW ----------
    int loginAttempts = 0; // Track failed attempts

    do
    {
        cout << "\n1. Login";
        cout << "\n2. Register";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";

        loginChoice = getValidInteger();

        if (loginChoice == 1)
        {
            if (auth.login())
            {
                cout << "\nLogin Successful!\n";
                break; // Proceed to main system
            }
            else
            {
                loginAttempts++;
                int remaining = 3 - loginAttempts;

                if (loginAttempts >= 3)
                {
                    cout << "\nInvalid credentials! 3 failed attempts. Exiting system..." << endl;
                    return 0; // Terminate the entire program
                }

                cout << "Invalid credentials! You have " << remaining << " attempts left.\n";
            }
        }
        else if (loginChoice == 2)
        {
            auth.registerUser();
        }
        else if (loginChoice == 0)
        {
            return 0;
        }
        else
        {
            cout << "Invalid choice!\n";
        }

    } while (true);

    int choice;

    while (true)
    {
        cout << "\n=========== MAIN MENU ==========\n";
        cout << "1. Books Management\n";
        cout << "2. Members Management\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        // Single point of entry for the input
        choice = getValidInteger();

        switch (choice)
        {
        case 1:
            booksMenu(library);
            break;
        case 2:
            membersMenu(library);
            break;
        case 3:
            library.issueBook();
            break;
        case 4:
            library.returnBooks();
            break;
        case 0:
            cout << "Thank you for using the system.\n";
            return 0;
        default:
            cout << "Invalid option!\n";
        }
    }
}
