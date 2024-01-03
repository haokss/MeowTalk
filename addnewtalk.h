#ifndef ADDNEWTALK_H
#define ADDNEWTALK_H

#include <QMainWindow>
#include <QtWidgets>
#include <QListWidget>
#include <QListWidgetItem>
#include <fstream>
#include "ui_addnewtalk.h"
#include "InitSocket.hpp"
#include "meowuser.h"
namespace Ui {
class AddNewTalk;
}

class AddNewTalk : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddNewTalk(QWidget *parent = nullptr);
    ~AddNewTalk();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_accept(const MeowMessage& friendMessage);
    void on_pushButton_reject();
    void onSearchChanged(const QString& newText);

private:
    Ui::AddNewTalk *ui;
    QString search;
};

class FriendItemWidget : public QWidget {
    Q_OBJECT
public:
    explicit FriendItemWidget(const MeowMessage& friendMessage, QWidget *parent = nullptr)
        : QWidget(parent), friendMessage(friendMessage){
        QHBoxLayout *layout = new QHBoxLayout(this);

        QLabel *nameLabel = new QLabel(QString::number(friendMessage.send_id));
        layout->addWidget(nameLabel);

        QPushButton *acceptButton = new QPushButton("接受 ");
        QPushButton *rejectButton = new QPushButton("拒绝 ");

        connect(acceptButton, &QPushButton::clicked, this, [this,friendMessage]{ emit acceptButtonClicked(friendMessage); });
        connect(rejectButton, &QPushButton::clicked, this, &FriendItemWidget::rejectButtonClicked);

        layout->addWidget(acceptButton);
        layout->addWidget(rejectButton);

        setLayout(layout);
    }
private:
    MeowMessage friendMessage;
signals:
    void acceptButtonClicked(const MeowMessage& friendMessage);
    void rejectButtonClicked();
};
#endif // ADDNEWTALK_H
