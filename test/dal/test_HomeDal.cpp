#include "CppUTest/TestHarness.h"
#include "dal/HomeDal.h"
#undef _L

#define DB       "localhost@fhfif_test"
#define USER     "postgres"
#define PASSWORD "testpass"

#define HOME_NAME       "Foster's"
#define HOME_SUGAR_CUBES 100
#define HOME_USER_ID     1

TEST_GROUP(TEST_HOME_DAL){
    void setup() {
        DAL::GetInstance()->connect(DB, USER, PASSWORD, SA_PostgreSQL_Client);
    }

    void teardown() {
        DAL::GetInstance()->rollback();
        DAL::GetInstance()->disconnect();
    }
};

static Home createFosters(int id) {
    string sid = to_string(id);

    return {
        HOME_NAME + sid,
        HOME_SUGAR_CUBES + id,
        HOME_USER_ID + id
    };
}

static void checkFosters(Home &home, int id) {
    string sid = to_string(id);

    STRCMP_EQUAL((HOME_NAME + sid).c_str(), home.getName().c_str())

    LONGS_EQUAL(HOME_SUGAR_CUBES + id, home.getSugarCubes())
    LONGS_EQUAL(HOME_USER_ID + id, home.getUserID())
}

TEST(TEST_HOME_DAL, TEST_SELECT_ALL) {
    {
        try {
            int id1 = 1;
            int id2 = 2;

            HomeDAL::insert(createFosters(id1));
            HomeDAL::insert(createFosters(id2));

            auto homes = HomeDAL::selectAll();
            LONGS_EQUAL(2, homes.size())

            checkFosters(homes[0], id1);
            checkFosters(homes[1], id2);
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_HOME_DAL, TEST_SELECT_BY_ID) {
    {
        try {
            int id1 = 1;
            int id2 = 2;

            int retID1 = HomeDAL::insert(createFosters(id1));
            int retID2 = HomeDAL::insert(createFosters(id2));

            auto home1 = HomeDAL::selectByID(retID1);
            checkFosters(home1, id1);

            auto home2 = HomeDAL::selectByID(retID2);
            checkFosters(home2, id2);
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_HOME_DAL, TEST_SELECT_BY_USER_ID) {
    {
        try {
            int id1 = 1;
            int id2 = 2;

            HomeDAL::insert(createFosters(id1));
            HomeDAL::insert(createFosters(id2));

            auto home1 = HomeDAL::selectByUserID(HOME_USER_ID + id1);
            checkFosters(home1, id1);

            auto home2 = HomeDAL::selectByUserID(HOME_USER_ID + id2);
            checkFosters(home2, id2);
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_HOME_DAL, TEST_UPDATE_NAME) {
    {
        try {
            int id = 1;
            string name = "TEST";

            int retID = HomeDAL::insert(createFosters(id));

            HomeDAL::updateName(retID, name);

            auto home = HomeDAL::selectByID(retID);

            STRCMP_EQUAL(name.c_str(), home.getName().c_str())
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_HOME_DAL, TEST_UPDATE_SUGAR_CUBES) {
    {
        try {
            int id = 1;
            int sugarCubes = 700;

            int retID = HomeDAL::insert(createFosters(id));

            HomeDAL::updateSugarCubes(retID, sugarCubes);

            auto home = HomeDAL::selectByID(retID);

            LONGS_EQUAL(sugarCubes, home.getSugarCubes())
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}
