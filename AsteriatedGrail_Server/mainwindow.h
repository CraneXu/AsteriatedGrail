#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define SERVER_TEST

#include <QMainWindow>
#include "src/server.h"

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
#ifdef SERVER_TEST
    Server *server_;
#endif
};

#endif // MAINWINDOW_H
