#include "Officer.h"
#include<iostream>
#include<fstream>

using namespace std;

void Officer::approveIssueStatus() {
    ifstream issueFile("issues.txt");
    if (!issueFile) {
        cout << "No issues reported yet.\n";
        return;
    }

    vector<string> issues;
    string issue;
    while (getline(issueFile, issue)) {
        issues.push_back(issue);  // Store each issue for later processing
    }
    issueFile.close();

    // Show reported issues with status
    cout << "\n--- Issues for Approval ---\n";
    for (int i = 0; i < issues.size(); i++) {
        cout << (i + 1) << ". " << issues[i] << endl;  // Display each reported issue
    }

    // Choose an issue to approve or change status
    int issueIndex;
    cout << "Enter the issue number to approve or change the status: ";
    cin >> issueIndex;

    if (issueIndex < 1 || issueIndex > issues.size()) {
        cout << "Invalid issue number.\n";
        return;
    }

    string newStatus;
    cout << "Enter the new status (e.g., Resolved, Pending, In Progress): ";
    cin.ignore();  // To clear any leftover input from the buffer
    getline(cin, newStatus);  // Get the new status from the officer

    // Modify the status of the selected issue
    size_t pos = issues[issueIndex - 1].find("Status: ");
    if (pos != string::npos) {
        issues[issueIndex - 1] = issues[issueIndex - 1].substr(0, pos + 8) + newStatus;
    }

    // Write the updated issues back to the file
    ofstream file("issues.txt", ios::trunc);  // Overwrite the file
    for (const auto& updatedIssue : issues) {
        file << updatedIssue << endl;
    }
    file.close();
    cout << "Issue status updated successfully.\n";
}

void Officer::performTask() {
    int choice;
    do {
        cout << "\n===== Officer Menu =====\n";
        cout << "1. Approve/Update Issue Status\n";
        cout << "2. View Reported Issues\n";
        cout << "3. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            approveIssueStatus();
            break;
        case 2:
            viewReport();
            break;
        case 3:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
}

void Officer::viewReport() {
    cout << "\n--- Officer's Report Viewing ---\n";
    ifstream issueFile("issues.txt");
    if (!issueFile) {
        cout << "No issues reported yet.\n";
        return;
    }

    string line;
    while (getline(issueFile, line)) {
        cout << line << endl;  // Print each reported issue
    }
    issueFile.close();
}
