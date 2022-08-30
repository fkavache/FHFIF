#pragma once

#include <iostream>

using namespace std;

class Transfer {
private:
    int m_id;
    int m_characterId;
    int m_sugarCubes;

public:
    Transfer(int characterId, int sugarCubes);

    int getID() const;
    int getCharacterID() const;
    int getSugarCubes() const;

    void setID(int id);
    void setCharacterID(int characterId);
    void setSugarCubes(int sugarCubes);

    string toString();
};