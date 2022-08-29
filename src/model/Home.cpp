#include "model/Home.h"

Home::Home() = default;

Home::Home(string name, int sugarCubes, int sugarCubesBudget, int userId):
        m_id(0),
        m_name(std::move(name)),
        m_sugarCubes(sugarCubes),
        m_sugarCubesBudget(sugarCubesBudget),
        m_userId(userId) {}

int Home::getID() const {
    return m_id;
}

string Home::getName() const {
    return m_name;
}

int Home::getSugarCubes() const {
    return m_sugarCubes;
}

int Home::getSugarCubesBudget() const {
    return m_sugarCubesBudget;
}

int Home::getUserID() const {
    return m_userId;
}

void Home::setID(int id) {
    m_id = id;
}

void Home::setName(string &&name) {
    m_name = std::move(name);
}

void Home::setSugarCubes(int sugarCubes) {
    m_sugarCubes = sugarCubes;
}

void Home::setSugarCubesBudget(int sugarCubesBudget) {
    m_sugarCubesBudget = sugarCubesBudget;
}

void Home::setUserID(int userID) {
    m_userId = userID;
}

string Home::toString() {
    return to_string(m_id)
           + " | " + m_name
           + " | " + to_string(m_sugarCubes)
           + " | " + to_string(m_sugarCubesBudget)
           + " | " + to_string(m_userId);
}
