#include "dal/CharacterDal.h"

#define CHARACTER_INSERT_QUERY             "INSERT INTO characters (fullname, nickname, age, sugar_cubes, home_id, species) VALUES (:1, :2, :3, :4, :5, :6) RETURNING id"
#define CHARACTER_SELECT_QUERY             "SELECT * FROM characters"
#define CHARACTER_SELECT_BY_TEAM_QUERY     "SELECT * FROM characters WHERE home_id = (:1)"
#define CHARACTER_SELECT_BY_ID_QUERY       "SELECT * FROM characters WHERE id = (:1)"
#define CHARACTER_UPDATE_QUERY             "UPDATE characters SET fullname = (:1), nickname = (:2) WHERE id = (:3)"
#define CHARACTER_UPDATE_HOME_QUERY        "UPDATE characters SET home_id = (:1) WHERE id = (:2)"
#define CHARACTER_UPDATE_SUGAR_CUBES_QUERY "UPDATE characters SET sugar_cubes = (:1) WHERE id = (:2)"
#define CHARACTER_TRUNCATE_QUERY           "TRUNCATE TABLE characters RESTART IDENTITY CASCADE"

int CharacterDAL::insert(const Character &character) {
    return DAL::GetInstance()->insert(CHARACTER_INSERT_QUERY, characterToEntry(character));
}

vector<Character> CharacterDAL::selectAll() {
    vector<Character> result;

    auto entries = DAL::GetInstance()->select(CHARACTER_SELECT_QUERY);

    result.reserve(entries.size());
    for (auto& entry: entries) {
        result.push_back(entryToCharacter(entry));
    }

    return result;
}

vector<Character> CharacterDAL::selectByHomeID(int homeId) {
    vector<Character> result;

    auto entries = DAL::GetInstance()->select(CHARACTER_SELECT_BY_TEAM_QUERY, {{ Field(homeId) }});

    result.reserve(entries.size());
    for (auto& entry: entries) {
        result.push_back(entryToCharacter(entry));
    }

    return result;
}

Character CharacterDAL::selectByID(int id) {
    auto entries = DAL::GetInstance()->select(CHARACTER_SELECT_BY_ID_QUERY, {{ Field(id) }});

    if (entries.empty()) {
        DAL::GetInstance()->throwException("Character not found");
    }

    return entryToCharacter(entries[0]);
}

Entry CharacterDAL::characterToEntry(const Character &character) {
    Entry entry = {
            {
                Field(character.getFullname()),
                Field(character.getNickname()),
                Field(character.getAge()),
                Field(character.getSugarCubes()),
                Field(character.getHomeID()),
                Field(character.getSpecies())
            }
    };

    return entry;
}

Character CharacterDAL::entryToCharacter(const Entry& entry) {
    Character character(
            entry.fields[1].text,
            entry.fields[2].text,
            entry.fields[3].numeric,
            entry.fields[4].numeric,
            entry.fields[5].numeric,
            (CharacterSpecies) entry.fields[6].numeric
    );

    character.setID(entry.fields[0].numeric);

    return character;
}

void CharacterDAL::update(int id, const Character& character) {
    DAL::GetInstance()->update(CHARACTER_UPDATE_QUERY, {
            {
                    Field(character.getFullname()),
                    Field(character.getNickname()),
                    Field(id)
            }
    });
}

void CharacterDAL::updateHome(int id, int home_id) {
    DAL::GetInstance()->update(CHARACTER_UPDATE_HOME_QUERY, {
            {
                    Field(home_id),
                    Field(id)
            }
    });
}

void CharacterDAL::updateSugarCubes(int id, int sugarCubes) {
    DAL::GetInstance()->update(CHARACTER_UPDATE_SUGAR_CUBES_QUERY, {
            {
                    Field(sugarCubes),
                    Field(id)
            }
    });
}

void CharacterDAL::truncate() {
    DAL::GetInstance()->truncate(CHARACTER_TRUNCATE_QUERY);
}