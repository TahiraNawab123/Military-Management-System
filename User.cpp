#include "User.h"
#include "Message.h"
#include <iostream>
#include <fstream>

using namespace std;

void User::sendUserMessage() {
    Message msg;
    string sender, receiver, content;

    cout << "Enter your username (sender): ";
    cin >> sender;
    cout << "Enter receiver username: ";
    cin >> receiver;
    cout << "Enter message content: ";
    cin.ignore();
    getline(cin, content);

    msg.sendMessage(sender, receiver, content);
}

void User::viewUserMessages() {
    string username;
    cout << "Enter your username to view messages: ";
    cin >> username;

    Message msg;
    msg.receiveMessage(username);
}

void User::editUserMessage() {
    string username;
    cout << "Enter your username to edit messages: ";
    cin >> username;

    Message msg;
    msg.editMessage(username);
}

bool authenticateUser(const string& username, const string& password, string& outRole) {
    ifstream file("users.txt");
    if (!file) {
        cout << "User database not found. Please ask an Admin to create users first.\n";
        return false;
    }

    string u, p, r;
    while (file >> u >> p >> r) {
        if (u == username && p == password) {
            outRole = r;
            return true;
        }
    }

    cout << "Invalid username or password.\n";
    return false;
}
