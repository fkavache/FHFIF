#include "dal/UserDal.h"

#define USER_INSERT_QUERY          "INSERT INTO users (e_mail, password) VALUES (:1, :2) RETURNING id"
#define USER_SELECT_QUERY          "SELECT * FROM users"
#define USER_SELECT_BY_EMAIL_QUERY "SELECT * FROM users WHERE e_mail = (:1)"

int UserDAL::insert(const User &user) {
    return DAL::GetInstance()->insert(USER_INSERT_QUERY, userToEntry(user));
}

vector<User> UserDAL::selectAll() {
    vector<User> result;

    auto entries = DAL::GetInstance()->select(USER_SELECT_QUERY);

    result.reserve(entries.size());
    for (auto& entry: entries) {
        result.push_back(entryToUser(entry));
    }

    return result;
}

User UserDAL::selectByEmail(const string& email) {
    auto entries = DAL::GetInstance()->select(USER_SELECT_BY_EMAIL_QUERY, {{ Field(email) }});

    if (entries.empty()) {
        DAL::GetInstance()->throwException("User not found");
    }

    return entryToUser(entries[0]);
}


Entry UserDAL::userToEntry(const User &user) {
    Entry entry = {
            {
                Field(user.getEMail()),
                Field(user.getPassword()),
            }
    };

    return entry;
}

User UserDAL::entryToUser(const Entry& entry) {
    User user(
            entry.fields[1].text,
            entry.fields[2].text
    );

    user.setID(entry.fields[0].numeric);

    return user;
}
