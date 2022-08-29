#pragma once

#include <iostream>

using namespace std;

class Home {
private:
    int m_id;
    string m_name;
    int m_sugarCubes;
    int m_sugarCubesBudget;
    int m_userId;

public:
    Home();
    Home(string name, int sugarCubes, int sugarCubesBudget, int userId);

    int getID() const;
    string getName() const;
    int getSugarCubes() const;
    int getSugarCubesBudget() const;
    int getUserID() const;

    void setID(int id);
    void setName(string&& name);
    void setSugarCubes(int sugarCubes);
    void setSugarCubesBudget(int sugarCubesBudget);
    void setUserID(int userID);

    string toString();
};