#include "CppUTest/TestHarness.h"
#include "dal/Dal.h"
#undef _L

#define DB       "localhost@fhfif_test"
#define USER     "postgres"
#define PASSWORD "testpass"

TEST_GROUP(TEST_DAL){};

TEST(TEST_DAL, TEST_CONNECT) {
    {
        try {
            DAL::GetInstance()->connect(DB, USER, PASSWORD, SA_PostgreSQL_Client);
            DAL::GetInstance()->disconnect();
        } catch (SAException& ex) {
            FAIL("Connection Failed")
        }
    }
}

TEST(TEST_DAL, TEST_EXCEPTION) {
    {
        try {
            DAL::GetInstance()->connect(DB, USER, PASSWORD, SA_PostgreSQL_Client);
            DAL::GetInstance()->throwException("EXCEPTION");
            DAL::GetInstance()->disconnect();
        } catch (SAException& ex) {
            STRCMP_EQUAL("EXCEPTION", ex.ErrText())
        }
    }
}