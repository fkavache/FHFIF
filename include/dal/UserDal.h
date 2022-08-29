#pragma once

#include <iostream>
#include "Dal.h"
#include "model/User.h"

typedef DAL::Entry Entry;
typedef DAL::Field Field;

class UserDAL {
private:
    static Entry userToEntry(const User& user);
    static User entryToUser(const Entry& entry);

public:
    static int insert(const User& user);
    static vector<User> selectAll();
    static User selectByEmail(const string& email);
};