#include "controller/ControllerData.h"

// TODO: [vacheka] predefined
static const vector<Character> characterData = {
        {"Blooregard Q. Kazoo", "Bloo", 22, 0, 0, CHARACTER_SPECIES_IMAGINARY_FRIEND},
        {"Cheese", "Scary Yellow Man",  20, 0, 0, CHARACTER_SPECIES_IMAGINARY_FRIEND},
        {"Wilt", "Lord Snotzax",        46, 0, 0, CHARACTER_SPECIES_IMAGINARY_FRIEND},
        {"Mr. Herriman", "Funny Bunny", 44, 0, 0, CHARACTER_SPECIES_IMAGINARY_FRIEND},
        {"Berry", "Barry Bling",        5,  0, 0, CHARACTER_SPECIES_IMAGINARY_FRIEND},

        {"Mac Kazoo", "Mac-Attack",    23, 0, 0, CHARACTER_SPECIES_HUMAN},
        {"Francis Foster", "Missy",    38, 0, 0, CHARACTER_SPECIES_HUMAN},
        {"Goo", "Lollipop Star",       27, 0, 0, CHARACTER_SPECIES_HUMAN},
        {"Martha Foster", "The Queen", 97, 0, 0, CHARACTER_SPECIES_HUMAN},
        {"Chris", "Dork",              32, 0, 0, CHARACTER_SPECIES_HUMAN}
};

const vector<Character> &ControllerData::getCharacterData() {
    return characterData;
}