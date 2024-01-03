#ifndef USERTALK_H
#define USERTALK_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <thread>
#include <fstream>
#include "meowuser.h"
#include "InitSocket.hpp"

namespace Ui {
class UserTalk;
}

class UserTalk : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserTalk(MeowUserData mud,QWidget *parent = nullptr);
    ~UserTalk();
public:
    void addMessageToListView(const QString &message);
    void loadLocalMessage(const std::string& path);
    void updateLocalMessage();
    void startReceiveThread();
public:
    MeowUserData meowTalkData;
    std::vector<MeowMessage> historyMessage;
    std::string cachePath;
    QString input;
    QStandardItemModel *itemModel;
private slots:
    void onTextChanged(const QString& newText);
    void on_pushButton_clicked();
    void on_pushButton_exit_clicked();

private:
    Ui::UserTalk *ui;

};

#endif // USERTALK_H
