#ifndef AVABUTTON_HPP
#define AVABUTTON_HPP

#include <QWidget>
#include <QPushButton>
#include "usersampleinfo.hpp"
#include "userinfo.hpp"
#include "meowuser.h"

class AvaButton: public QPushButton
{
    Q_OBJECT
public:
    AvaButton(const MeowUserData& userData,QWidget *parent = nullptr);
    ~AvaButton();
private:
    UserSampleInfo *usInfo;
    UserInfo *uInfo;
    MeowUserData uData;
protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // AVABUTTON_HPP
