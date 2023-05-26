#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "databasehandler.h"
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DatabaseHandler::getInstance().initializeDatabase();

}
MainWindow::~MainWindow()
{
    delete ptrAddPackage;
    delete ptrFindPackage;
    delete ptrFindTourist;
    delete ptrRegisterTourist;
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ptrAddPackage = new AddPackage();
    ptrAddPackage->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    ptrRegisterTourist = new RegisterTourist();
    ptrRegisterTourist->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    ptrFindPackage = new FindPackage();
    ptrFindPackage->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    ptrFindTourist = new FindTourist();
    ptrFindTourist->show();
}

