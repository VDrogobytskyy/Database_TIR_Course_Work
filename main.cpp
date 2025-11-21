#include <iostream>
#include <fstream>
#include <memory>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/resultset.h>
#include "libs/json.hpp" 

using json = nlohmann::json;

struct DbConfig {
    std::string host;
    std::string user;
    std::string password;
    std::string database;
};

DbConfig loadConfig(const std::string& path) {
    std::ifstream file(path);
    json j;
    file >> j;

    return {
        j["host"],
        j["user"],
        j["password"],
        j["database"]
    };
}

int main() {
    try {
        DbConfig cfg = loadConfig("config.json");


        sql::mysql::MySQL_Driver *driver;
        std::unique_ptr<sql::Connection> con;

        driver = sql::mysql::get_mysql_driver_instance();
        con.reset(driver->connect(cfg.host, cfg.user, cfg.password));
        con->setSchema(cfg.database);

        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM Car"));

        while (res->next()) {
            std::cout << res->getString(1) << std::endl;
        }
    }
    catch (sql::SQLException &e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}
