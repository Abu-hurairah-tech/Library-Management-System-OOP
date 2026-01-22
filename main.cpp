#include <iostream>
#include "login.h"
#include "Library.h"

using namespace std;

int main()
{
    AuthManager auth;
    Library library;
    library.loadIssuedBooks();

    int choice;

    cout << "=============================\n";
    cout << "  LIBRARY MANAGEMENT SYSTEM  \n";
    cout << "=============================\n";

    // ---------- LOGIN FLOW ----------
    while (true)
    {
        cout << "\n1. Login";
        cout << "\n2. Register";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            if (auth.login())
            {
                cout << "\nLogin Successful!\n";
                break;
            }
            cout << "Invalid credentials!\n";
        }
        else if (choice == 2)
        {
            auth.registerUser();
        }
        else if (choice == 0)
        {
            return 0;
        }
        else
        {
            cout << "Invalid choice!\n";
        }
    }

    // ---------- MAIN LIBRARY MENU ----------
    while (true)
    {
        cout << "\n=========== MAIN MENU ==========\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. View Books\n";
        cout << "4. Add Member\n";
        cout << "5. Remove Member\n";
        cout << "6. View Members\n";
        cout << "7. Issue Book\n";
        cout << "8. Return Book\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            library.addBook();
            break;
        case 2:
            library.removeBook();
            break;
        case 3:
            library.displayBooks();
            break;
        case 4:
            library.addMember();
            break;
        case 5:
            library.removeMember();
            break;
        case 6:
            library.displayMembers();
            break;
        case 7:
            library.issueBook();
            break;
        case 8:
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
