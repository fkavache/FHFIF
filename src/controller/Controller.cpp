#include "controller/Controller.h"
#include "controller/ControllerData.h"
#include "utils/Utils.h"
#include "utils/Log.h"

// Todo vacheka
#define CONTROLLER_UNIT "CONTROLLER"

#define JWT_PAYLOAD_EMAIL    "email"
#define JWT_PAYLOAD_PASSWORD "password"
#define JWT_LOGIN_EXPIRATION  30 * 60

#define CHARACTER_MIN_SUGAR_CUBES 100
#define CHARACTER_MAX_SUGAR_CUBES 10000

#define DEFAULT_HOME_NAME        "Foster's Home"
#define DEFAULT_HOME_SUGAR_CUBES  20000000

#define CHARACTER_MIN_SUGAR_INC 10
#define CHARACTER_MAX_SUGAR_INC 100

void Controller::createCharacters(int homeID, int N) {
    vector<Character> characterData = ControllerData::getCharacterData();

    while (N--) {
        int idx = Utils::getRandom(0, (int) characterData.size() - 1);
        int sugarCubes = Utils::getRandom(CHARACTER_MIN_SUGAR_CUBES, CHARACTER_MAX_SUGAR_CUBES);

        Character character = characterData[idx];
        character.setSugarCubes(sugarCubes);
        character.setHomeID(homeID);

        CharacterDAL::insert(character);
    }
}

bool Controller::isAuthorized(const string& token, string& email) {
    try {
        bool claims = Utils::JWTCheck(token, {JWT_PAYLOAD_EMAIL, JWT_PAYLOAD_PASSWORD});
        if (claims) {
            string pEmail = Utils::JWTGetClaim(token, JWT_PAYLOAD_EMAIL);
            string pPassword = Utils::JWTGetClaim(token, JWT_PAYLOAD_PASSWORD);

            User user = UserDAL::selectByEmail(pEmail);

            email = pEmail;

            return user.getPassword() == Utils::hash(pPassword);
        }

        return false;
    } catch (SAException& ex) {
        Log::LOG_ERROR(CONTROLLER_UNIT, (string) ex.ErrText());
        return false;
    }
}

CStatus Controller::registerUser(string&& email, string&& password, string& token) {
    try {
        int userID = UserDAL::insert({email, Utils::hash(password)});

        int homeID = HomeDAL::insert(
                {
                    DEFAULT_HOME_NAME + to_string(userID),
                    DEFAULT_HOME_SUGAR_CUBES,
                    userID
                });

        createCharacters(homeID, 5);

        DAL::GetInstance()->commit();

        unordered_map<string, string> payload({
            {JWT_PAYLOAD_EMAIL,    email},
            {JWT_PAYLOAD_PASSWORD, password}
        });

        token = Utils::JWTEncode(payload, JWT_LOGIN_EXPIRATION);

        return C_SUCCESS;
    } catch (SAException& ex) {
        Log::LOG_ERROR(CONTROLLER_UNIT, (string) ex.ErrText());
        DAL::GetInstance()->rollback();
        return C_ERROR;
    }
}

CStatus Controller::loginUser(string&& email, string&& password, string& token) {
    try {
        User user = UserDAL::selectByEmail(email);

        if (user.getPassword() == Utils::hash(password)) {
            unordered_map<string, string> payload({
                {JWT_PAYLOAD_EMAIL, email},
                {JWT_PAYLOAD_PASSWORD, password}
            });

            token = Utils::JWTEncode(payload, JWT_LOGIN_EXPIRATION);

            return C_SUCCESS;
        }

        return C_AUTH_ERROR;
    } catch (SAException& ex) {
        Log::LOG_ERROR(CONTROLLER_UNIT, (string) ex.ErrText());
        DAL::GetInstance()->rollback();
        return C_ERROR;
    }
}

CStatus Controller::fetchUserHome(std::string &&email, Home &out) {
    try {
        User user = UserDAL::selectByEmail(email);

        out = HomeDAL::selectByUserID(user.getID());

        return C_SUCCESS;
    } catch (SAException& ex) {
        Log::LOG_ERROR(CONTROLLER_UNIT, (string) ex.ErrText());
        return C_ERROR;
    }
}

