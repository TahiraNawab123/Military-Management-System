#include <iostream>
#include <string>
#include "IDS.h"
#include "User.h"
#include "Message.h"
#include "Admin.h"
#include "Officer.h"
#include "Soldier.h"
#include "SecureCommunication.h"
#include "Inventory.h"
#include "Alert.h"
#include <windows.h>

using json = nlohmann::json;
using namespace std;

void launchUserSystem() {
    cout << "\n=============================================\n";
    cout << "        MILITARY USER ACCESS PORTAL\n";
    cout << "=============================================\n";

    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    string role;
    if (!authenticateUser(username, password, role)) {
        // authenticateUser already prints an appropriate message
        return;
    }

    User* user = nullptr;
    if (role == "Admin") {
        user = new Admin();
    } else if (role == "Officer") {
        user = new Officer();
    } else if (role == "Soldier") {
        user = new Soldier();
    } else {
        cout << "Unknown role configured for this user.\n";
        return;
    }

    // Initialize the in-memory representation for this session
    user->registerUser(username, password, role);

    cout << "\nAccess Granted! Role: " << role << "\n";

    // Lightweight messaging hub before entering the role dashboard
    Message msg;
    string choice;

    cout << "Do you want to send a message before entering the dashboard? (yes/no): ";
    cin >> choice;

    if (choice == "yes" || choice == "y") {
        string receiver, message_content;
        cout << "Enter recipient username: ";
        cin >> receiver;
        cin.ignore();
        cout << "Enter your message: ";
        getline(cin, message_content);
        msg.sendMessage(username, receiver, message_content);
    }

    cout << "\nYour Inbox:\n";
    msg.receiveMessage(username);

    // Hand over to role-specific dashboard
    user->performTask();
    user->viewReport();

    delete user;
}

void launchIDSSystem() {
    MotionSensor m1(101,"Near Gate", 10.5,"Motion Sensor", 20.5);
    MotionSensor m2(102,"Between two towers", 10.6,"Motion Sensor", 20.5);
    HeatSensor h1 (109,"Near the next base", 25.8,"Heat Sensor", 37.5);
    HeatSensor h2 (105,"At 2nd tower", 29.8,"Heat Sensor", 37.5);
    SensorInventory inventory;
Intruder intruder1(111,"5 feet from the tower","12:14 a.m",&m2,"Motion");
Intruder intruder2(112,"10 feet from the other base","12:25 a.m",&m1,"Motion");
Intruder intruder3(113,"15 feet from the tower","2:00 a.m",&h2,"Heat");
Intruder intruder4(114,"25 feet from the other base","12:25 a.m",&h1,"Heat");
IntrusionLog il;
int choice;
do{
cout<<"============================ Welcome to Intrusion Dectection System (IDS) ============================="<<endl;
cout<<"1. Add a Sensor"<<endl;
cout<<"2. Remove a Sensor"<<endl;
cout<<"3. Search a Sensor"<<endl;
cout<<"4. View All Sensors"<<endl;
cout<<"5. Detect Intrusion"<<endl;
cout<<"6. Assess Threat Level "<<endl;    
cout<<"7. View Intrusion Logs"<<endl;
cout<<"8. Generate Intrusion Report"<<endl;
cout<<"9. Log an event "<<endl;
cout<<"10. Exit program "<<endl;
cout<<"========================================================================================================="<<endl;
cout<<"Please enter your choice "<<endl;
cin>>choice;
switch (choice){
    case 1:
    cout<<"Add a Sensor"<<endl;
  
inventory.addSensor(&m1);
inventory.addSensor(&h1);
inventory.addSensor(&m2);
inventory.addSensor(&h2);
    break;
    case 2:
    cout<<"Enter the sensor id of sensor you want to remove"<<endl;
    int i;
cin>>i;
     inventory.removeSensor(i);
    break;
    case 3:
    int ID;
    cout<<"Enter the Id of sensor to search"<<endl;
cin>>ID;
   inventory.getSensorByID(ID);
    break;
    case 4:
    cout<<"View all Sensors"<<endl;
    inventory.displaySensors();
    cout<<"The total number of sensors are "<<inventory. getTotalSensors()<<endl;
    break;
    case 5:
    cout<<"Detect intrusion"<<endl;
  intruder1.displayIntruderInfo();
    break;
    case 6:
    cout<<"Access threat level"<<endl;
    {
        ThreatType level = ThreatLevel::analyzeThreat(intruder2);
        ThreatLevel::triggerBeep(level);
    }
    break;
    case 7:
    cout << "Using template class Storage to show all intruders\n";
    {
        Storage<Intruder> intruderStorage;
        intruderStorage.addItem(intruder1);
        intruderStorage.addItem(intruder2);
        intruderStorage.addItem(intruder3);
        intruderStorage.addItem(intruder4);

        intruderStorage.displayAll();
        cout << "Total intruders stored: " << intruderStorage.getCount() << endl;
    }
    cout<<"View intrusion logs"<<endl;
    il.addIntrusion( intruder1);
    il.addIntrusion( intruder2);
    il.addIntrusion( intruder3);
    il.addIntrusion( intruder4);
    il.displayIntrusions();
    
    break;
    case 8:
    cout<<"Generate intrusion report"<<endl;
     il.storeToJSON("Instrusions.json");
     il.loadFromJSON( "Instrusions.json");

    break;
    case 9:
    cout<<" Event logging "<<endl;
    Logger::getInstance()->logEvent("Motion detected near the gate.");
    Logger::getInstance()->logEvent("Heat sensor dected heat.");
    Logger::getInstance()->logEvent("Intruder detected.");

    break;
    case 10:
    cout<<" Exiting the program "<<endl;

    break;
default :
cout<<" Invalid choice... "<<endl;
break;
}
}
while (choice != 10);
} 

