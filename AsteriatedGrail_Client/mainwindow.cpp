#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client_ = new Client();
    while(!client_->InitTcpClient((QHostAddress)"127.0.0.1")){}
    connect(client_,SIGNAL(ReadDone(QString)),this,SLOT(ShowInText(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    client_->SendMessage("hello server! I'm client");
}

void MainWindow::ShowInText(QString msg)
{
    ui->textEdit->append(msg);
}
