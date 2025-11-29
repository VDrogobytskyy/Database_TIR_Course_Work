#include "DB.h"
#include <fstream>
#include <iostream>
#include "libs/json.hpp"

using json = nlohmann::json;

DataBase* DataBase::instance = nullptr;

DbConfig DataBase::loadConfig(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open config.json");
    }
    json j;
    file >> j;

    return {
        j["host"].get<std::string>(),
        j["port"].get<unsigned int>(),
        j["user"].get<std::string>(),
        j["password"].get<std::string>(),
        j["database"].get<std::string>()
    };
}

DataBase::DataBase() {
    try {
        config = loadConfig("config.json");
        session = std::make_unique<mysqlx::Session>(
            config.host, config.port, config.user, config.password, config.database
        );
        std::cout << "Database connected successfully" << std::endl;
    }
    catch (const mysqlx::Error &err) {
        std::cerr << "MySQL Error: " << err.what() << std::endl;
        throw;
    }
}

DataBase* DataBase::getInstance() {
    if (!instance) {
        instance = new DataBase();
    }
    return instance;
}

mysqlx::Session* DataBase::getSession() {
    return session.get();
}