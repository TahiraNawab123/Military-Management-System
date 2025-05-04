#ifndef SOLDIER_H
#define SOLDIER_H

#include "User.h"
#include<iostream>
#include<fstream>
using namespace std;

class Soldier : public User {
public:
      // Method to report an issue
      void reportIssue();

      // Method to view reported issues
      void viewReportedIssues();
  
      // Menu function to interact with soldier
      void performTask() override;
  
      // Method to view report (status included)
      void viewReport() override {
          cout << "\n--- Soldier's Report Viewing ---\n";
          
          // Reading and displaying reported issues from a file (issues.txt)
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
};

#endif
