#ifndef DB_H
#define DB_H

#include <string>
#include <memory>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/resultset.h>
#include "libs/json.hpp" 

struct DbConfig {
    std::string host;
    std::string user;
    std::string password;
    std::string database;
};


class DataBase{
    private:
        DataBase();
        static DataBase* instance;

        DbConfig config;
        sql::mysql::MySQL_Driver *driver;
        std::unique_ptr<sql::Connection> connection;

        DbConfig loadConfig(const std::string &path);

        DataBase(const DataBase&) = delete;
        DataBase operator=(const DataBase&) = delete;
    public:
        static DataBase* getInstance();
        sql::Connection* getConnection();

};



#endif