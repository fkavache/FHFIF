#include "dal/TransferDal.h"

#define TRANSFER_INSERT_QUERY           "INSERT INTO transfers (character_id, sugar_cubes) VALUES (:1, :2) RETURNING id"
#define TRANSFER_SELECT_QUERY           "SELECT * FROM transfers"
#define TRANSFER_SELECT_BY_PLAYER_QUERY "SELECT * FROM transfers WHERE character_id = (:1)"
#define TRANSFER_REMOVE_BY_PLAYER_QUERY "DELETE FROM transfers WHERE character_id = (:1)"
#define TRANSFER_TRUNCATE_QUERY         "TRUNCATE TABLE transfers RESTART IDENTITY CASCADE"

int TransferDAL::insert(const Transfer &transfer) {
    return DAL::GetInstance()->insert(TRANSFER_INSERT_QUERY, transferToEntry(transfer));
}

vector<Transfer> TransferDAL::selectAll() {
    vector<Transfer> result;

    auto entries = DAL::GetInstance()->select(TRANSFER_SELECT_QUERY);

    result.reserve(entries.size());
    for (auto& entry: entries) {
        result.push_back(entryToTransfer(entry));
    }

    return result;
}

Transfer TransferDAL::selectByCharacterID(int characterId) {
    auto entries = DAL::GetInstance()->select(TRANSFER_SELECT_BY_PLAYER_QUERY, {{ Field(characterId) }});

    if (entries.empty()) {
        DAL::GetInstance()->throwException("Transfer not found");
    }

    return entryToTransfer(entries[0]);
}

void TransferDAL::removeByCharacterID(int characterId) {
    DAL::GetInstance()->remove(TRANSFER_REMOVE_BY_PLAYER_QUERY, {{ Field(characterId) }});
}

Entry TransferDAL::transferToEntry(const Transfer &transfer) {
    Entry entry = {
            {
                Field(transfer.getCharacterID()),
                Field(transfer.getSugarCubes()),
            }
    };

    return entry;
}

Transfer TransferDAL::entryToTransfer(const Entry& entry) {
    Transfer transfer(
            entry.fields[1].numeric,
            entry.fields[2].numeric
    );

    transfer.setID(entry.fields[0].numeric);

    return transfer;
}

void TransferDAL::truncate() {
    DAL::GetInstance()->truncate(TRANSFER_TRUNCATE_QUERY);
}