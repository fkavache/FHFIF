#include "model/User.h"

User::User(string eMail, string password):
        m_eMail(std::move(eMail)), m_password(std::move(password)) {}

int User::getID() const {
    return m_id;
}

string User::getEMail() const {
    return m_eMail;
}

string User::getPassword() const {
    return m_password;
}

void User::setEMail(string &&eMail) {
    m_eMail = std::move(eMail);
}

void User::setPassword(string &&password) {
    m_password = std::move(password);
}

void User::setID(int id) {
    m_id = id;
}

string User::toString() {
    return to_string(m_id) + " | " + m_eMail + " | " + m_password;
}
