#include "model/Character.h"

Character::Character() = default;

Character::Character(string fullname, string nickname, int age, int sugarCubes, int homeId, CharacterSpecies species):
        m_id(0),
        m_fullname(std::move(fullname)),
        m_nickname(std::move(nickname)),
        m_age(age),
        m_sugarCubes(sugarCubes),
        m_homeId(homeId),
        m_species(species) {}

int Character::getID() const {
    return m_id;
}

string Character::getFullname() const {
    return m_fullname;
}

string Character::getNickname() const {
    return m_nickname;
}

int Character::getAge() const {
    return m_age;
}

int Character::getSugarCubes() const {
    return m_sugarCubes;
}

int Character::getHomeID() const {
    return m_homeId;
}

CharacterSpecies Character::getSpecies() const {
    return m_species;
}

void Character::setID(int id) {
    m_id = id;
}

void Character::setFullname(string &&fullname) {
    m_fullname = std::move(fullname);
}

void Character::setNickname(string &&nickname) {
    m_nickname = std::move(nickname);
}

void Character::setAge(int age) {
    m_age = age;
}

void Character::setSugarCubes(int sugarCubes) {
    m_sugarCubes = sugarCubes;
}

void Character::setHomeID(int homeID) {
    m_homeId = homeID;
}

void Character::setSpecies(CharacterSpecies species) {
    m_species = species;
}

string Character::toString() {
    return to_string(m_id)
           + " | " + m_fullname
           + " | " + m_nickname
           + " | " + to_string(m_age)
           + " | " + to_string(m_sugarCubes)
           + " | " + to_string(m_homeId)
           + " | " + to_string(m_species);
}