CStatus Controller::fetchUserCharacters(string&& email, vector<Character>& out) {
    try {
        User user = UserDAL::selectByEmail(email);
        Home home = HomeDAL::selectByUserID(user.getID());

        out = CharacterDAL::selectByHomeID(home.getID());

        return C_SUCCESS;
    } catch (SAException& ex) {
        Log::LOG_ERROR(CONTROLLER_UNIT, (string) ex.ErrText());
        return C_ERROR;
    }
}

CStatus Controller::updateUserHome(string&& email, int id, string&& name) {
    try {
        User user = UserDAL::selectByEmail(email);
        Home home = HomeDAL::selectByID(id);

        if (home.getUserID() == user.getID()) {
            HomeDAL::updateName(id, name);

            DAL::GetInstance()->commit();

            return C_SUCCESS;
        }

        return C_AUTH_ERROR;
    } catch (SAException& ex) {
        Log::LOG_ERROR(CONTROLLER_UNIT, (string) ex.ErrText());
        DAL::GetInstance()->rollback();
        return C_ERROR;
    }
}

CStatus Controller::updateUserCharacter(string&& email, int id, string&& fullname, string&& nickname) {
    try {
        User user = UserDAL::selectByEmail(email);
        Home home = HomeDAL::selectByUserID(user.getID());
        Character character = CharacterDAL::selectByID(id);

        if (character.getHomeID() == home.getID()) {
            character.setFullname(std::move(fullname));
            character.setNickname(std::move(nickname));

            CharacterDAL::update(id, character);

            DAL::GetInstance()->commit();

            return C_SUCCESS;
        }

        return C_AUTH_ERROR;
    } catch (SAException& ex) {
        Log::LOG_ERROR(CONTROLLER_UNIT, (string) ex.ErrText());
        DAL::GetInstance()->rollback();
        return C_ERROR;
    }
}

CStatus Controller::characterToTransferList(string&& email, int id) {
    try {
        User user = UserDAL::selectByEmail(email);
        Home home = HomeDAL::selectByUserID(user.getID());
        Character character = CharacterDAL::selectByID(id);

        if (character.getHomeID() == home.getID()) {
            TransferDAL::insert({id, character.getSugarCubes()});

            DAL::GetInstance()->commit();

            return C_SUCCESS;
        }

        return C_AUTH_ERROR;
    } catch (SAException& ex) {
        Log::LOG_ERROR(CONTROLLER_UNIT, (string) ex.ErrText());
        DAL::GetInstance()->rollback();
        return C_ERROR;
    }
}

CStatus Controller::fetchTransfers(vector<Transfer>& out) {
    try {
        out = TransferDAL::selectAll();

        return C_SUCCESS;
    } catch (SAException& ex) {
        Log::LOG_ERROR(CONTROLLER_UNIT, (string) ex.ErrText());
        return C_ERROR;
    }
}

CStatus Controller::transferCharacter(string&& email, int characterID, int newHomeID) {
    try {
        User user = UserDAL::selectByEmail(email);
        Home home = HomeDAL::selectByUserID(user.getID());

        if (home.getID() == newHomeID) {
            Transfer transfer = TransferDAL::selectByCharacterID(characterID);
            Character character = CharacterDAL::selectByID(characterID);
            Home oldHome = HomeDAL::selectByID(character.getHomeID());
            Home newHome = HomeDAL::selectByID(newHomeID);

            HomeDAL::updateSugarCubes(oldHome.getID(), oldHome.getSugarCubes() + character.getSugarCubes());

            int increase = Utils::getRandom(CHARACTER_MIN_SUGAR_INC, CHARACTER_MAX_SUGAR_INC);
            int newSugarCubes = character.getSugarCubes() + character.getSugarCubes() * increase / 100;
            CharacterDAL::updateHome(characterID, newHomeID);
            CharacterDAL::updateSugarCubes(characterID, newSugarCubes);

            HomeDAL::updateSugarCubes(newHome.getID(), newHome.getSugarCubes() - character.getSugarCubes());

            TransferDAL::removeByCharacterID(characterID);

            DAL::GetInstance()->commit();

            (void) transfer;

            return C_SUCCESS;
        }

        return C_AUTH_ERROR;
    } catch (SAException& ex) {
        Log::LOG_ERROR(CONTROLLER_UNIT, (string) ex.ErrText());
        DAL::GetInstance()->rollback();
        return C_ERROR;
    }
}