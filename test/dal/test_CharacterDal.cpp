#include "CppUTest/TestHarness.h"
#include "dal/CharacterDal.h"
#undef _L

#define DB       "localhost@fhfif_test"
#define USER     "postgres"
#define PASSWORD "testpass"

#define BLOO_NAME      "Blooregard Q. Kazoo"
#define BLOO_NICKNAME  "Bloo"
#define BLOO_AGE        20
#define BLOO_SUGARCUBES 100
#define BLOO_HOME       1
#define BLOO_SPECIES    CHARACTER_SPECIES_IMAGINARY_FRIEND

TEST_GROUP(TEST_CHARACTER_DAL){
    void setup() {
        DAL::GetInstance()->connect(DB, USER, PASSWORD, SA_PostgreSQL_Client);
    }

    void teardown() {
        DAL::GetInstance()->rollback();
        DAL::GetInstance()->disconnect();
    }
};

static Character createBloo(int id) {
    string sid = to_string(id);

    return {
            BLOO_NAME + sid,
            BLOO_NICKNAME + sid,
            BLOO_AGE + id,
            BLOO_SUGARCUBES + id,
            BLOO_HOME + id,
            BLOO_SPECIES
    };
}

static void checkBloo(Character &character, int id) {
    string sid = to_string(id);

    STRCMP_EQUAL((BLOO_NAME + sid).c_str(), character.getFullname().c_str())
    STRCMP_EQUAL((BLOO_NICKNAME + sid).c_str(), character.getNickname().c_str())

    LONGS_EQUAL(BLOO_AGE + id, character.getAge())
    LONGS_EQUAL(BLOO_SUGARCUBES + id, character.getSugarCubes())
    LONGS_EQUAL(BLOO_HOME + id, character.getHomeID())
    LONGS_EQUAL(BLOO_SPECIES, character.getSpecies())
}

TEST(TEST_CHARACTER_DAL, TEST_SELECT_ALL) {
    {
        try {
            int id1 = 1;
            int id2 = 2;

            CharacterDAL::insert(createBloo(id1));
            CharacterDAL::insert(createBloo(id2));

            auto characters = CharacterDAL::selectAll();
            LONGS_EQUAL(2, characters.size())

            checkBloo(characters[0], id1);
            checkBloo(characters[1], id2);
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_CHARACTER_DAL, TEST_SELECT_BY_ID) {
    {
        try {
            int id1 = 1;
            int id2 = 2;

            int retID1 = CharacterDAL::insert(createBloo(id1));
            int retID2 = CharacterDAL::insert(createBloo(id2));

            auto character1 = CharacterDAL::selectByID(retID1);
            checkBloo(character1, id1);

            auto character2 = CharacterDAL::selectByID(retID2);
            checkBloo(character2, id2);
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_CHARACTER_DAL, TEST_SELECT_BY_HOME_ID) {
    {
        try {
            int id1 = 1;
            int id2 = 2;

            CharacterDAL::insert(createBloo(id1));
            CharacterDAL::insert(createBloo(id2));

            auto characters1 = CharacterDAL::selectByHomeID(BLOO_HOME + id1);
            LONGS_EQUAL(1, characters1.size())
            checkBloo(characters1[0], id1);

            auto characters2 = CharacterDAL::selectByHomeID(BLOO_HOME + id2);
            LONGS_EQUAL(1, characters2.size())
            checkBloo(characters2[0], id2);
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_CHARACTER_DAL, TEST_UPDATE) {
    {
        try {
            int id1 = 1;
            int id2 = 2;
            string sid2 = to_string(id2);

            int retID = CharacterDAL::insert(createBloo(id1));

            CharacterDAL::update(retID, createBloo(id2));

            auto character = CharacterDAL::selectByID(retID);

            STRCMP_EQUAL((BLOO_NAME + sid2).c_str(), character.getFullname().c_str())
            STRCMP_EQUAL((BLOO_NICKNAME + sid2).c_str(), character.getNickname().c_str())

            LONGS_EQUAL(BLOO_AGE + id1, character.getAge())
            LONGS_EQUAL(BLOO_SUGARCUBES + id1, character.getSugarCubes())
            LONGS_EQUAL(BLOO_HOME + id1, character.getHomeID())
            LONGS_EQUAL(BLOO_SPECIES, character.getSpecies())
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_CHARACTER_DAL, TEST_UPDATE_HOME) {
    {
        try {
            int id = 1;
            int homeID = 7;

            int retID = CharacterDAL::insert(createBloo(id));

            CharacterDAL::updateHome(retID, homeID);

            auto character = CharacterDAL::selectByID(retID);

            LONGS_EQUAL(homeID, character.getHomeID())
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_CHARACTER_DAL, TEST_UPDATE_SUGAR_CUBES) {
    {
        try {
            int id = 1;
            int sugarCubes = 700;

            int retID = CharacterDAL::insert(createBloo(id));

            CharacterDAL::updateSugarCubes(retID, sugarCubes);

            auto character = CharacterDAL::selectByID(retID);

            LONGS_EQUAL(sugarCubes, character.getSugarCubes())
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}