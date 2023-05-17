#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qlistwidget.h"
#include <QFile>
#include <QStandardPaths>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file(path);

    if(!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QListWidgetItem *item = new QListWidgetItem(in.readLine(), ui->listWidget);
        ui->listWidget->addItem(item);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }
    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
    QFile file(path);

    if(!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream out(&file);

    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        out<<ui->listWidget->item(i)->text()<<"\n";
    }
    file.close();
}


void MainWindow::on_btnAdd_clicked()
{
    if(!ui->txtTask->text().isEmpty())
    {
        QListWidgetItem* item = new QListWidgetItem(ui->txtTask->text(), ui->listWidget);
        ui->listWidget->addItem(item);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        ui->txtTask->clear();
    }
    ui->txtTask->setFocus();

}


void MainWindow::on_btnRemove_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }
}


void MainWindow::on_btnRemoveAll_clicked()
{
    ui->listWidget->clear();

}

