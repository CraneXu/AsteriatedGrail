#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server_ = new Server(5555);
    server_->InitTcpServer();
    //connect(server_,&Server::ReadDone,this,&MainWindow::ShowInText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    server_->SendMessage(*server_,(QString)"hello client! I'm server");
}

void MainWindow::ShowInText(QString msg)
{
    ui->textEdit->append(msg);
}
