#include "CppUTest/TestHarness.h"
#include "model/Home.h"
#undef _L

TEST_GROUP(TEST_HOME){};

#define HOME_NAME              "Foster's"
#define HOME_SUGAR_CUBES        100
#define HOME_SUGAR_CUBES_BUDGET 1000
#define BLOO_USER_ID            1

static Home createFostersHome(int id) {
    string sid = to_string(id);

    return {
            HOME_NAME + sid,
            HOME_SUGAR_CUBES + id,
            HOME_SUGAR_CUBES_BUDGET + id,
            BLOO_USER_ID + id
    };
}

static void checkFosters(Home &home, int id) {
    string sid = to_string(id);

    STRCMP_EQUAL((HOME_NAME + sid).c_str(), home.getName().c_str())

    LONGS_EQUAL(HOME_SUGAR_CUBES + id, home.getSugarCubes())
    LONGS_EQUAL(HOME_SUGAR_CUBES_BUDGET + id, home.getSugarCubesBudget())
    LONGS_EQUAL(BLOO_USER_ID + id, home.getUserID())
}

static void updateFosters(Home &home, int id) {
    string sid = to_string(id);

    home.setName(HOME_NAME + sid);
    home.setSugarCubes(HOME_SUGAR_CUBES + id);
    home.setSugarCubesBudget(HOME_SUGAR_CUBES_BUDGET + id);
    home.setUserID(BLOO_USER_ID + id);
}

TEST(TEST_HOME, TEST_CLASS) {
    {
        int OID = 11;
        int NID = 12;
        Home home = createFostersHome(OID);

        checkFosters(home, OID);
        updateFosters(home, NID);
        checkFosters(home, NID);
    }
}
