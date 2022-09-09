#include "api/APIServer.h"
#include "CppUTest/TestHarness.h"

#undef _L

// TODO: [vacheka] config
#define DB        "localhost@fhfif_test"
#define USER      "postgres"
#define PASSWORD  "testpass"
#define LOCALHOST "127.0.0.1"
#define PORT       8080

TEST_GROUP(TEST_APISERVER){
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

IGNORE_TEST(TEST_APISERVER, TEST_REGISTER_USER) {
    {
        APIServer::run(LOCALHOST, PORT);
    }
}
