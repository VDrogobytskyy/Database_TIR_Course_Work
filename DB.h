#ifndef DB_H
#define DB_H

#include <mysqlx/xdevapi.h>
#include <string>

struct DbConfig {
    std::string host;
    unsigned int port;
    std::string user;
    std::string password;
    std::string database;
};

class DataBase {
    private:
        DataBase();
        static DataBase* instance;

        DbConfig config;
        std::unique_ptr<mysqlx::Session> session;

        DbConfig loadConfig(const std::string& path);

        DataBase(const DataBase&) = delete;
        DataBase& operator=(const DataBase&) = delete;

    public:
        static DataBase* getInstance();
        mysqlx::Session* getSession();
};

#endif