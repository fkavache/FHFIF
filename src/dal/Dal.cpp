#include "dal/Dal.h"

DAL* DAL::m_dal = nullptr;

DAL::DAL() = default;

void DAL::connect(string&& sDBString, string&& sUserID, string&& sPassword, SAClient_t eSAClient) {
    m_con.Connect(_TSA(sDBString.c_str()), _TSA(sUserID.c_str()), _TSA(sPassword.c_str()), eSAClient);
    m_con.setAutoCommit(SA_AutoCommitOff);
}

void DAL::entryToCommand(SACommand& command, const Entry& entry) {
    for (const Field& field: entry.fields) {
        if (field.type == FIELD_TYPE_NUMERIC) {
            command << (long) field.numeric;
        } else if (field.type == FIELD_TYPE_TEXT) {
            command << _TSA(field.text.c_str());
        }
    }
}

int DAL::insert(string&& cmd, const DAL::Entry &entry) {
    SACommand insert(&m_con, _TSA(cmd.c_str()));

    entryToCommand(insert, entry);

    insert.Execute();
    insert.FetchNext();

    return insert[1].asLong();
}

vector<DAL::Entry> DAL::select(string&& cmd, const Entry &entry) {
    vector<Entry> result;

    SACommand select(&m_con, _TSA(cmd.c_str()));

    entryToCommand(select, entry);

    select.Execute();
    int fieldCount = select.FieldCount();

    result.reserve(fieldCount);
    while(select.FetchNext()) {
        Entry nEntry = {};

        for (int i = 1; i <= fieldCount; i++) {
            SADataType_t type = select[i].FieldType();

            if (type == SA_dtLong) {
                nEntry.fields.emplace_back(select[i].asLong());
            } else if (type == SA_dtLongChar) {
                nEntry.fields.emplace_back((string) select[i].asString());
            }
        }

        result.push_back(nEntry);
    }

    return result;
}

void DAL::update(string&& cmd, const DAL::Entry &entry) {
    SACommand update(&m_con, _TSA(cmd.c_str()));

    entryToCommand(update, entry);

    update.Execute();
}

void DAL::remove(string&& cmd, const DAL::Entry &entry) {
    SACommand remove(&m_con, _TSA(cmd.c_str()));

    entryToCommand(remove, entry);

    remove.Execute();
}

void DAL::commit() {
    m_con.Commit();
}

void DAL::rollback() {
    m_con.Rollback();
}

void DAL::disconnect() {
    m_con.Disconnect();
    delete m_dal;
}

void DAL::throwException(const string& msg) {
    throw SAException(SA_UserGenerated_Error, 1, 1, _TSA(msg.c_str()));
}

DAL *DAL::GetInstance() {
    if (!m_dal) {
        m_dal = new DAL();
    }

    return m_dal;
}

