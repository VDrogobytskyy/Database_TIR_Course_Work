#include "DB.h"

#include <iostream>
#include <fstream>


DataBase* DataBase::instance = nullptr;

using json = nlohmann::json;

DbConfig DataBase::loadConfig(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open config.json");
    }

    json j;
    file >> j;

    return {
        j["host"],
        j["user"],
        j["password"],
        j["database"]
    };
}

DataBase::DataBase(){
    try{
        config = loadConfig("config.json");

        driver = sql::mysql::get_mysql_driver_instance();
        connection.reset(driver->connect(config.host, config.user, config.password));
        connection->setSchema(config.database);

        std::cout << "DataBase opened successfully" << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        throw;
    }
}


DataBase* DataBase::getInstance() {
    if (!instance) {
        instance = new DataBase();
    }
    return instance;
}


sql::Connection* DataBase::getConnection() {
    return connection.get();
}