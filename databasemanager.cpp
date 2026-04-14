#include "databasemanager.h"

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager inst;
    return inst;
}

bool DatabaseManager::openDatabase(const QString& path) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    return db.open();
}

void DatabaseManager::initSchema() {
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS credentials ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "service TEXT, "
               "username TEXT, "
               "password TEXT, "
               "url TEXT, "
               "notes TEXT)");
}
