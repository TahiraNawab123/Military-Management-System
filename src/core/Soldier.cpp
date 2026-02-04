#include "Soldier.h"
#include<iostream>
#include<fstream>

using namespace std;


void Soldier::reportIssue() {
    // Get Soldier ID, issue title, and description from the user
    string soldierID, issueTitle, issueDescription;

    cout << "Enter Soldier ID: ";
    cin >> soldierID;

    cout << "Enter the issue title: ";
    cin.ignore();  // To clear any leftover input from the buffer
    getline(cin, issueTitle);  // To read the entire title

    cout << "Enter the issue description: ";
    getline(cin, issueDescription);  // To read the entire description

    // Create the issue report with Soldier ID, title, description, and a default "Pending" status
    ofstream file("issues.txt", ios::app);
    if (file.is_open()) {
        file << "ID: " << soldierID << endl << ", Title: " << endl << issueTitle << ", Description: " << endl <<issueDescription << ", Status: Pending\n";
        file.close();
        cout << "Issue reported successfully.\n";
    } else {
        cout << "Error opening file to report the issue.\n";
    }
}

void Soldier::viewReportedIssues() {
    ifstream reportFile("issues.txt");
    if (!reportFile) {
        cout << "No issues reported yet.\n";
        return;
    }

    string issue;
    cout << "\n--- Reported Issues ---\n";
    while (getline(reportFile, issue)) {
        cout << issue << endl;  // Display each reported issue
    }
    reportFile.close();
}

void Soldier::performTask() {
    int choice;
    do {
        cout << "\n===== Soldier Menu =====\n";
        cout << "1. Report an Issue\n";
        cout << "2. View Reported Issues\n";
        cout << "3. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            reportIssue();
            break;
        case 2:
            viewReportedIssues();
            break;
        case 3:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
}