#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "meowuser.h"
#include "qmessagebox.h"
#include "MeowMessage.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_main_login_clicked();
    void on_pushButton_exit_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

private:
    void on_pushButton_main_login();
};
#endif // MAINWINDOW_H
