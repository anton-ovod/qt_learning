#ifndef REGISTERTOURIST_H
#define REGISTERTOURIST_H

#include <QDialog>
#include <QMessageBox>
#include "databasehandler.h"

namespace Ui {
class RegisterTourist;
}

class RegisterTourist : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterTourist(QWidget *parent = nullptr);
    ~RegisterTourist();


private slots:
    void on_btnRegister_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_btnReset_clicked();

private:
    Ui::RegisterTourist *ui;
    QSqlDatabase& database = DatabaseHandler::getInstance().getDatabase();
};

#endif // REGISTERTOURIST_H
