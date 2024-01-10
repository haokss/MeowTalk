#ifndef USERINFO_HPP
#define USERINFO_HPP

#include <QWidget>
#include "meowuser.h"
namespace Ui {
class UserInfo;
}

class UserInfo : public QWidget
{
    Q_OBJECT

public:
    explicit UserInfo(const MeowUserData& userData,QWidget *parent = nullptr);
    ~UserInfo();

private slots:
    void on_pushButton_submit_clicked();

private:
    Ui::UserInfo *ui;
    MeowUserData userData;
};

#endif // USERINFO_HPP
