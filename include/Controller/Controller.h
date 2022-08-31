#pragma once

#include "dal/CharacterDal.h"
#include "dal/HomeDal.h"
#include "dal/TransferDal.h"
#include "dal/UserDal.h"

#include "model/Character.h"
#include "model/Home.h"
#include "model/Transfer.h"
#include "model/User.h"

using namespace std;

enum CStatus {
    C_SUCCESS = 0,
    C_AUTH_ERROR,
    C_ERROR,
};

class Controller {
public:
    static CStatus registerUser(string&& email, string&& password, string& token);
    static CStatus loginUser(string&& email, string&& password, string& token);
    static CStatus fetchUserHome(string&& email, Home& out);

    static bool isAuthorized(const string& token, string& email);
private:
    static void createCharacters(int homeID, int N);
};