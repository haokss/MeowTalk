#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "InitSocket.hpp"
#include "meowuser.h"
#include "qfile.h"
// 全局socket，开启软件启用
ClientSocket CSOCKET;
// 全局MeowUser，萌T用户数据，登录成功后加载
MeowUser SELFUSER;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //设置中文字体
    QIcon icon(":/res/bg/logo.png");
    a.setFont(QFont("Microsoft Yahei", 9));
    MainWindow w;
    w.setWindowIcon(icon);
    QApplication::setWindowIcon(icon);
    w.show();

    return a.exec();
}
