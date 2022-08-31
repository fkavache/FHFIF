#pragma once

#include <iostream>
#include "Dal.h"
#include "model/Transfer.h"

typedef DAL::Entry Entry;
typedef DAL::Field Field;

class TransferDAL {
private:
    static Entry transferToEntry(const Transfer& transfer);
    static Transfer entryToTransfer(const Entry& entry);

public:
    static int insert(const Transfer& transfer);
    static vector<Transfer> selectAll();
    static Transfer selectByCharacterID(int characterId);
    static void removeByCharacterID(int characterId);
    static void truncate();
};