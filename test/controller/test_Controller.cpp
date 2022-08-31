#include "controller/Controller.h"
#include "utils/Utils.h"
#include "CppUTest/TestHarness.h"

#undef _L

#define DB       "localhost@fhfif_test"
#define USER     "postgres"
#define PASSWORD "testpass"

#define USER_EMAIL    "email"
#define USER_PASSWORD "password"
#define INCORRECT     "incorrect"

TEST_GROUP(TEST_CONTROLLER){
    void setup() {
        DAL::GetInstance()->connect(DB, USER, PASSWORD, SA_PostgreSQL_Client);
    }

    void teardown() {
        CharacterDAL::truncate();
        TransferDAL::truncate();
        HomeDAL::truncate();
        UserDAL::truncate();
        DAL::GetInstance()->commit();
        DAL::GetInstance()->disconnect();
    }
};

TEST(TEST_CONTROLLER, TEST_REGISTER_USER) {
    {
        try {
            string token;
            string email = USER_EMAIL;
            string password = Utils::hash(USER_PASSWORD);

            CStatus status = Controller::registerUser(USER_EMAIL, USER_PASSWORD, token);
            LONGS_EQUAL(C_SUCCESS, status)

            CHECK(Controller::isAuthorized(token, email))

            auto users = UserDAL::selectAll();
            LONGS_EQUAL(1, users.size())
            STRCMP_EQUAL(email.c_str(), (users[0].getEMail()).c_str())
            STRCMP_EQUAL(password.c_str(), (users[0].getPassword()).c_str())

            auto homes = HomeDAL::selectAll();
            LONGS_EQUAL(1, homes.size())
            LONGS_EQUAL(users[0].getID(), homes[0].getUserID())

            auto characters = CharacterDAL::selectAll();
            LONGS_EQUAL(5, characters.size())

            for (const auto &character: characters) {
                LONGS_EQUAL(homes[0].getID(), character.getHomeID())
            }
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_CONTROLLER, TEST_LOGIN_USER) {
    {
        try {
            string token;
            string email = USER_EMAIL;
            string password = USER_PASSWORD;
            CStatus status;

            status = Controller::registerUser(USER_EMAIL, USER_PASSWORD, token);
            LONGS_EQUAL(C_SUCCESS, status)

            status = Controller::loginUser(USER_EMAIL, USER_PASSWORD, token);
            LONGS_EQUAL(C_SUCCESS, status)

            status = Controller::loginUser(USER_EMAIL, INCORRECT, token);
            LONGS_EQUAL(C_AUTH_ERROR, status)
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_CONTROLLER, TEST_FETCH_HOME) {
    {
        try {
            string token;
            string email = USER_EMAIL;
            string password = USER_PASSWORD;
            Home home;
            CStatus status;

            status = Controller::registerUser(USER_EMAIL, USER_PASSWORD, token);
            LONGS_EQUAL(C_SUCCESS, status)

            status = Controller::fetchUserHome(USER_EMAIL, home);
            LONGS_EQUAL(C_SUCCESS, status)

            auto user = UserDAL::selectByEmail(USER_EMAIL);
            LONGS_EQUAL(user.getID(), home.getUserID())
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_CONTROLLER, TEST_FETCH_CHARACTERS) {
    {
        try {
            string token;
            string email = USER_EMAIL;
            string password = USER_PASSWORD;
            vector<Character> characters;
            CStatus status;

            status = Controller::registerUser(USER_EMAIL, USER_PASSWORD, token);
            LONGS_EQUAL(C_SUCCESS, status)

            status = Controller::fetchUserCharacters(USER_EMAIL, characters);
            LONGS_EQUAL(C_SUCCESS, status)

            auto user = UserDAL::selectByEmail(USER_EMAIL);
            auto home = HomeDAL::selectByUserID(user.getID());

            for (auto &character: characters) {
                LONGS_EQUAL(home.getID(), character.getHomeID())
            }
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_CONTROLLER, TEST_UPDATE_HOME) {
    {
        try {
            int homeID = 1;
            string newName = "Ben Foster's";

            string token;
            string email = USER_EMAIL;
            string password = USER_PASSWORD;
            vector<Character> characters;
            CStatus status;

            status = Controller::registerUser(USER_EMAIL, USER_PASSWORD, token);
            LONGS_EQUAL(C_SUCCESS, status)

            status = Controller::updateUserHome(USER_EMAIL, homeID, newName.c_str());
            LONGS_EQUAL(C_SUCCESS, status)

            auto home = HomeDAL::selectByID(homeID);
            STRCMP_EQUAL(newName.c_str(), home.getName().c_str())
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_CONTROLLER, TEST_UPDATE_CHARACTER) {
    {
        try {
            int characterID = 1;
            string newFullname = "Jackie Khones";
            string newNickname = "The Talking Broccoli";

            string token;
            string email = USER_EMAIL;
            string password = USER_PASSWORD;
            vector<Character> characters;
            CStatus status;

            status = Controller::registerUser(USER_EMAIL, USER_PASSWORD, token);
            LONGS_EQUAL(C_SUCCESS, status)

            status = Controller::updateUserCharacter(USER_EMAIL, characterID, newFullname.c_str(), newNickname.c_str());
            LONGS_EQUAL(C_SUCCESS, status)

            auto character = CharacterDAL::selectByID(characterID);
            STRCMP_EQUAL(newFullname.c_str(), character.getFullname().c_str())
            STRCMP_EQUAL(newNickname.c_str(), character.getNickname().c_str())
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}