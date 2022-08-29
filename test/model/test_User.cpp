#include "CppUTest/TestHarness.h"
#include "model/User.h"
#undef _L

TEST_GROUP(TEST_USER){};

#define USER_EMAIL    "email"
#define USER_PASSWORD "password"

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

static void updateUser(User &user, int id) {
    string sid = to_string(id);

    user.setEMail(USER_EMAIL + sid);
    user.setPassword(USER_PASSWORD + sid);
}

TEST(TEST_USER, TEST_CLASS) {
    {
        int OID = 11;
        int NID = 12;
        User user = createUser(OID);

        checkUser(user, OID);
        updateUser(user, NID);
        checkUser(user, NID);
    }
}
