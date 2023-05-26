#include "findtourist.h"
#include "ui_findtourist.h"

FindTourist::FindTourist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindTourist)
{
    ui->setupUi(this);
}

FindTourist::~FindTourist()
{
    delete ui;
}

void FindTourist::on_btnFindTourist_clicked()
{
    if(!ui->txtTouristName->text().isEmpty())
    {
        QString touristName =ui->txtTouristName->text();
        if(!database.open())
        {
            qDebug() << "Error openning database <Find Tourist>";
            return;
        }
        QString queryString = "SELECT FirstName, MiddleName, LastName, PassportNo, ContactNo, PermAddress, PackageName FROM Tourist WHERE FirstName LIKE '%" + touristName + "%'";
        QSqlQueryModel* model = new QSqlQueryModel;
        model->setQuery(queryString);
        ui->tableView->setModel(model);
        database.close();
    }
    else
    {
        ui->txtTouristName->setFocus();
        qDebug() << "You need to enter something in the `lineEdit` object.";
        return;
    }
}

