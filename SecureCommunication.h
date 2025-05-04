#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"
#include <fstream>
#include <stdexcept>
using json = nlohmann::json;
using namespace std;
           //prototype of all function defined here  and clases are declared here
//--------------------------------------
// -------------------- Encryption Interface --------------------
class Encryption {
public:
    virtual string encrypt(const string &data)=0;
      virtual string decrypt(const string &data)=0;
      virtual void updateKey(const string &data)=0;
     virtual string getAlgorithmName()=0;
    virtual ~Encryption() {}
};

// -------------------- CaesarEncryption --------------------
class CaesarEncryption : public Encryption {
private:
    int shift;

public:
    CaesarEncryption(int shiftValue = 3);
    string encrypt(const string &data) override;
    string decrypt(const string &data) override;
    void updateKey(const string &data) override;
    string getAlgorithmName() override;
};

// -------------------- UserManagement --------------------
class UserManagement {
public:
    static bool verifyUserAccess(const string &username, const string &password);
    static void displayUserInfo(const string &username);
};

// -------------------- SecureMessage --------------------
class SecureMessage {
private:
    Encryption *encryption;
    string messageContent;
    bool encryptionStatus;

public:
    SecureMessage(Encryption *enc, const string &message = "");
    void setMessage(const string &message);
    string getMessage() const;
    string sendMessage();
    string receiveMessage(const string &encryptedMessage);
    bool getEncryptionStatus() const;
    SecureMessage operator+(const SecureMessage &other);
    void displayModuleInfo();
    string retrySendMessage(int retries);

};

// // -------------------- KeyManager --------------------
// class KeyEntry {
// public:
//     string identifier;
//     string key;
// };
//
// class KeyManager {
// private:
//     vector<KeyEntry> keyStore;
//
// public:
//     void storeKey(const string &identifier, const string &key);
//     string retrieveKey(const string &identifier);
//     void updateKey(const string &identifier, const string &newKey);
//     void deleteKey(const string &identifier);
// };

// -------------------- LogManager --------------------
class LogManager {
private:
    static LogManager* instance;
    vector<string> logHistory;
    string logFilePath;
    LogManager(); // private constructor for singleton
    void loadLogsFromFile();
    void saveLogsToFile();

public:
    static LogManager* getInstance();
    void logEvent(const string& event);
    void displayLogs() const;
    void deleteLogAtIndex(int index);
    void deleteAlllogs();
};


#endif//FUNCTIONS_H