#include "api/APIHandlers.h"

// Post Handlers ===============================
// =============================================
pair<SStatus, string> APIHandlers::registerUser(const string&,  json& data) {
    string token;

    CStatus status = Controller::registerUser(svalue(data, KEY_EMAIL),
                                              svalue(data, KEY_PASSWORD),
                                              token);

    return { CTOS(status), status == C_SUCCESS ? tokenToJson(token) : "" };
}

pair<SStatus, string> APIHandlers::loginUser(const string&,  json& data) {
    string token;

    CStatus status = Controller::loginUser(svalue(data, KEY_EMAIL),
                                           svalue(data, KEY_PASSWORD),
                                           token);

    return { CTOS(status), status == C_SUCCESS ? tokenToJson(token) : "" };
}

pair<SStatus, string> APIHandlers::characterToTransfer(const string &, json &data) {
    CStatus status = Controller::characterToTransferList(svalue(data, KEY_EMAIL),
                                                         ivalue(data, KEY_ID));

    return { CTOS(status), "" };
}

// =============================================
// =============================================

// Get Handlers ================================
// =============================================
pair<SStatus, string> APIHandlers::fetchHome(const string&, json& data) {
    Home home = {};

    CStatus status = Controller::fetchUserHome(svalue(data, KEY_EMAIL), home);

    return { CTOS(status), status == C_SUCCESS ?  homeToJson(home) : ""};
}

pair<SStatus, string> APIHandlers::fetchCharacters(const string&, json& data) {
    vector<Character> characters;

    CStatus status = Controller::fetchUserCharacters(svalue(data, KEY_EMAIL), characters);

    return { CTOS(status), status == C_SUCCESS ? charactersToJson(characters) : "" };
}

pair<SStatus, string> APIHandlers::fetchTransfers(const string&, json& data) {
    vector<Transfer> transfers;

    CStatus status = Controller::fetchTransfers(transfers);

    return { CTOS(status), status == C_SUCCESS ? transfersToJson(transfers) : "" };
}

// =============================================
// =============================================

// Put Handlers ================================
// =============================================
pair<SStatus, string> APIHandlers::updateHome(const string&, json& data) {
    CStatus status = Controller::updateUserHome(svalue(data, KEY_EMAIL),
                                                ivalue(data, KEY_ID),
                                                svalue(data, KEY_NAME));

    return { CTOS(status), "" };
}

pair<SStatus, string> APIHandlers::updateCharacter(const string&, json& data) {
    CStatus status = Controller::updateUserCharacter(svalue(data, KEY_EMAIL),
                                                     ivalue(data, KEY_ID),
                                                     svalue(data, KEY_FULLNAME),
                                                     svalue(data, KEY_NICKNAME));

    return { CTOS(status), "" };
}

pair<SStatus, string> APIHandlers::transferCharacter(const string&, json& data) {
    CStatus status = Controller::transferCharacter(svalue(data, KEY_EMAIL),
                                                   ivalue(data, KEY_CHARACTER_ID),
                                                   ivalue(data, KEY_HOME_ID));

    return { CTOS(status), "" };
}

// =============================================
// =============================================


// Utility functions ===========================
// =============================================
SStatus APIHandlers::CTOS(CStatus status) {
    switch (status) {
        case C_SUCCESS: return S_SUCCESS;
        case C_AUTH_ERROR: return S_AUTH_ERROR;

        default: return S_ERROR;
    }
}

string APIHandlers::tokenToJson(const string& token) {
    json tokenJSON;

    tokenJSON[KEY_TOKEN] = token;

    return tokenJSON.dump();
}

string APIHandlers::homeToJson(const Home& home) {
    json homeJSON;

    homeJSON[KEY_ID] = home.getID();
    homeJSON[KEY_NAME] = home.getName();
    homeJSON[KEY_SUGAR_CUBES] = home.getSugarCubes();

    return homeJSON.dump();
}

string APIHandlers::charactersToJson(const vector<Character>& characters) {
    json charactersJSON;
    json charactersArray;

    for (auto &character: characters) {
        json characterJSON;

        characterJSON[KEY_ID] = character.getID();
        characterJSON[KEY_FULLNAME] = character.getFullname();
        characterJSON[KEY_NICKNAME] = character.getNickname();
        characterJSON[KEY_AGE] = character.getAge();
        characterJSON[KEY_SPECIES] = character.getSpecies();

        charactersArray.push_back(characterJSON);
    }

    charactersJSON[KEY_LENGTH] = characters.size();
    charactersJSON[KEY_CHARACTERS] = charactersArray;

    return charactersJSON.dump();
}

string APIHandlers::transfersToJson(const vector<Transfer>& transfers) {
    json transfersJSON;
    json transfersArray;

    for (auto &transfer: transfers) {
        json transferJSON;

        transferJSON[KEY_ID] = transfer.getID();
        transferJSON[KEY_CHARACTER_ID] = transfer.getCharacterID();
        transferJSON[KEY_SUGAR_CUBES] = transfer.getSugarCubes();

        transfersArray.push_back(transferJSON);
    }

    transfersJSON[KEY_LENGTH] = transfers.size();
    transfersJSON[KEY_TRANSFERS] = transfersArray;

    return transfersJSON.dump();
}

int APIHandlers::ivalue(json& data, const string& key) {
    return data.value(key, KEY_DEFAULT_INT);
}

string APIHandlers::svalue(json& data, const string& key) {
    return data.value(key, KEY_DEFAULT);
}

// =============================================
// =============================================