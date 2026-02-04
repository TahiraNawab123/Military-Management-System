#include "Alert.h"

int Alert::totalAlerts = 0;
CentralNotifier* CentralNotifier::instance = nullptr;

Alert::Alert(int id, const string& msg, const string& lvl, const string& time)
    : id(id), message(msg), level(lvl), timestamp(time) {
    totalAlerts++;
}

Alert::~Alert() {}

int Alert::getTotal() {
    return totalAlerts;
}

EmailAlert::EmailAlert(int id, const string& msg, const string& lvl, const string& time)
    : Alert(id, msg, lvl, time) {}

void EmailAlert::notify() const {
    cout << "Email Alert [" << id << "] - " << level << " - " << message << timestamp << endl;
}

json EmailAlert::toJSON() const {
    return json{{"type", "Email"}, {"id", id}, {"message", message}, {"level", level}, {"timestamp", timestamp}};
}

SMSAlert::SMSAlert(int id, const string& msg, const string& lvl, const string& time)
    : Alert(id, msg, lvl, time) {}

void SMSAlert::notify() const {
    cout << "SMS Alert [" << id << "] - " << level << " - " << message << timestamp << endl;
}

json SMSAlert::toJSON() const {
    return json{{"type", "SMS"}, {"id", id}, {"message", message}, {"level", level}, {"timestamp", timestamp}};
}

void AlertManager::addAlert(Alert* alert) {
    alerts.push_back(alert);
}

void AlertManager::loadAlertsFromJSON(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw runtime_error("File not found");
    }

    json j;
    inFile >> j;
    for (const auto& item : j) {
        int id = item.at("id");
        string msg = item.at("message");
        string lvl = item.at("level");
        string time = item.at("timestamp");

        if (item.at("type") == "Email")
            alerts.push_back(new EmailAlert(id, msg, lvl, time));
        else if (item.at("type") == "SMS")
            alerts.push_back(new SMSAlert(id, msg, lvl, time));
    }

    inFile.close();
}

void AlertManager::saveAlertsToJSON(const string& filename) const {
    json j;
    for (const auto& a : alerts) {
        j.push_back(a->toJSON());
    }

    ofstream outFile(filename);
    outFile << j.dump(4);
    outFile.close();
}

void AlertManager::showAllAlerts() const {
    for (const auto& a : alerts) {
        a->notify();
    }
}

AlertManager::~AlertManager() {
    for (auto a : alerts) {
        delete a;
    }
}

void debugLog(const Alert& alert) {
    cout << "DEBUG LOG - Alert ID: " << alert.id << ", Level: " << alert.level << ", Message: " << alert.message << endl;
}

void showAlert(const string& msg) {
    cout << "Alert: " << msg << endl;
}

void showAlert(const Alert& alert) {
    alert.notify();
}

CentralNotifier* CentralNotifier::getInstance() {
    if (!instance)
        instance = new CentralNotifier();
    return instance;
}

void CentralNotifier::notifyAll(const Alert& alert) {
    cout << "Central Notification: " << string(alert) << endl;
}

Alert::operator string() const {
    return "[" + to_string(id) + "] " + level + " - " + message + timestamp;
}
