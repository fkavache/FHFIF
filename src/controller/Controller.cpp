#include "controller/Controller.h"
#include "controller/ControllerData.h"
#include "utils/Utils.h"
#include "utils/Log.h"

// Todo vacheka
#define CONTROLLER_UNIT "CONTROLLER"

#define JWT_PAYLOAD_EMAIL    "email"
#define JWT_PAYLOAD_PASSWORD "password"
#define JWT_LOGIN_EXPIRATION  30 * 60

#define PLAYER_MIN_SUGAR_CUBES 100
#define PLAYER_MAX_SUGAR_CUBES 10000

#define DEFAULT_HOME_NAME        "Foster's Home"
#define DEFAULT_HOME_SUGAR_CUBES  20000000

void Controller::createCharacters(int homeID, int N) {
    vector<Character> characterData = ControllerData::getCharacterData();

    while (N--) {
        int idx = Utils::getRandom(0, (int) characterData.size() - 1);
        int sugarCubes = Utils::getRandom(PLAYER_MIN_SUGAR_CUBES, PLAYER_MAX_SUGAR_CUBES);

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