#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>
#include<fstream>
using namespace std;

class Message {
private:
    string sender;
    string receiver;
    string content;

public:
    Message(const string& sender = "", const string& receiver = "", const string& content = "");
    ~Message();

    void sendMessage(const string& sender, const string& receiver, const string& content);
    void receiveMessage(const string& username);
    void editMessage(const string& username);
};

#endif // MESSAGE_H
