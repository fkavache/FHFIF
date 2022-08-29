#pragma once

#include <iostream>

using namespace std;

class User {
private:
    int m_id;
    string m_eMail;
    string m_password;

public:
    User(string eMail, string password);

    int getID() const;
    string getEMail() const;
    string getPassword() const;

    void setID(int id);
    void setEMail(string&& eMail);
    void setPassword(string&& password);

    string toString();
};