#include "model/Transfer.h"

Transfer::Transfer(int characterId, int sugarCubes) :
        m_id(0),
        m_characterId(characterId),
        m_sugarCubes(sugarCubes) {}

int Transfer::getID() const {
    return m_id;
}

int Transfer::getCharacterID() const {
    return m_characterId;
}

int Transfer::getSugarCubes() const {
    return m_sugarCubes;
}

void Transfer::setID(int id) {
    m_id = id;
}

void Transfer::setCharacterID(int characterId) {
    m_characterId = characterId;
}

void Transfer::setSugarCubes(int sugarCubes) {
    m_sugarCubes = sugarCubes;
}

string Transfer::toString() {
    return to_string(m_id)
           + " | " + to_string(m_characterId)
           + " | " + to_string(m_sugarCubes);
}
