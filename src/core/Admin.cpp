#include"Admin.h"
#include<iostream>
#include<fstream>
using namespace std;
void Admin::performTask() {
    int choice;
    do {
        cout << "\n===== Admin Panel =====\n";
        cout << "1. Manage Accounts\n";
        cout << "2. Reset Password\n";
        cout << "3. View Report\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            manageAccounts();  // menu inside this already
            break;
        case 2:
            resetPassword();
            break;
        case 3:
            viewReport();
            break;
        case 4:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}


void Admin::viewReport() {
    ifstream file("users.txt");
    if (!file) {
        cout << "No user data found.\n";
        return;
    }

    int total = 0, admins = 0, officers = 0, soldiers = 0;
    string u, p, r;
    while (file >> u >> p >> r) {
        total++;
        if (r == "Admin") admins++;
        else if (r == "Officer") officers++;
        else if (r == "Soldier") soldiers++;
    }

    cout << "\n--- User Report ---\n";
    cout << "Total Users: " << total << "\n";
    cout << "Admins: " << admins << "\n";
    cout << "Officers: " << officers << "\n";
    cout << "Soldiers: " << soldiers << "\n";
}


void Admin::manageAccounts() {
    int choice;
    do {
        cout << "\n=== Manage Accounts ===\n";
        cout << "1. Add User\n2. Delete User\n3. Modify User\n4. Show All Users\n5. Back to Admin Panel\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addUser();
            break;
        case 2:
            deleteUser();
            break;
        case 3:
            modifyUser();
            break;
        case 4:
             showAllUsers();
            break;
        case 5:
            cout << "Returning to Admin Panel...\n";
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 5);
}



void Admin::addUser() {
    string username, password, role;
    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter role (Admin/Officer/Soldier): ";
    cin >> role;

    ofstream file("users.txt", ios::app);
    file << username << " " << password << " " << role << "\n";
    file.close();

    cout << "User added successfully.\n";
}

void Admin::deleteUser() {
    string username;
    cout << "Enter username to delete: ";
    cin >> username;

    ifstream infile("users.txt");
    ofstream outfile("temp.txt");

    string u, p , r;
    bool found = false;
    while (infile >> u >> p >> r) {
        if (u != username) {
            outfile << u << " " << p << " " << r << "\n";
        } else {
            found = true;
        }
    }
    infile.close();
    outfile.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (found) {
        cout << "User deleted successfully.\n";
    } else {
        cout << "User not found.\n";
    }
}

void Admin::modifyUser() {
    string username;
    cout << "Enter username to modify: ";
    cin >> username;

    ifstream infile("users.txt");
    ofstream outfile("temp.txt");

    string u, p , r;
    bool found = false;
    while (infile >> u >> p >> r) {
        if (u == username) {
            found = true;
            string newPass, newRole;
            cout << "Enter new password: ";
            cin >> newPass;
            cout << "Enter new role (Admin/Officer/Soldier): ";
            cin >> newRole;
            outfile << u << " " << newPass << " " << newRole << "\n";
        }else{
            outfile << u << " " << p << " " << r << "\n";
        }
    }
    infile.close();
    outfile.close();
    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (found) {
        cout << "User modified successfully.\n";
    } else {
        cout << "User not found.\n";
    }
}

void Admin::resetPassword() {
    string username;
    cout << "Enter the username for password reset: ";
    cin >> username;

    ifstream inFile("users.txt");
    ofstream tempFile("temp.txt");

    string u, p, r;
    bool found = false;

    while (inFile >> u >> p >> r) {
        if (u == username) {
            found = true;
            string newPass;
            cout << "Enter new password for " << username << ": ";
            cin >> newPass;
            tempFile << u << " " << newPass << " " << r << "\n";
        } else {
            tempFile << u << " " << p << " " << r << "\n";
        }
    }

    inFile.close();
    tempFile.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (found)
        cout << "Password reset successful.\n";
    else
        cout << "User not found.\n";
}

void Admin::showAllUsers() {
    ifstream file("users.txt");
    if (!file) {
        cout << "No user data found.\n";
        return;
    }

    string username, password, role;
    int count = 0;
    cout << "\n--- Current Users ---\n";
    cout << "Username\tPassword\tRole\n";
    cout << "-------------------------------------\n";

    while (file >> username >> password >> role) {
        cout << username << "\t\t" << password << "\t\t" << role << "\t\n";
        count++;
    }

    file.close();

    if (count == 0)
        cout << "No users found.\n";
    else
        cout << "Total Users: " << count << "\n";
}
