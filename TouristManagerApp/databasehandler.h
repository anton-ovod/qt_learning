#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

class DatabaseHandler {
public:
    static DatabaseHandler& getInstance() {
        static DatabaseHandler instance;  // Singleton instance
        return instance;
    }

    bool initializeDatabase() {
        if (isInitialized)
            return true;
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("TouristManagerApp.db");

        if (!db.open()) {
            qDebug() << "Error opening database:" << db.lastError().text();
            return false;
        }

        QSqlQuery query;
        QString createPackageTabel = "CREATE TABLE IF NOT EXISTS Packages ("
                                     "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                     "PackageName TEXT,"
                                     "PackageDescription TEXT,"
                                     "PackagePrice TEXT"
                                     ")";
        if(!query.exec(createPackageTabel))
        {
            qDebug() << "Error creating <Package> table : "<< query.lastError().text();
        }

        QString createTouristTable = "CREATE TABLE IF NOT EXISTS Tourist ("
                                     "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                     "FirstName TEXT,"
                                     "MiddleName TEXT,"
                                     "LastName TEXT,"
                                     "PassportNo TEXT,"
                                     "ContactNo  TEXT,"
                                     "PermAddress TEXT,"
                                     "PackageName TEXT"
                                     ")";
        if(!query.exec(createTouristTable))
        {
            qDebug() << "Error creating <Tourist> table : "<< query.lastError().text();
        }
        db.close();

        isInitialized = true;
        return true;
    }

    QSqlDatabase& getDatabase() {
        return db;
    }

private:
    QSqlDatabase db;
    bool isInitialized;

    DatabaseHandler() : isInitialized(false) {}

    ~DatabaseHandler() {
        if (db.isOpen()) {
            db.close();
        }
    }

    // Prevent copy construction and assignment
    DatabaseHandler(const DatabaseHandler&) = delete;
    DatabaseHandler& operator=(const DatabaseHandler&) = delete;
};
#endif // DATABASEHANDLER_H
