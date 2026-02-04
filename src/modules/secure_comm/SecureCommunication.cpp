#include "SecureCommunication.h"

    //-----------------------------------------------//
    //-------------CaesarEncryption-----------------//
//-----------------------------------------------//
CaesarEncryption::CaesarEncryption(int shiftValue) { //constructor
    shift = shiftValue;
}
string CaesarEncryption::encrypt(const string &data) {//encrypt the message using Cipher logic
    string encryptionResult=data;//copy of input string store in encryption result
    for (char &ch:encryptionResult){//using loop
        if (isalpha(ch)) {//check if charcter is a letter or not
            char base = islower(ch) ? 'a' : 'A';//choose base
            ch = (ch - base + shift) % 26 + base;//apply Caesar shift
        }
    }
    return encryptionResult;//return result
}

string CaesarEncryption::decrypt(const string &data) {
    string encryptionResult=data;//make copy
    for (char &ch:encryptionResult) {//loop
        if (isalpha(ch)) {//check if chracter is a letter or not
 char base=islower(ch)?'a' : 'A';//choose base
              ch=(ch-base -shift +26)% 26 + base;//reverse shift
        }
    }
    return encryptionResult;//return decrypted result
}

void CaesarEncryption::updateKey(const string &data) {
    try {
        shift=stoi(data);
    }
    catch (...) {
        throw invalid_argument("Shift must be a number");
    }

}

string CaesarEncryption::getAlgorithmName() {//algorithm name
    return "Caesar Cipher";
}
//-----------------------------------------------//
//-------------SecureMessage-----------------//
//-----------------------------------------------//
//constrcutor
SecureMessage::SecureMessage(Encryption *enc, const string &message):encryption(enc),messageContent(message),encryptionStatus(false){}
void SecureMessage::setMessage(const string &message) {
    //xet message
    messageContent=message;
}
string SecureMessage::getMessage() const {//get message
    return messageContent;
}
string SecureMessage::sendMessage() { //encrypt and send messaege
    try {//exception handling
        string encrypted=encryption->encrypt(messageContent);
        encryptionStatus = true;
        return encrypted;
    }
    catch (const exception &e) {
        encryptionStatus = false;
        throw;
    }
}
string SecureMessage::receiveMessage(const string &encryptedMessage) {//secure message
    try {//exception handling
         string decrypted=encryption->decrypt(encryptedMessage);
           encryptionStatus=true;
         return decrypted;
    }
    catch (const exception &e) {//catch
        encryptionStatus = false;
        throw;
    }
}
bool SecureMessage::getEncryptionStatus() const {
    return encryptionStatus;//get encrption status
}
SecureMessage SecureMessage::operator+(const SecureMessage &other) {//cogine message display
    SecureMessage combinedMessage(encryption);
    combinedMessage.messageContent=this->messageContent +" "+other.messageContent;
    return combinedMessage;
}
void SecureMessage::displayModuleInfo() {
    cout<<"Secure Communication Module\n";
    cout<<"Caesar Cipher encryption, formatting, retries supported\n";
}
string SecureMessage::retrySendMessage(int retries) {
    int attempts =0;
    while(attempts<retries) {
        try {
            return sendMessage();
        }
        catch (...) {
            attempts++;
            cout<<"Retry Attempts are: "<<attempts<<endl;

        }

    }
    throw runtime_error("Attempts limit Reached! Failed to send message");
}

//-----------------------------------------------//
//-------------User management-----------------//
//-----------------------------------------------//
bool UserManagement::verifyUserAccess(const string &username, const string &password) {
                   // Dummy example
    return username == "Aiman" && password == "1234";
}
void UserManagement::displayUserInfo(const string &username) {//display info
    cout << "User Info for: " << username << endl;
}

// //-----------------------------------------------//
// //-------------KeyManager-----------------//
// //-----------------------------------------------//
// void KeyManager::storeKey(const string &identifier, const string &key) {
//     //store key
//     KeyEntry entry;
//     entry.identifier = identifier;
//     entry.key = key;
//     keyStore.push_back(entry);
// }
// string KeyManager::retrieveKey(const string &identifier) {//RETRIVE KEY
//     for (int k=0;k<keyStore.size();k++) {//LOOP
//         if(keyStore[k].identifier==identifier) {//compare
//             return keyStore[k].key;//store key
//         }
//     }
//     throw runtime_error("Key not founded!!");
// }
// void KeyManager::updateKey(const string &identifier, const string &newKey) {
//     for (int u= 0;u< keyStore.size();u++) {
//          if (keyStore[u].identifier==identifier) {//compare compare key
//                 keyStore[u].key=newKey;
//                   return;
//         }
//     }
//      throw runtime_error("Key not founded for update!!");
// }
// void KeyManager::deleteKey(const string &identifier) {//delete key
//     for (int d=0;d<keyStore.size();d++) {
//          if (keyStore[d].identifier==identifier) {//compare identifiew
//               keyStore.erase(keyStore.begin()+d);
//               return;
//         }
//     }
//       throw runtime_error("Key not found for deletion");
// }
//-----------------------------------------------//
//-------------LogManager-----------------//
//-----------------------------------------------//
LogManager* LogManager::instance = nullptr;

LogManager::LogManager() { //manage logs
    logFilePath = "log.json";
    loadLogsFromFile();
}
LogManager* LogManager::getInstance() {//get instance of singleton class
      if (instance==nullptr){

        instance=new LogManager();
      }
     return instance;
}

void LogManager::logEvent(const string& event) {
    // Timestamp
      time_t now=time(0);
      char* dt=ctime(&now);
    string timestampedEvent="[" + string(dt).substr(0, 24) + "] "+ event;
    logHistory.push_back(timestampedEvent);
    saveLogsToFile();    //save timing of log in the log file
}

void LogManager::saveLogsToFile() {//save to file
    json j;
    j["logs"] = logHistory;

    ofstream outFile(logFilePath);
    if (outFile.is_open()) {//if file is open
        outFile << j.dump(4); // Pretty print JSON
        outFile.close();
    }
}

void LogManager::loadLogsFromFile() {// load from json file
    ifstream inFile(logFilePath);
    if (inFile.is_open()) { //if file is open
        json j;
        inFile >> j;//load logs
        if (j.contains("logs")) {
            logHistory = j["logs"].get<vector<string>>();
        }
        inFile.close();
    }
}

void LogManager::displayLogs() const {//display logs
if(logHistory.empty()) {
    cout<<"No logs avaiable.\n";
    return;
}
    int index=0;// to store index
    for (const string& entry:logHistory) {//for each loop
        cout<<index++<<":"<<entry<<endl;//display logs with index
    }
}
void LogManager::deleteLogAtIndex(int index) {
    if(index >=0 && index<logHistory.size()) { //Check if the give index is valid or not
        cout<<"Deleted log: "<<endl;
        cout<<logHistory[index]<<endl;
        logHistory.erase(logHistory.begin()+index);//remove the log at specific inex
        saveLogsToFile();
    }
    else {
        cout<<"Invalid log\n";
    }
}
void LogManager::deleteAlllogs() {
    logHistory.clear();//Remove all logs
    saveLogsToFile(); //overwriting file empty array
    cout<<"All Logs have been deleted!\n";
}