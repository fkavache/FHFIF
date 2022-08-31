#include "CppUTest/TestHarness.h"
#include "dal/UserDal.h"
#undef _L

#define DB       "localhost@fhfif_test"
#define USER     "postgres"
#define PASSWORD "testpass"

#define USER_EMAIL    "email"
#define USER_PASSWORD "password"

TEST_GROUP(TEST_USER_DAL){
    void setup() {
        DAL::GetInstance()->connect(DB, USER, PASSWORD, SA_PostgreSQL_Client);
    }

    void teardown() {
        UserDAL::truncate();
        DAL::GetInstance()->commit();
        DAL::GetInstance()->disconnect();
    }
};

static User createUser(int id) {
    string sid = to_string(id);

    return {
        USER_EMAIL + sid,
        USER_PASSWORD + sid,
    };
}

static void checkUser(User &user, int id) {
    string sid = to_string(id);

    STRCMP_EQUAL((USER_EMAIL + sid).c_str(), user.getEMail().c_str())
    STRCMP_EQUAL((USER_PASSWORD + sid).c_str(), user.getPassword().c_str())
}

TEST(TEST_USER_DAL, TEST_SELECT_ALL) {
    {
        try {
            int id1 = 1;
            int id2 = 2;

            UserDAL::insert(createUser(id1));
            UserDAL::insert(createUser(id2));

            auto users = UserDAL::selectAll();
            LONGS_EQUAL(2, users.size())

            checkUser(users[0], id1);
            checkUser(users[1], id2);
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_USER_DAL, TEST_SELECT_BY_EMAIL) {
    {
        try {
            int id1 = 1;
            int id2 = 2;

            UserDAL::insert(createUser(id1));
            UserDAL::insert(createUser(id2));

            auto user1 = UserDAL::selectByEmail("email1");
            checkUser(user1, id1);

            auto user2 = UserDAL::selectByEmail("email2");
            checkUser(user2, id2);
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_USER_DAL, TEST_TRUNCATE) {
    {
        try {
            int id = 1;

            UserDAL::insert(createUser(id));
            UserDAL::insert(createUser(id));

            UserDAL::truncate();

            auto users = UserDAL::selectAll();
            LONGS_EQUAL(0, users.size())
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}