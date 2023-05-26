#ifndef FINDTOURIST_H
#define FINDTOURIST_H

#include <QDialog>
#include <QSqlQueryModel>
#include "databasehandler.h"


namespace Ui {
class FindTourist;
}

class FindTourist : public QDialog
{
    Q_OBJECT

public:
    explicit FindTourist(QWidget *parent = nullptr);
    ~FindTourist();

private slots:
    void on_btnFindTourist_clicked();

private:
    Ui::FindTourist *ui;
    QSqlDatabase database = DatabaseHandler::getInstance().getDatabase();
};

#endif // FINDTOURIST_H
