#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class DatabaseManager {
public:
    static DatabaseManager& instance();
    bool openDatabase(const QString& path);
    void initSchema();

private:
    DatabaseManager() = default;
    QSqlDatabase db;
};

#endif