void launchInventorySystem() {
    Inventory& inv = Inventory::getInstance();
    int choice;
    string id, name, category, date, status, filename;

    do {
        cout << "\n===== Equipment Inventory Menu =====\n";
        cout << "1. Add Equipment\n2. Add Equipment with Maintenance Record\n3. Remove Equipment\n4. Show All Equipment\n5. Save Inventory to JSON\n6. Load Inventory from JSON\n7. Check Equipment Exists\n0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        try {
            switch (choice) {
                case 1:
                    cout << "Enter ID: "; getline(cin, id);
                    cout << "Enter Name: "; getline(cin, name);
                    cout << "Enter Category: "; getline(cin, category);
                    inv.addEquipment(Equipment(id, name, category));
                    break;
                case 2:
                    cout << "Enter ID: "; getline(cin, id);
                    cout << "Enter Name: "; getline(cin, name);
                    cout << "Enter Category: "; getline(cin, category);
                    cout << "Enter Last Service Date: "; getline(cin, date);
                    cout << "Enter Status: "; getline(cin, status);
                    inv.addEquipment(Equipment(id, name, category), MaintenanceRecord(date, status));
                    break;
                case 3:
                    cout << "Enter ID to remove: "; getline(cin, id);
                    inv.removeEquipment(id);
                    break;
                case 4:
                    inv.showAll();
                    break;
                case 5:
                    cout << "Enter filename to save (e.g., inventory.json): ";
                    getline(cin, filename);
                    inv.saveToJSON(filename);
                    break;
                case 6:
                    cout << "Enter filename to load (e.g., inventory.json): ";
                    getline(cin, filename);
                    inv.loadFromJSON(filename);
                    break;
                case 7:
                    cout << "Enter ID to check: "; getline(cin, id);
                    inv.checkEquipmentExists(id);
                    break;
                case 0:
                    cout << "Returning to Main Menu...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    } while (choice != 0);
}

void launchSecureCommunicationSystem() {
    string username, password;
    UserManagement userManager1;

    cout << "=========== Secure System Login ============\n";
    cout << "Enter Username: "; cin >> username;
    cout << "Password: "; cin >> password;

    if (!userManager1.verifyUserAccess(username, password)) {
        cout << "Access Denied. Invalid Credentials.\n";
        return;
    }

    userManager1.displayUserInfo(username);
    int encryptionkey;
    cout << "\nEnter Caesar Shift Key: "; cin >> encryptionkey;
    CaesarEncryption caesar(encryptionkey);
    SecureMessage message(&caesar);
    LogManager* logger = LogManager::getInstance();
    int choice;
    do {
        cout << "\n===== Secure Communication Menu =====\n";
        cout << "1. Encrypt Message\n2. Decrypt Message\n3. Retry Send Message\n4. View Logs\n5. Delete Log at Index\n6. Delete All Logs\n7. Update Caesar Key\n8. Back to Main Menu\n";
        cout << "Choose option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string plainmessage;
                cout << "Enter your message to encrypt: ";
                getline(cin, plainmessage);
                message.setMessage(plainmessage);
                string encrypted = message.sendMessage();
                cout << "Encrypted Message: " << encrypted << endl;
                logger->logEvent("Message Encrypted.");
                break;
            }
            case 2: {
                string encrypted;
                cout << "Enter the encrypted message to decrypt: ";
                getline(cin, encrypted);
                string decrypted = message.receiveMessage(encrypted);
                cout << "Decrypted Message: " << decrypted << endl;
                logger->logEvent("Message Decrypted.");
                break;
            }
            case 3: {
                string retrymsg;
                int retries;
                cout << "Enter message to send with retry: ";
                getline(cin, retrymsg);
                cout << "Enter retry attempts: ";
                cin >> retries;
                cin.ignore();
                message.setMessage(retrymsg);
                try {
                    string result = message.retrySendMessage(retries);
                    cout << "Encrypted Message after retries: " << result << endl;
                    logger->logEvent("Retry Encryption Successful.");
                } catch (exception& e) {
                    cout << e.what() << endl;
                    logger->logEvent("Retry Failed.");
                }
                break;
            }
            case 4:
                logger->displayLogs();
                break;
            case 5: {
                logger->displayLogs();
                int index;
                cout << "Enter index you want to delete: ";
                cin >> index;
                logger->deleteLogAtIndex(index);
                break;
            }
            case 6:
                logger->deleteAlllogs();
                break;
            case 7: {
                string encryptionupdatedkey;
                cout << "Enter new Caesar Key: ";
                cin >> encryptionupdatedkey;
                caesar.updateKey(encryptionupdatedkey);
                cout << "Encryption Key Updated.\n";
                logger->logEvent("Encryption Key Updated.");
                break;
            }
            case 8:
                logger->logEvent("User Logged Out.");
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (choice != 8);
}

void launchAlertSystem() {
    try {
        AlertManager manager;
        cout << "Loading alerts from JSON...\n";
        manager.loadAlertsFromJSON("alerts.json");
        cout << "\nShowing loaded alerts:\n";
        manager.showAllAlerts();

        Alert* newAlert = new EmailAlert(6, "Intrusion detected in Zone A", "High", "2025-05-01 20:00:00");
        manager.addAlert(newAlert);
        CentralNotifier::getInstance()->notifyAll(*newAlert);
        debugLog(*newAlert);
        manager.saveAlertsToJSON("alerts.json");

        quickAlert("in Zone B!");
        showAlert("Manual alert triggered.");
        showAlert(*newAlert);

        Alert* alert1 = new SMSAlert(7, "System reboot", "Info", "2025-05-01 21:00:00");
        manager.addAlert(alert1);
        AlertPair<Alert*> pair(newAlert, alert1);
        pair.showPair();

        cout << "\nTotal alerts so far: " << Alert::getTotal() << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main() {
    int option;
    do {
        cout << "\n========== Main Project Menu ==========\n";
        cout << "1. User System\n2. Intrusion Detection System\n3. Equipment Inventory System\n4. Secure Communication System\n5. Alert System\n6. Exit\n";
        cout << "Select option: ";
        cin >> option;

        switch (option) {
            case 1:
                launchUserSystem();
                break;
            case 2:
                launchIDSSystem();
                break;
            case 3:
                launchInventorySystem();
                break;
            case 4:
                launchSecureCommunicationSystem();
                break;
            case 5:
                launchAlertSystem();
                break;
            case 6:
                cout << "Exiting Project. Have Fun:P!\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (option != 6);

return 0;
}