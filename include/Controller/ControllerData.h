#pragma once

#include <iostream>
#include <vector>
#include "model/Character.h"

using namespace std;

class ControllerData {
public:
    static const vector<Character> &getCharacterData();
};