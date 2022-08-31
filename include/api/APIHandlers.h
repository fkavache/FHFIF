#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include "controller/Controller.h"
#include "utils/Keys.h"

using json = nlohmann::json;
using namespace std;

enum SStatus {
    S_SUCCESS = 200,
    S_AUTH_ERROR = 401,
    S_ERROR = 500
};

typedef pair<SStatus, string> (*ControllerHandler)(const string&, json& data);

class APIHandlers {
public:
    APIHandlers() = delete;

    // POST
    static pair<SStatus, string> registerUser(const string&, json& data);
    static pair<SStatus, string> loginUser(const string&, json& data);
    static pair<SStatus, string> characterToTransfer(const string&, json& data);

    // GET
    static pair<SStatus, string> fetchHome(const string&, json& data);
    static pair<SStatus, string> fetchCharacters(const string&, json& data);
    static pair<SStatus, string> fetchTransfers(const string&, json& data);

    // PUT
    static pair<SStatus, string> updateHome(const string&, json& data);
    static pair<SStatus, string> updateCharacter(const string&, json& data);
    static pair<SStatus, string> transferCharacter(const string&, json& data);
private:
    static string tokenToJson(const string& token);
    static string homeToJson(const Home& home);
    static string charactersToJson(const vector<Character>& characters);
    static string transfersToJson(const vector<Transfer>& transfers);

    static int ivalue(json& data, const string& key);
    static string svalue(json& data, const string& key);

    static SStatus CTOS(CStatus status);
};