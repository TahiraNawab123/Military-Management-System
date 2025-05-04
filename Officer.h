#ifndef OFFICER_H
#define OFFICER_H

#include "User.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

class Officer : public User {
public:
    // Method to approve or change the status of reported issues
    void approveIssueStatus();

    void performTask() override;
    void viewReport() override;
};

#endif

