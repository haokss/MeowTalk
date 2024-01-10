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
    // 消息记录存储在本地，每当打开一个对话就加载本地聊天记录
    // 从本地对应id中加载聊天记录
    cachePath = "D:/Qt_Project/Sql/cache/"+std::to_string(SELFUSER.self.id)+"/"
            +std::to_string(meowTalkData.id)+".txt";
    loadLocalMessage(cachePath);
    for(const auto &it:historyMessage){
        addMessageToListView(std::to_string(it.send_id).c_str());
        addMessageToListView(QString::fromStdString(it.content));
    }
    // 创建一个线程用于接收服务器的消息
    std::thread(&UserTalk::startReceiveThread,this).detach();
    // 绑定信息改变的槽函数
    connect(ui->lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onTextChanged(const QString&)));
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(on_pushButton_clicked()));

}

UserTalk::~UserTalk()
{
    // 每次关闭对话窗口之后都从数据库中同步到本地最新的聊天记录

    delete ui;
    delete itemModel;
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

void UserTalk::loadLocalMessage(const std::string &path)
{
    std::ifstream file(path);
    if(!file.is_open()){
        std::cerr<<"fail to open history"<<std::endl;
        return ;
    }
    std::string line;
    while(std::getline(file,line)){
        MeowMessage mmsg(line);
        historyMessage.push_back(mmsg);
    }
}

void UserTalk::updateLocalMessage()
{
    // 从数据库中更新本地聊天缓存

}

void UserTalk::startReceiveThread() {
    while(true){
        MeowMessage mmsg;
        CSOCKET.ReceiveMessages(mmsg);
        addMessageToListView(std::to_string(mmsg.send_id).c_str());
        addMessageToListView(QString::fromStdString(mmsg.content));
    }
}

void UserTalk::on_pushButton_exit_clicked()
{
    this->close();
}
