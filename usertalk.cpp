#include "usertalk.h"
#include "ui_usertalk.h"

extern ClientSocket CSOCKET;
extern MeowUser SELFUSER;
UserTalk::UserTalk(MeowUserData mud,QWidget *parent) :
    QMainWindow(parent),ui(new Ui::UserTalk)
{
    meowTalkData = mud;
    ui->setupUi(this);
    ui->label->setText(meowTalkData.name.c_str());
    itemModel = new QStandardItemModel(this);
    ui->listView->setModel(itemModel);
    ui->listView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 创建一个线程用于接收服务器的消息
    std::thread(&UserTalk::startReceiveThread,this).detach();
    // 绑定信息改变的槽函数
    connect(ui->lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onTextChanged(const QString&)));
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(on_pushButton_clicked()));

}

UserTalk::~UserTalk()
{
    delete ui;
}
// 绑定消息槽
void UserTalk::onTextChanged(const QString& newText) {
    // 从输入框中获取得到输入信息
    input = newText;

}
void UserTalk::on_pushButton_clicked()
{
    // 解析输入数据
    std::string send = input.toStdString();
    // 封装发送数据
    send = "0#3#"+std::to_string(SELFUSER.self.id)+"#"+
            std::to_string(meowTalkData.id)+"#"+send;
    const char *sendByte = send.c_str();
    CSOCKET.SendeMessages(sendByte);
    // 接受自己的回传消息
//    MeowMessage mmsg;
//    CSOCKET.ReceiveMessages(mmsg);
//    addMessageToListView(std::to_string(mmsg.send_id).c_str());
//    addMessageToListView(static_cast<QString>(mmsg.content));
    // 发送消息成功后应该清除lineEidt
    QLineEdit *qle = new QLineEdit();
    qle = this->ui->lineEdit;
    qle->setText("");

}
void UserTalk::addMessageToListView(const QString &message) {
    QStandardItem *item = new QStandardItem(message);
    itemModel->appendRow(item);
    // 如果需要滚动到最后一行显示新消息，可以添加以下代码
    ui->listView->scrollToBottom();
}

void UserTalk::startReceiveThread() {
    while(true){
        MeowMessage mmsg;
        CSOCKET.ReceiveMessages(mmsg);
        addMessageToListView(std::to_string(mmsg.send_id).c_str());
        addMessageToListView(static_cast<QString>(mmsg.content));
    }

}

void UserTalk::on_pushButton_exit_clicked()
{
    this->close();
}
