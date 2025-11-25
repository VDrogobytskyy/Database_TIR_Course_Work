#include <iostream>
#include <fstream>
#include <memory>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/resultset.h>
#include "libs/json.hpp" 

#include "DB.h"

int main(void) {
    try {

        DataBase* db = DataBase::getInstance();
        sql::Connection* con = db->getConnection();

        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM Car"));

        sql::ResultSetMetaData* meta = res->getMetaData();
        int columnCount = meta->getColumnCount();

        for (int i = 1; i <= columnCount; ++i) {
            std::cout << meta->getColumnName(i);
            if (i < columnCount) std::cout << " | ";
        }
        std::cout << std::endl;

        while (res->next()) {
            for (int i = 1; i <= columnCount; ++i) {
                std::cout << res->getString(i);
                if (i < columnCount) std::cout << " | ";
            }
            std::cout << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


    return 0;
}