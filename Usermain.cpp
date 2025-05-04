#include "User.h"
#include "Admin.h"   // Include the Admin class
#include "Officer.h"  // Include the Officer class
#include "Soldier.h"  // Include the Soldier class
#include "Message.h"  // Include the Message class
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // Pointer to base class
    User* user = nullptr;

    // Register a user using username, password, and role
    string entered_username, entered_password, entered_role;
    cout << "Please Enter username: ";
    cin >> entered_username;
    cout << "Please Enter password: ";
    cin >> entered_password;
    cout << "Please Enter your role (Admin/Officer/Soldier): ";
    cin >> entered_role;

    // Create correct object based on role
    if (entered_role == "Admin") {
        user = new Admin();
    } else if (entered_role == "Officer") {
        user = new Officer();
    } else if (entered_role == "Soldier") {
        user = new Soldier();
    } else {
        cout << "Invalid role! Exiting..." << endl;
        return 1;
    }

    // Calling the registerUser function
    user->registerUser(entered_username, entered_password, entered_role);

    // If user wants to login 
    string login_username, login_password;
    cout << "Please Enter username to login: ";
    cin >> login_username;
    cout << "Please Enter password to login: ";
    cin >> login_password;

    if (user->loginUser(login_username, login_password)) {
        cout << "Access Granted! Role: " << user->getRole() << endl;
      
        // Create a Message object to handle messages
        Message msg;
        
        // Display message sending option
        string send_message_choice;
        cout << "Do you want to send a message? (yes/no): ";
        cin >> send_message_choice;

        if (send_message_choice == "yes" || send_message_choice == "y") {
            string receiver;
            cout << "Enter the username of the recipient: ";
            cin >> receiver;

            string message_content;
            cout << "Enter the message: ";
            cin.ignore();  // To clear the buffer
            getline(cin, message_content);  // Get the message content

            msg.sendMessage(login_username, receiver, message_content);  // Call sendMessage function
        }

        // Depending on the role, allow the user to view messages
        cout << "\nViewing Messages for " << user->getRole() << ":\n";
        msg.receiveMessage(login_username);  // Receive messages

        // User-specific tasks
        user->performTask();
        user->viewReport(); // This should be implemented in derived classes
    }

    delete user;  // Free memory

    return 0;
}
