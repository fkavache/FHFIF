#pragma once

#include <iostream>

using namespace std;

enum CharacterSpecies {
    CHARACTER_SPECIES_NONE = 0,
    CHARACTER_SPECIES_HUMAN,
    CHARACTER_SPECIES_IMAGINARY_FRIEND,
};

class Character {
private:
    int m_id;
    string m_fullname;
    string m_nickname;
    int m_age;
    int m_sugarCubes;
    int m_homeId;
    CharacterSpecies m_species;

public:
    Character();
    Character(string fullname, string nickname, int age, int sugarCubes, int homeId, CharacterSpecies species);

    int getID() const;
    string getFullname() const;
    string getNickname() const;
    int getAge() const;
    int getSugarCubes() const;
    int getHomeID() const;
    CharacterSpecies getSpecies() const;

    void setID(int id);
    void setFullname(string&& fullname);
    void setNickname(string&& nickname);
    void setAge(int age);
    void setSugarCubes(int sugarCubes);
    void setHomeID(int homeID);
    void setSpecies(CharacterSpecies species);

    string toString();
};