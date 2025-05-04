// functions.cpp
#include "json.hpp"
using json = nlohmann::json;
#include "Inventory.h"

// Define static Inventory instance
Inventory* Inventory::instance = nullptr;

// Friend function for MaintenanceRecord
ostream& operator<<(ostream& os, const MaintenanceRecord& m) {
    os << "Last Serviced: " << m.lastServiceDate << ", Status: " << m.status;
    return os;
}

// Friend function for Equipment
ostream& operator<<(ostream& os, const Equipment& eq) {
    os << "ID: " << eq.id << ", Name: " << eq.name << ", Category: " << eq.category << "\n"
       << eq.maintenance;
    return os;
}

// Operator== overload
bool operator==(const Equipment& lhs, const Equipment& rhs) {
    return lhs.id == rhs.id;
}

// Operator+ overload
Equipment Equipment::operator+(const Equipment& other) const {
    return Equipment(id + "+" + other.id, name + " & " + other.name, category);
}

// Operator= overload
Equipment& Equipment::operator=(const Equipment& other) {
    if (this != &other) {
        id = other.id;
        name = other.name;
        category = other.category;
        maintenance = other.maintenance;
    }
    return *this;
}

// Cast operator (Equipment to string)
Equipment::operator string() const {
    return id + " - " + name + " (" + category + ")";
}

// Singleton access
Inventory& Inventory::getInstance() {
    if (!instance) {
        instance = new Inventory();
    }
    return *instance;
}

// Add Equipment (basic)
void Inventory::addEquipment(const Equipment& eq) {
    equipmentList.push_back(eq);
    equipmentMap[eq.id] = eq;
}

// Add Equipment with MaintenanceRecord (function overloading)
void Inventory::addEquipment(const Equipment& eq, const MaintenanceRecord& record) {
    Equipment copy = eq;
    copy.maintenance = record;
    addEquipment(copy);
}

// Remove Equipment
void Inventory::removeEquipment(const string& id) {
    bool found = false;
    for (auto it = equipmentList.begin(); it != equipmentList.end(); ++it) {
        if (it->id == id) {
            equipmentList.erase(it);
            equipmentMap.erase(id);
            found = true;
            cout << "Removed equipment with ID: " << id << endl;
            break;
        }
    }
    if (!found) {
        cout << "Equipment ID not found.\n";
    }
}

// Show all equipment
void Inventory::showAll() const {
    for (const auto& eq : equipmentList) {
        cout << eq << "\n\n";
    }
}

// Save to JSON
void Inventory::saveToJSON(const string& filename) const {
    json j;
    for (const auto& eq : equipmentList) {
        j.push_back({
            {"id", eq.id},
            {"name", eq.name},
            {"category", eq.category},
            {"maintenance", {
                {"lastServiceDate", eq.maintenance.lastServiceDate},
                {"status", eq.maintenance.status}
            }}
        });
    }

    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error: Could not open file for writing.\n";
        return;
    }
    outFile << j.dump(4);
    outFile.close();
    cout << "Inventory saved to " << filename << endl;
}

// Load from JSON
void Inventory::loadFromJSON(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Could not open file for reading.\n";
        return;
    }

    json j;
    inFile >> j;
    equipmentList.clear();
    equipmentMap.clear();

    for (const auto& item : j) {
        Equipment eq(item["id"], item["name"], item["category"]);
        eq.maintenance = MaintenanceRecord(item["maintenance"]["lastServiceDate"], item["maintenance"]["status"]);
        addEquipment(eq);
    }

    cout << "Inventory loaded from " << filename << endl;
}

// Exception example
void Inventory::checkEquipmentExists(const string& id) const {
    if (equipmentMap.find(id) == equipmentMap.end()) {
        throw runtime_error("Equipment with ID " + id + " not found.");
    } else {
        cout << "Equipment found: " << string(equipmentMap.at(id)) << "\n";
    }
}