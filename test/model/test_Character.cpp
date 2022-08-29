#include "CppUTest/TestHarness.h"
#include "model/Character.h"
#undef _L

TEST_GROUP(TEST_CHARACTER){};

#define BLOO_NAME       "Blooregard Q. Kazoo"
#define BLOO_NICKNAME   "Bloo"
#define BLOO_AGE         20
#define BLOO_SUGAR_CUBES 100
#define BLOO_HOME        1
#define BLOO_SPECIES     CHARACTER_SPECIES_IMAGINARY_FRIEND

static Character createBloo(int id) {
    string sid = to_string(id);

    return {
        BLOO_NAME + sid,
        BLOO_NICKNAME + sid,
        BLOO_AGE + id,
        BLOO_SUGAR_CUBES + id,
        BLOO_HOME + id,
        BLOO_SPECIES
    };
}

static void checkBloo(Character &character, int id) {
    string sid = to_string(id);

    STRCMP_EQUAL((BLOO_NAME + sid).c_str(), character.getFullname().c_str())
    STRCMP_EQUAL((BLOO_NICKNAME + sid).c_str(), character.getNickname().c_str())

    LONGS_EQUAL(BLOO_AGE + id, character.getAge())
    LONGS_EQUAL(BLOO_SUGAR_CUBES + id, character.getSugarCubes())
    LONGS_EQUAL(BLOO_HOME + id, character.getHomeID())
    LONGS_EQUAL(BLOO_SPECIES, character.getSpecies())
}

static void updateBloo(Character &character, int id) {
    string sid = to_string(id);

    character.setFullname(BLOO_NAME + sid);
    character.setNickname(BLOO_NICKNAME + sid);
    character.setAge(BLOO_AGE + id);
    character.setSugarCubes(BLOO_SUGAR_CUBES + id);
    character.setHomeID(BLOO_HOME + id);
    character.setSpecies(BLOO_SPECIES);
}

TEST(TEST_CHARACTER, TEST_CLASS) {
    {
        int OID = 11;
        int NID = 12;
        Character character = createBloo(OID);

        checkBloo(character, OID);
        updateBloo(character, NID);
        checkBloo(character, NID);
    }
}