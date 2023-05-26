#ifndef FINDPACKAGE_H
#define FINDPACKAGE_H

#include <QDialog>
#include <QSqlQueryModel>
#include "databasehandler.h"

namespace Ui {
class FindPackage;
}

class FindPackage : public QDialog
{
    Q_OBJECT

public:
    explicit FindPackage(QWidget *parent = nullptr);
    ~FindPackage();

private slots:
    void on_btnFindPackage_clicked();

private:
    Ui::FindPackage *ui;
    QSqlDatabase database = DatabaseHandler::getInstance().getDatabase();
};

#endif // FINDPACKAGE_H
