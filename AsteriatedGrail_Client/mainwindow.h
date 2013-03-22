#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define CLIENT_TEST

#include <QMainWindow>
#include "src/client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();
    void ShowInText(QString msg);

private:
    Ui::MainWindow *ui;
#ifdef CLIENT_TEST
    Client *client_;
#endif
};

#endif // MAINWINDOW_H
