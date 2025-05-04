#ifndef ALERT_H
#define ALERT_H

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <exception>
#include <string>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

// Forward declarations
class Alert;
class CentralNotifier;

//Alert (Base Class)
class Alert {
protected:
    int id;
    string message;
    string level;
    string timestamp;
    static int totalAlerts;

public:
    Alert(int id, const string& msg, const string& lvl, const string& time);
    virtual ~Alert();

    virtual void notify() const = 0;
    virtual json toJSON() const = 0;

    static int getTotal();

    friend void debugLog(const Alert& alert);
    friend class CentralNotifier;

    operator string() const; // Cast operator
};

//Derived Classes
class EmailAlert : public Alert {
public:
    EmailAlert(int id, const string& msg, const string& lvl, const string& time);
    void notify() const override;
    json toJSON() const override;
};

class SMSAlert : public Alert {
public:
    SMSAlert(int id, const string& msg, const string& lvl, const string& time);
    void notify() const override;
    json toJSON() const override;
};

//Singleton Class
class CentralNotifier {
private:
    static CentralNotifier* instance;
    CentralNotifier() {}
    CentralNotifier(const CentralNotifier&) = delete;
    void operator=(const CentralNotifier&) = delete;

public:
    static CentralNotifier* getInstance();
    void notifyAll(const Alert& alert);
    ~CentralNotifier() {}
};

//AlertManager
class AlertManager {
private:
    vector<Alert*> alerts;
    map<string, string> alertLevels;

public:
    void addAlert(Alert* alert);
    void loadAlertsFromJSON(const string& filename);
    void saveAlertsToJSON(const string& filename) const;
    void showAllAlerts() const;
    ~AlertManager();
};

//Friend Function
void debugLog(const Alert& alert);

//Inline Function
inline void quickAlert(const string& msg) {
    cout << "Quick Alert: " << msg << endl;
}

//Function Overloading
void showAlert(const string& msg);
void showAlert(const Alert& alert);

//Template Class
template <typename T>
class AlertPair {
private:
    T alert1;
    T alert2;

public:
    AlertPair(T a1, T a2) : alert1(a1), alert2(a2) {}
    void showPair() {
        cout << "Pair of Alerts:" << endl;
        cout << string(*alert1) << endl;
        cout << string(*alert2) << endl;
    }
};


#endif