#pragma once

#include <iostream>
#include "Dal.h"
#include "model/Character.h"

typedef DAL::Entry Entry;
typedef DAL::Field Field;

class CharacterDAL {
private:
    static Entry characterToEntry(const Character& character);
    static Character entryToCharacter(const Entry& entry);

public:
    static int insert(const Character& character);
    static vector<Character> selectAll();
    static vector<Character> selectByHomeID(int homeId);
    static Character selectByID(int id);
    static void update(int id, const Character& character);
    static void updateHome(int id, int homeId);
    static void updateSugarCubes(int id, int sugarCubes);
};