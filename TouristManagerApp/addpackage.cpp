#include "addpackage.h"
#include "ui_addpackage.h"



AddPackage::AddPackage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPackage)
{
    ui->setupUi(this);
}

AddPackage::~AddPackage()
{
    delete ui;
}

void AddPackage::on_btnSave_clicked()
{
    if(!ui->txtPackageName->text().isEmpty() && !ui->txtDescription->toPlainText().isEmpty() && !ui->txtPackagePrice->text().isEmpty())
    {
        QString packageName = ui->txtPackageName->text();
        QString packageDescription = ui->txtDescription->toPlainText();
        QString packagePrice = ui->txtPackagePrice->text();

        if(!database.open())
        {
            qDebug() << "Error openning database <Add Package>: " << database.lastError().text();
            return;
        }
        QSqlQuery query;
        QString insert_query = "INSERT INTO Packages (PackageName, PackageDescription, PackagePrice) "
                  "VALUES (:PackageName, :PackageDescription, :PackagePrice)";

        query.prepare(insert_query);
        query.bindValue(":PackageName", packageName);
        query.bindValue(":PackageDescription", packageDescription);
        query.bindValue(":PackagePrice", packagePrice);

        if(!query.exec())
        {
            qDebug() << "Error executing query <Add Package>: " << query.lastError().text();
            return;
        }
        QMessageBox msgBox;
        msgBox.setText("Package has been successfully added");

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
        database.close();
    }
    on_btnReset_clicked();
}


void AddPackage::on_btnReset_clicked()
{
    ui->txtPackageName->clear();
    ui->txtDescription->clear();
    ui->txtPackagePrice->clear();
    ui->txtPackageName->setFocus();

}

