#pragma once

#include <iostream>
#include <vector>
#include "SQLAPI/SQLAPI.h"

using namespace std;

class DAL {
private:
    SAConnection m_con;

protected:
    DAL();
    static DAL* m_dal;

public:
    enum FieldType {
        FIELD_TYPE_NUMERIC,
        FIELD_TYPE_TEXT
    };

    struct Field {
        FieldType type;
        int numeric;
        string text;

        Field(int numeric) : type(FIELD_TYPE_NUMERIC), numeric(numeric) {}
        Field(string text) : type(FIELD_TYPE_TEXT), text(std::move(text)) {}
    };

    struct Entry {
        vector<Field> fields;
    };

    DAL(const DAL& other) = delete;
    void operator=(const DAL&) = delete;

    static DAL *GetInstance();
    void connect(string&& sDBString, string&& sUserID, string&& sPassword, SAClient_t eSAClient);
    int insert(string&& cmd, const Entry &entry);
    vector<Entry> select(string&& cmd, const Entry &entry = {});
    void update(string&& cmd, const DAL::Entry &entry);
    void remove(string&& cmd, const DAL::Entry &entry);
    void commit();
    void rollback();
    void disconnect();
    void throwException(const string& msg);

private:
    void entryToCommand(SACommand& command, const Entry& entry);
};