#include "CppUTest/TestHarness.h"
#include "model/Transfer.h"
#undef _L

TEST_GROUP(TEST_TRANSFER){};

#define TRANSFER_CHARACTER_ID 11
#define TRANSFER_SUGAR_CUBES  111

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

static void updateTransfer(Transfer &transfer, int id) {
    transfer.setCharacterID(TRANSFER_CHARACTER_ID + id);
    transfer.setSugarCubes(TRANSFER_SUGAR_CUBES + id);
}

TEST(TEST_TRANSFER, TEST_CLASS) {
    {
        int OID = 11;
        int NID = 12;
        Transfer transfer = createTransfer(OID);

        checkTransfer(transfer, OID);
        updateTransfer(transfer, NID);
        checkTransfer(transfer, NID);
    }
}
