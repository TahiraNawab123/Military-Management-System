#include "Alert.h"

int main() {
    try {
        AlertManager manager;

        cout << "Loading alerts from JSON..." << endl;
        manager.loadAlertsFromJSON("alerts.json");

        cout << endl << "Showing loaded alerts:" << endl;
        manager.showAllAlerts();

        cout << endl << "Adding new alert..." << endl;
        Alert* newAlert = new EmailAlert(6, "Intrusion detected in Zone A", "High", "2025-05-01 20:00:00");
        manager.addAlert(newAlert);

        cout << "Notifying via CentralNotifier..." << endl;
        CentralNotifier::getInstance()->notifyAll(*newAlert);

        cout << "Logging with friend function..." << endl;
        debugLog(*newAlert);

        cout << "Saving updated alerts to JSON..." << endl;
        manager.saveAlertsToJSON("alerts.json");

        cout << "Inline quick alert..." << endl;
        quickAlert("in Zone B!");

        cout << endl << "Showing alerts using overloaded functions:" << endl;
        showAlert("Manual alert triggered.");
        showAlert(*newAlert);

        cout << endl << "Pairing alerts with template class..." << endl;
        Alert* alert1 = new SMSAlert(7, "System reboot", "Info", "2025-05-01 21:00:00");
        manager.addAlert(alert1);
        AlertPair<Alert*> pair(newAlert, alert1);
        pair.showPair();

        cout << endl << "Total alerts so far: " << Alert::getTotal() << endl;

    } catch (const exception& e) {
        cerr << endl << "Exception: " << e.what() << endl;
    }

    return 0;
}