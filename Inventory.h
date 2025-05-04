// Inventory.h
#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "json.hpp"


using namespace std;
using json = nlohmann::json;

// Forward declarations
class Equipment;
class MaintenanceRecord;
class Inventory;

// Friend class declaration
class MaintenanceRecord {
    public:
    string lastServiceDate;
    string status;


    MaintenanceRecord(const string& date = "N/A", const string& stat = "Unknown")
        : lastServiceDate(date), status(stat) {}

    friend class Equipment;
    friend ostream& operator<<(ostream& os, const MaintenanceRecord& m);
};

class Equipment {
    string id, name, category;
    MaintenanceRecord maintenance;

public:
    Equipment(const string& id = "", const string& name = "", const string& cat = "")
        : id(id), name(name), category(cat) {}

    // Static function
    static void staticInfo() {
        cout << "Static Info: Equipment objects store ID, Name, Category and Maintenance Data.\n";
    }

    // Inline function
    inline string getID() const { return id; }

    // Friend class/function
    friend class Inventory;
    friend ostream& operator<<(ostream& os, const Equipment& eq);
    friend bool operator==(const Equipment& lhs, const Equipment& rhs);

    // Operator overloading
    Equipment operator+(const Equipment& other) const;
    Equipment& operator=(const Equipment& other);
    explicit operator string() const;
};

class Inventory {
    vector<Equipment> equipmentList;
    map<string, Equipment> equipmentMap;

    // Singleton pattern
    static Inventory* instance;
    Inventory() {}

public:
    // Static method to access singleton
    static Inventory& getInstance();

    // Prevent copying
    Inventory(const Inventory&) = delete;
    Inventory& operator=(const Inventory&) = delete;

    void addEquipment(const Equipment& eq);
    void removeEquipment(const string& id);
    void showAll() const;
    void saveToJSON(const string& filename) const;
    void loadFromJSON(const string& filename);

    // Function overloading
    void addEquipment(const Equipment& eq, const MaintenanceRecord& record);

    // Exception throwing method
    void checkEquipmentExists(const string& id) const;
};

#endif