#include "avabutton.hpp"
#include <QMouseEvent>
#include <QEvent>
#include <qdebug.h>
AvaButton::AvaButton(const MeowUserData &userData,QWidget *parent):QPushButton(parent)
{
    // 设置用户头像
    if(userData.sex){
        QIcon icon(":/res/_ava/boy.png");
        setIcon(icon);
        setIconSize(QSize(100,100));
    }else{
        QIcon icon(":/res/_ava/girl.png");
        setIcon(icon);
        setIconSize(QSize(100,100));
    }
    // 设置按钮的位置和大小
    setFixedSize(100,100);
    QString style = "QPushButton {border-radius: 50%; background-color: white; padding: 50%;}";
    setStyleSheet(style);
    // 加载信息
    userData.printMeowUserData();
    uData = userData;
    usInfo = new UserSampleInfo(uData);
    usInfo->setWindowFlags(Qt::FramelessWindowHint);
    uInfo = new UserInfo(uData);
}

AvaButton::~AvaButton()
{
    delete usInfo;
    delete uInfo;
}
void AvaButton::enterEvent(QEvent *event) {
    QPoint buttonTopLeft = mapToGlobal(rect().topLeft());
    // 鼠标进入按钮时的处理逻辑
    usInfo->setGeometry(buttonTopLeft.x() - 330, buttonTopLeft.y(), 300, 150);
    usInfo->show();
    QWidget::enterEvent(event);
}

void AvaButton::leaveEvent(QEvent *event) {
    // 鼠标离开按钮时的处理逻辑
    usInfo->hide();
    QWidget::leaveEvent(event);
}

void AvaButton::mousePressEvent(QMouseEvent *event)
{
    usInfo->hide();
    uInfo->show();
    QPushButton::mousePressEvent(event);
}
