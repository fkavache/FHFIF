#include "CppUTest/TestHarness.h"
#include "dal/TransferDal.h"
#undef _L

// TODO: [vacheka] config
#define DB       "localhost@fhfif_test"
#define USER     "postgres"
#define PASSWORD "testpass"

#define TRANSFER_CHARACTER_ID 11
#define TRANSFER_SUGAR_CUBES  111

TEST_GROUP(TEST_TRANSFER_DAL){
    void setup() {
        DAL::GetInstance()->connect(DB, USER, PASSWORD, SA_PostgreSQL_Client);
    }

    void teardown() {
        TransferDAL::truncate();
        DAL::GetInstance()->commit();
        DAL::GetInstance()->disconnect();
    }
};

static Transfer createTransfer(int id) {
    return {
        TRANSFER_CHARACTER_ID + id,
        TRANSFER_SUGAR_CUBES + id,
    };
}

static void checkTransfer(Transfer &transfer, int id) {
    LONGS_EQUAL(TRANSFER_CHARACTER_ID + id, transfer.getCharacterID())
    LONGS_EQUAL(TRANSFER_SUGAR_CUBES + id, transfer.getSugarCubes())
}


TEST(TEST_TRANSFER_DAL, TEST_SELECT_ALL) {
    {
        try {
            int id1 = 1;
            int id2 = 2;

            TransferDAL::insert(createTransfer(id1));
            TransferDAL::insert(createTransfer(id2));

            auto transfers = TransferDAL::selectAll();
            LONGS_EQUAL(2, transfers.size())

            checkTransfer(transfers[0], id1);
            checkTransfer(transfers[1], id2);
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_TRANSFER_DAL, TEST_SELECT_BY_CHARACTER_ID) {
    {
        try {
            int id1 = 1;
            int id2 = 2;

            TransferDAL::insert(createTransfer(id1));
            TransferDAL::insert(createTransfer(id2));

            auto transfer1 = TransferDAL::selectByCharacterID(12);
            checkTransfer(transfer1, id1);

            auto transfer2 = TransferDAL::selectByCharacterID(13);
            checkTransfer(transfer2, id2);
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}

TEST(TEST_TRANSFER_DAL, TEST_TRUNCATE) {
    {
        try {
            int id = 1;

            TransferDAL::insert(createTransfer(id));
            TransferDAL::insert(createTransfer(id));

            TransferDAL::truncate();

            auto transfers = TransferDAL::selectAll();
            LONGS_EQUAL(0, transfers.size())
        } catch (SAException& ex) {
            FAIL(ex.ErrText())
        }
    }
}
