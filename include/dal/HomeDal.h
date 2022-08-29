#pragma once

#include <iostream>
#include "Dal.h"
#include "model/Home.h"

typedef DAL::Entry Entry;
typedef DAL::Field Field;

class HomeDAL {
private:
    static Entry homeToEntry(const Home& home);
    static Home entryToHome(const Entry& entry);

public:
    static int insert(const Home& home);
    static vector<Home> selectAll();
    static Home selectByUserID(int userId);
    static Home selectByID(int id);
    static void updateName(int id, const string& name);
    static void updateSugarCubes(int id, int sugarCubes);
};