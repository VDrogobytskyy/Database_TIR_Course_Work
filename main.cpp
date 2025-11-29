#include <iostream>
#include "DB.h"

int main() {
    try {
        DataBase* db = DataBase::getInstance();
        mysqlx::Session* session = db->getSession();

        // Отримуємо схему і таблицю
        mysqlx::Schema schema = session->getSchema("TIR");
        mysqlx::Table car = schema.getTable("Car");

        // Виконуємо SELECT *
        mysqlx::RowResult res = car.select("*").execute();

        // Виводимо результат
        for (mysqlx::Row row : res) { 
            for (unsigned int i = 0; i < row.colCount(); ++i) {
                std::cout << row[i] << " | ";
            }
            std::cout << std::endl;
        }

        session->close();
    }
    catch (const mysqlx::Error &err) {
        std::cerr << "MySQL Error: " << err.what() << std::endl;
    }
    catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}