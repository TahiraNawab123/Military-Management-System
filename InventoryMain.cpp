// // main.cpp
#include <iostream>
#include "Inventory.h"

// using namespace std;

// int main() {
//     try {
//         // Singleton instance of Inventory
//         Inventory& inv = Inventory::getInstance();

//         // Sample data creation
//         Equipment eq1("E001", "Rifle", "Weapon");
//         Equipment eq2("E002", "Helmet", "Protective Gear");
//         Equipment eq3("E003", "Bulletproof Vest", "Protective Gear");

//         // Add equipment
//         inv.addEquipment(eq1);
//         inv.addEquipment(eq2);
//         inv.addEquipment(eq3);

//         // Display all equipment
//         cout << "All Equipment:\n";
//         inv.showAll();

//         // Save inventory to JSON
//         inv.saveToJSON("inventory.json");

//         // Load inventory from JSON
//         inv.loadFromJSON("inventory.json");

//         // Check for specific equipment
//         inv.checkEquipmentExists("E002");
//         inv.checkEquipmentExists("E004");  // This will throw an exception

//         // Remove equipment
//         inv.removeEquipment("E002");
//         inv.removeEquipment("E004");  // This will notify equipment not found

//         // Show remaining equipment
//         cout << "Remaining Equipment:\n";
//         inv.showAll();

//     } catch (const exception& e) {
//         cerr << "Error: " << e.what() << endl;
//     }

//     return 0;
// }




int main() {
    Inventory& inv = Inventory::getInstance();
    int choice;
    string id, name, category, date, status, filename;

    do {
        cout << "\n===== Equipment Inventory Menu =====\n";
        cout << "1. Add Equipment\n";
        cout << "2. Add Equipment with Maintenance Record\n";
        cout << "3. Remove Equipment\n";
        cout << "4. Show All Equipment\n";
        cout << "5. Save Inventory to JSON\n";
        cout << "6. Load Inventory from JSON\n";
        cout << "7. Check Equipment Exists\n";
        cout << "0. Exit\n";
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
                    cout << "Exiting...\n";
                    break;

                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }

    } while (choice != 0);

    return 0;
}