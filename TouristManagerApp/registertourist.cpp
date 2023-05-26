#include "registertourist.h"
#include "ui_registertourist.h"

RegisterTourist::RegisterTourist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterTourist)
{
    ui->setupUi(this);
    ui->txtDescription->setReadOnly(true);
    if(!database.open())
    {
        qDebug() << "Error openning database <Adding options for combobox>: " << database.lastError().text();
        return;
    }
    QSqlQuery query("SELECT PackageName FROM Packages", database);

    while(query.next())
    {
        QString option = query.value(0).toString();
        ui->comboBox->addItem(option);
    }


}

RegisterTourist::~RegisterTourist()
{
    database.close();
    delete ui;
}

void RegisterTourist::on_btnRegister_clicked()
{
    if(!ui->txtFirstName->text().isEmpty() && !ui->txtMiddleName->text().isEmpty()
        && !ui->txtLastName->text().isEmpty() && !ui->txtPassportNumber->text().isEmpty()
        && !ui->txtContactNumber->text().isEmpty()
        && !ui->comboBox->currentText().isEmpty())
    {

        QString FirstName = ui->txtFirstName->text();
        QString MiddleName = ui->txtMiddleName->text();
        QString LastName = ui->txtLastName->text();
        QString PassportNo = ui->txtPassportNumber->text();
        QString ContactNo = ui->txtContactNumber->text();
        QString PermAddress = ui->txtAddress->text();
        QString PackageName = ui->comboBox->currentText();

        if(!database.open())
        {
            qDebug() << "Error openning database <Add Tourist>: " << database.lastError().text();
            return;
        }
        QSqlQuery query;
        QString insert_query = "INSERT INTO Tourist (FirstName, MiddleName, LastName, PassportNo, ContactNo, PermAddress, PackageName)"
                               "VALUES (:FirstName, :MiddleName, :LastName, :PassportNo, :ContactNo, :PermAddress, :PackageName)";

        query.prepare(insert_query);
        query.bindValue(":FirstName", FirstName);
        query.bindValue(":MiddleName", MiddleName);
        query.bindValue(":LastName", LastName);
        query.bindValue(":PassportNo", PassportNo);
        query.bindValue(":ContactNo", ContactNo);
        query.bindValue(":PermAddress", PermAddress);
        query.bindValue(":PackageName", PackageName);

        if(!query.exec())
        {
            qDebug() << "Error executing query <Register Tourist>: " << query.lastError().text();
            return;
        }
        QMessageBox msgBox;
        msgBox.setText("Tourist has been successfully registered");

        // Set the QMessageBox properties using style sheets
        msgBox.setStyleSheet(
            "QMessageBox {"
            "    background-color: #F0F0F0;"
            "    border-radius: 10px;"
            "}"
            "QMessageBox QLabel {"
            "    color: #000000;"
            "    font-family: Arial;"
            "    font-size: 14px;"
            "    margin-right: 30px;"
            "}"
            "QMessageBox QPushButton {"
            "border: 2px solid transparent;"
            "color: #FFFFFF;"
            "background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0 #84afe5, stop:1 #1168e4);"
            "padding: 5px 20px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #3d3d3d;"
            "}"
            "QMessageBox QPushButton:pressed {"
            "color: #aeaeae;"
            "background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0 #ffffff, stop:0.5 #fbfdfd, stop:1 #ffffff);"
            "}"
            );

        // Remove the close button (X) on the edge of the box
        msgBox.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

        msgBox.setStandardButtons(QMessageBox::NoButton);
        msgBox.addButton(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);

        // Get the OK button and align it in the center
        msgBox.defaultButton()->setStyleSheet("QPushButton {"
                                              "margin-right: 120px;"
                                              "}");

        // Set the font and font size for the QMessageBox text
        QLabel* label = msgBox.findChild<QLabel*>("qt_msgbox_label");
        if (label) {
            QFont font = label->font();
            font.setFamily("Arial");
            font.setPointSize(14);
            label->setFont(font);
        }

        // Execute the dialog and handle the result
        int result = msgBox.exec();
        if (result == QMessageBox::Ok) {
            msgBox.close();
        }
    }
    on_btnReset_clicked();
}


void RegisterTourist::on_comboBox_currentIndexChanged(int index)
{
    QString packageName = ui->comboBox->currentText();
    QSqlQuery query("SELECT PackageDescription FROM Packages WHERE PackageName ='" + packageName + "'", database);
    if (query.exec() && query.next()) {
        QString data = query.value(0).toString();
        ui->txtDescription->setText(data);
        // qDebug() << "Data for" << packageName << ":" << data;

    } else {
        qDebug() << "Error retrieving data:" << query.lastError().text();
    }



}


void RegisterTourist::on_btnReset_clicked()
{
    ui->txtFirstName->clear();
    ui->txtMiddleName->clear();
    ui->txtLastName->clear();
    ui->txtAddress->clear();
    ui->txtContactNumber->clear();
    ui->txtPassportNumber->clear();
    ui->txtFirstName->setFocus();
}

