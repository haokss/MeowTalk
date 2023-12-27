#include "usermain.h"
#include "ui_usermain.h"
#include "qlistwidget.h"
#include "QListWidgetItem"
extern MeowUser SELFUSER;
UserMain::UserMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserMain)
{
    ui->setupUi(this);
    this->setWindowTitle("MeowTalk");
    // 加载用户名
    QLabel *label_name = ui->label;
    std::string self_name = "用户名: "+SELFUSER.self.name;
    label_name->setText(QString::fromStdString(self_name));
    // 加载签名
    QLabel *label_sign = ui->label_2;
    std::string self_sign = "sign: "+SELFUSER.self.sign;
    label_sign->setText(QString::fromStdString(self_sign));
    // 加载好友列表
    QListWidget* friendListWidget = ui->listWidget;
    friendListWidget->setIconSize(QSize(40, 30)); // 设置头像尺寸
    // 添加好友条目
//    friendItem->setWhatsThis("friend_id"); // 设置唯一标识符，用于处理点击事件等
    for (const MeowUserData& friendData : SELFUSER.friends) {
        // 创建 QListWidgetItem
        QListWidgetItem *item = new QListWidgetItem(QIcon("D:\\Qt_Project\\Sql\\res\\_ava\\ava.png"),
                                         friendData.name.c_str());
        item->setSizeHint(QSize(80,60));
        // 将 item 添加到 QListWidget
        friendListWidget->addItem(item);
    }
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onItemClicked(QListWidgetItem*)));
}

UserMain::~UserMain()
{
    delete ui;
}

void UserMain::onItemClicked(QListWidgetItem *item)
{
    if (item) {
        int row = ui->listWidget->row(item);  // 获取所点击的项的行号
        const MeowUserData& clickedUserData = SELFUSER.friends[row];  // 获取对应的 MeowUserData
        // 在这里根据 clickedId 产生不同的对话框内容
        // 等待实现：每打开一个新的对话框都应该向服务器请求历史对话数据
        // 请求的历史对话数据可以从服务器加载到本地，这样下次打开就不需要从服务器请求了
        UserTalk *usertalk_id = new UserTalk(clickedUserData);
        // MeowUserData 似乎需要拷贝构造函数
        usertalk_id->show();
    }
}

void UserMain::on_pushButton_add_clicked()
{
    AddNewTalk *ant = new AddNewTalk();
    ant->show();
}
