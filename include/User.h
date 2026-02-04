#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include "Message.h" 

using namespace std;

class User {
private:
          string username;
          string password;
          string role;  // This will store the role of the user (Admin, Officer, Soldier)
 
public:
    // Default constructor
    User() {}
    // Message association functions
    void sendUserMessage();
    void viewUserMessages();
    void editUserMessage();

    // Register a user (stores the username, password, and role)
    void registerUser(const string& entered_username, const string& entered_password, const string& entered_role) {
        username = entered_username;
        password = entered_password;
        role = entered_role; // Sets the role during registration
        cout << "User registered successfully as " << role << "!" << endl;
    }

    // User Login (compare entered username and password with the stored ones)
    bool loginUser(const string& login_username, const string& login_password) {
        if (login_username == username && login_password == password) {
            cout << "Login successful!" << std::endl;
            return true;
        } else {
            cout << "Invalid username or password." << endl;
            return false;
        }
    }

    // Getter function to retrieve the role
    string getRole() {
        return role;
    }

     // Virtual functions to be overridden
     virtual void performTask() = 0;  // pure virtual function
     virtual void viewReport() = 0;
     virtual ~User() {}  // Ensures proper cleanup of derived classes

};

// Authenticate a user against the persistent users.txt store.
// Returns true if username/password are valid and fills outRole with the user's role.
bool authenticateUser(const string& username, const string& password, string& outRole);

#endif
