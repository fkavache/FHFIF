#pragma once

#include <iostream>

using namespace std;

class Home {
private:
    int m_id;
    string m_name;
    int m_sugarCubes;
    int m_userId;

public:
    Home();
    Home(string name, int sugarCubes, int userId);

    int getID() const;
    string getName() const;
    int getSugarCubes() const;
    int getUserID() const;

    void setID(int id);
    void setName(string&& name);
    void setSugarCubes(int sugarCubes);
    void setUserID(int userID);

    string toString();
};