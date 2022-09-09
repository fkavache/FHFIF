#include <iostream>
#include "api/APIServer.h"
#include "dal/Dal.h"

using namespace std;

// TODO: [vacheka] config
#define DB        "localhost@fhfif"
#define USER      "postgres"
#define PASSWORD  "testpass"
#define LOCALHOST "127.0.0.1"
#define PORT       8080

int main() {
//    DAL::GetInstance()->connect(DB, USER, PASSWORD, SA_PostgreSQL_Client);
//
//    APIServer::run(LOCALHOST, PORT);
//
//    DAL::GetInstance()->disconnect();

    cout << "\n============== FHFIF ==============\n" << endl;
    return 0;
}
