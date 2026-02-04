#include <iostream>
#include "SecureCommunication.h"
#include <fstream>
using namespace std;
void showMainMenu() {
    cout << "\n\n==============================================\n\n";          
    cout << "          Secure Communication System      \n";
    cout << "\n\n===============================================\n\n";
    cout << "1.Encrypt Message\n";
    cout << "2.Decrypt Message\n";
    cout << "3.Retry Send Message\n";
    cout << "4.View Logs\n";
    cout << "5.Delete Logs at specific index\n";
    cout << "6.Delete All Logs\n";
    cout << "7.Update Caesar Key\n";
    cout << "8.Exit\n";
    cout << "Choose option(1-7): ";
}

int main() {
    string username;//get username
    string password;//password
    UserManagement userManager1;

    cout << "=========== Secure System Login ============\n";
    cout<<"Entre Username: ";
    cin>>username;
    cout <<"Password: ";
    cin>>password;

    if (!userManager1.verifyUserAccess(username, password)) {
        cout<<"Access Denied. Invalid Credentials.\n";
        return 0;
    }
    userManager1.displayUserInfo(username);
    int encryptionkey;
    cout<<"\nEnter Caesar Shift Key: ";
    cin>>encryptionkey;
    CaesarEncryption caesar(encryptionkey);
    SecureMessage message(&caesar);
    LogManager*logger=LogManager::getInstance();
    int choice;
    do {
         showMainMenu(); //show main menu
        cin>>choice;
        cin.ignore();    // clears input buffer
         switch(choice){
            case 1: {  //case 1 (encrypt message)
                string plainmessage;//plain input text message
                 cout<<"Enter your message to encrypt: ";
                  getline(cin,plainmessage);
                 message.setMessage(plainmessage);//set message
                string encrypted=message.sendMessage();//send message
                cout<<"Encrypted Message: "<< encrypted<<endl;//show encrypted method
                 logger->logEvent("Message Encrypted.");//logging
                break;
            }
            case 2: {//case 2 decrypt message
                  string encrypted;//encryted message
                  cout<<"Enter the encrypted message to decrypt: ";
                  getline(cin, encrypted);
                     string decrypted=message.receiveMessage(encrypted);
                  cout<<"Decrypted Message: " << decrypted << endl;
                   logger->logEvent("Message Decrypted.");//logging
                  break;
            }
            case 3: {//retry send
                    string retrymsg;
                  int retries;
                 cout <<"Enter message to send with retry: ";
                 getline(cin, retrymsg);
                  cout<<"Enter retry attempts: ";
                 cin>>retries;
                   cin.ignore();
                 message.setMessage(retrymsg);//set message
                try { //try
                     string result=message.retrySendMessage(retries);//exception handling
                    cout<<"Encrypted Message after retries: " << result << endl;
                    logger->logEvent("Retry Encryption Successful.");
                }
                catch (exception& e) {//catch exception
                    cout<<e.what() << endl;
                    logger->logEvent("Retry Failed.");
                }
                break;
            }
            case 4: {//viewlogs
                cout << "============= Log History ============\n";
                logger->displayLogs();//display log
                break;
            }
             case 5: {//delete log at specific index
                logger->displayLogs();//display log
                int index;
                cout<<"Entre index you want to delete: "<<endl;//chose index
                cin>>index;
                logger->deleteLogAtIndex(index);//deelte that speicfic log
                break;
             }
             case 6: {//delete all logs
                logger->deleteAlllogs();
                break;
             }
            case 7: { //entre new key
                string encryptionupdatedkey;
                cout<<"Enter new Caesar Key: ";
                cin>>encryptionupdatedkey;
                cin.ignore();
                caesar.updateKey(encryptionupdatedkey);
                cout << "Encryption Key Updated.\n";
                logger->logEvent("Encryption Key Updated.");
                break;
            }
            case 8: {//Exit
                cout<<"Exiting..................."<<endl;;
                cout<<" Goodbye!\n";
                  logger->logEvent("User Logged Out.");//how in logs histroy
                break;
            }
            default: {//invalid option
                  cout<<"Invalid option....Please Try again!\n";
                break;
            }
        }
    } while(choice != 8);//repeat until user chooese exit

    return 0;
}