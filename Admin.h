#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include<iostream>
using namespace std;

class Admin : public User {
    private:
    void addUser();
    void deleteUser();
    void modifyUser();
    void showAllUsers();


    public:
    void performTask() override;
    void viewReport() override;
    void manageAccounts();
    void resetPassword();
    };
    

#endif
