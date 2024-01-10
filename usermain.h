#ifndef USERMAIN_H
#define USERMAIN_H

#include <QMainWindow>
#include "meowuser.h"
#include "qlistwidget.h"
#include "qmessagebox.h"
#include "usertalk.h"
#include "addnewtalk.h"
#include "avabutton.hpp"
namespace Ui {
class UserMain;
}

class UserMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserMain(QWidget *parent = nullptr);
    ~UserMain();

private:
    Ui::UserMain *ui;
    AvaButton *ava;
    // 创建用户界面的同时生成对应用户
    MeowUser now_user;
    QMenu *menu;
private slots:
    void onItemClicked(QListWidgetItem* item);
    void on_pushButton_add_clicked();
    void on_toolButton_clicked();
    void onDeleteFriend();
};

#endif // USERMAIN_H
