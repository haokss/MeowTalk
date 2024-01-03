#include "addnewtalk.h"

extern ClientSocket CSOCKET;
extern MeowUser SELFUSER;
AddNewTalk::AddNewTalk(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddNewTalk)
{
    ui->setupUi(this);

    QListWidget *friendListWidget = ui->listWidget;
    std::vector<MeowMessage> newFriends = SELFUSER.newFriends;

    // Add friend items
    for (const MeowMessage& friendName : newFriends) {
//        QString sendIdQStr = static_cast<QString>(friendName.send_id);
        FriendItemWidget *friendItemWidget = new FriendItemWidget(friendName);
        QListWidgetItem *item = new QListWidgetItem(friendListWidget);
        item->setSizeHint(friendItemWidget->sizeHint());
        friendListWidget->addItem(item);
        friendListWidget->setItemWidget(item, friendItemWidget);
        connect(friendItemWidget, &FriendItemWidget::acceptButtonClicked, this, &AddNewTalk::on_pushButton_accept);
        connect(friendItemWidget, &FriendItemWidget::rejectButtonClicked, this, &AddNewTalk::on_pushButton_reject);
    }

//    setCentralWidget(friendListWidget);
    // 搜索信息改变的信号和槽
    connect(ui->lineEdit,SIGNAL(textChanged(const QString&)), this, SLOT(onSearchChanged(const QString&)));
}

AddNewTalk::~AddNewTalk()
{
    delete ui;
}

void AddNewTalk::on_pushButton_clicked()
{
    // 发送添加好友/群请求
    // TODO:: 逻辑上应该先判断是否已经是好友了

    std::string str = "0#4#"+std::to_string(SELFUSER.self.id)
            +"#"+search.toStdString()+"#request";
    CSOCKET.SendeMessages(str.c_str());

    // TODO:: 由服务器判断目标是否存在，服务器返回查找结果
    MeowMessage mmsg;
    CSOCKET.ReceiveMessages(mmsg);
    // 暂时的做法：立即创建消息缓存
    if(mmsg.content=="1"){
        std::string path = "D:/Qt_Project/Sql/cache/"+std::to_string(SELFUSER.self.id)+"/"+
                search.toStdString()+".txt";
        std::cout<<path<<std::endl;
        std::ofstream outfile(path);
    }else{
        QMessageBox::information(this,"warning","用户不存在");
    }
    ui->lineEdit->setText("");
}

void AddNewTalk::on_pushButton_accept(const MeowMessage& friendMessage)
{
    // 发送建立好友到服务器
    std::string str = "0#4#"+std::to_string(SELFUSER.self.id)
            +"#"+std::to_string(friendMessage.send_id)+"#accept";
    CSOCKET.SendeMessages(str.c_str());
    delete ui->listWidget->currentItem();
    // 建立消息缓存
    std::string path = "D:/Qt_Project/Sql/cache/"+std::to_string(SELFUSER.self.id)+"/"+
            std::to_string(friendMessage.send_id)+".txt";
    std::ofstream outfile(path);
}

void AddNewTalk::on_pushButton_reject()
{
    // 拒绝请求什么也不做了
    delete ui->listWidget->currentItem();
}

void AddNewTalk::onSearchChanged(const QString &newText)
{
    search = newText;
}
