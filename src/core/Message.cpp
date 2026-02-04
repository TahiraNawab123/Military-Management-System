#include "Message.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor
Message::Message(const string& sender, const string& receiver, const string& content) 
    : sender(sender), receiver(receiver), content(content) {}

// Destructor
Message::~Message() {}

// sendMessage function - store the message to a file
void Message::sendMessage(const string& sender, const string& receiver, const string& content) {
    this->sender = sender;
    this->receiver = receiver;
    this->content = content;

    // Save the message to a file
    ofstream messageFile("messages.txt", ios::app);  // Open the file in append mode
    if (messageFile.is_open()) {
        messageFile << sender << "," << receiver << "," << content << "\n";  // Save message
        messageFile.close();
        cout << "Message sent from " << sender << " to " << receiver << ": " << content << endl;
    } else {
        cout << "Error: Unable to send message." << endl;
    }
}

// receiveMessage function - display messages for the user
void Message::receiveMessage(const string& username) {
    ifstream messageFile("messages.txt");
    string line;
    bool foundMessage = false;

    if (messageFile.is_open()) {
        while (getline(messageFile, line)) {
            size_t firstComma = line.find(',');
            size_t secondComma = line.find(',', firstComma + 1);

            // Extract sender, receiver, and content using the commas
            string sender = line.substr(0, firstComma);
            string receiver = line.substr(firstComma + 1, secondComma - firstComma - 1);
            string content = line.substr(secondComma + 1);

            // Check if the current user is the receiver
            if (receiver == username) {
                cout << "Message from " << sender << ": " << content << endl;
                foundMessage = true;
            }
        }
        messageFile.close();
    } else {
        cout << "Error: Unable to read messages." << endl;
    }

    if (!foundMessage) {
        cout << "No new messages for " << username << "." << endl;
    }
}

// editMessage function - allow sender to edit their own message
void Message::editMessage(const string& username) {
    ifstream messageFile("messages.txt");
    ofstream tempFile("temp_messages.txt");  // Temporary file to store updated messages
    string line;
    bool messageFound = false;

    if (messageFile.is_open() && tempFile.is_open()) {
        while (getline(messageFile, line)) {
            size_t firstComma = line.find(',');
            size_t secondComma = line.find(',', firstComma + 1);

            // Extract sender, receiver, and content using the commas
            string sender = line.substr(0, firstComma);
            string receiver = line.substr(firstComma + 1, secondComma - firstComma - 1);
            string content = line.substr(secondComma + 1);

            // If the current message is from the sender, allow editing
            if (sender == username) {
                cout << "Current message: " << content << endl;
                cout << "Enter new message content: ";
                getline(cin, content);
                messageFound = true;
            }

            // Write the message back to the temp file (whether edited or not)
            tempFile << sender << "," << receiver << "," << content << "\n";
        }
        messageFile.close();
        tempFile.close();

        // If a message was edited, rename the temp file to the original file
        if (messageFound) {
            remove("messages.txt");  // Delete the original messages file
            rename("temp_messages.txt", "messages.txt");  // Rename the temp file
            cout << "Message updated successfully!" << endl;
        } else {
            cout << "You are not allowed to edit this message." << endl;
        }
    } else {
        cout << "Error: Unable to read or write to the message files." << endl;
    }
}
