#include "findpackage.h"
#include "ui_findpackage.h"

FindPackage::FindPackage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindPackage)
{
    ui->setupUi(this);
}

FindPackage::~FindPackage()
{
    delete ui;
}

void FindPackage::on_btnFindPackage_clicked()
{
    if(!ui->txtPackageName->text().isEmpty())
    {
        QString packageName =ui->txtPackageName->text();
        if(!database.open())
        {
            qDebug() << "Error openning database <Find Package>";
            return;
        }
        QString queryString = "SELECT PackageName, PackageDescription, PackagePrice FROM Packages WHERE PackageName LIKE '%" + packageName + "%'";
        QSqlQueryModel* model = new QSqlQueryModel;
        model->setQuery(queryString);
        ui->tableView->setModel(model);
        ui->tableView->setColumnWidth(0, 120);
        ui->tableView->setColumnWidth(1, 240);
        ui->tableView->setColumnWidth(2, 103);
        database.close();
    }
    else
    {
        ui->txtPackageName->setFocus();
        qDebug() << "You need to enter something in the `lineEdit` object.";
        return;
    }

}

