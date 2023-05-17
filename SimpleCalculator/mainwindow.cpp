#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double firstNum, secondNum, result;

void MainWindow::on_btnAdd_clicked()
{
    firstNum = ui->txtFirstNum->text().toDouble();
    secondNum = ui->txtSecondNum->text().toDouble();
    result = firstNum + secondNum;
    ui->txtResult->setText(QString::number(result));
}


void MainWindow::on_btnSubtract_clicked()
{
    firstNum = ui->txtFirstNum->text().toDouble();
    secondNum = ui->txtSecondNum->text().toDouble();
    result = firstNum - secondNum;
    ui->txtResult->setText(QString::number(result));
}


void MainWindow::on_btnDivide_clicked()
{
    firstNum = ui->txtFirstNum->text().toDouble();
    secondNum = ui->txtSecondNum->text().toDouble();
    if(secondNum != 0) {
        result = firstNum / secondNum;
        ui->txtResult->setText(QString::number(result));
    }
    else
    {
         ui->txtResult->setText("You can not divide by 0");
    }


}


void MainWindow::on_btnMultiply_clicked()
{
    firstNum = ui->txtFirstNum->text().toDouble();
    secondNum = ui->txtSecondNum->text().toDouble();
    result = firstNum * secondNum;
    ui->txtResult->setText(QString::number(result));
}

