#include "dal/HomeDal.h"

#define HOME_INSERT_QUERY             "INSERT INTO homes (name, sugar_cubes, user_id) VALUES (:1, :2, :3) RETURNING id"
#define HOME_SELECT_QUERY             "SELECT * FROM homes"
#define HOME_SELECT_BY_USER_QUERY     "SELECT * FROM homes WHERE user_id = (:1)"
#define HOME_SELECT_BY_ID_QUERY       "SELECT * FROM homes WHERE id = (:1)"
#define HOME_UPDATE_NAME_QUERY        "UPDATE homes SET name = (:1) WHERE id = (:2)"
#define HOME_UPDATE_SUGAR_CUBES_QUERY "UPDATE homes SET sugar_cubes = (:1) WHERE id = (:2)"
#define HOME_TRUNCATE_QUERY           "TRUNCATE TABLE homes RESTART IDENTITY CASCADE"

int HomeDAL::insert(const Home &home) {
    return DAL::GetInstance()->insert(HOME_INSERT_QUERY, homeToEntry(home));
}

vector<Home> HomeDAL::selectAll() {
    vector<Home> result;

    auto entries = DAL::GetInstance()->select(HOME_SELECT_QUERY);

    result.reserve(entries.size());
    for (auto& entry: entries) {
        result.push_back(entryToHome(entry));
    }

    return result;
}

Home HomeDAL::selectByUserID(int userId) {
    auto entries = DAL::GetInstance()->select(HOME_SELECT_BY_USER_QUERY, {{ Field(userId) }});

    if (entries.empty()) {
        DAL::GetInstance()->throwException("Home not found");
    }

    return entryToHome(entries[0]);
}

Home HomeDAL::selectByID(int id) {
    auto entries = DAL::GetInstance()->select(HOME_SELECT_BY_ID_QUERY, {{ Field(id) }});

    if (entries.empty()) {
        DAL::GetInstance()->throwException("Home not found");
    }

    return entryToHome(entries[0]);
}

Entry HomeDAL::homeToEntry(const Home &home) {
    Entry entry = {
            {
                Field(home.getName()),
                Field(home.getSugarCubes()),
                Field(home.getUserID()),
            }
    };

    return entry;
}

Home HomeDAL::entryToHome(const Entry& entry) {
    Home home(
            entry.fields[1].text,
            entry.fields[2].numeric,
            entry.fields[3].numeric
    );

    home.setID(entry.fields[0].numeric);

    return home;
}

void HomeDAL::updateName(int id, const string& name) {
    DAL::GetInstance()->update(HOME_UPDATE_NAME_QUERY, {
            {
                    Field(name),
                    Field(id)
            }
    });
}

void HomeDAL::updateSugarCubes(int id, int sugarCubes) {
    DAL::GetInstance()->update(HOME_UPDATE_SUGAR_CUBES_QUERY, {
            {
                    Field(sugarCubes),
                    Field(id)
            }
    });
}

void HomeDAL::truncate() {
    DAL::GetInstance()->truncate(HOME_TRUNCATE_QUERY);
}