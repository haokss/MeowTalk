#include "usermain.h"
#include "ui_usermain.h"
#include "qlistwidget.h"
#include "QListWidgetItem"
#include "delfriend.h"
extern MeowUser SELFUSER;
UserMain::UserMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserMain)
{
    ui->setupUi(this);
    this->setWindowTitle("MeowTalk");
    // 加载头像
    AvaButton *ava = new AvaButton(SELFUSER.self);
    ava->setParent(this);
    ava->setGeometry(20,30,100,100);
    // 加载用户名
    QLabel *label_name = ui->label;
    std::string self_name = SELFUSER.self.name;
    label_name->setText(QString::fromStdString(self_name));
    // 加载签名
    QLabel *label_sign = ui->label_2;
    std::string self_sign = "签名："+SELFUSER.self.sign;
    label_sign->setText(QString::fromStdString(self_sign));
    // 加载好友列表
    QListWidget* friendListWidget = ui->listWidget;
    friendListWidget->setIconSize(QSize(40, 30)); // 设置头像尺寸
//    friendItem->setWhatsThis("friend_id"); // 设置唯一标识符，用于处理点击事件等
    for (const MeowUserData& friendData : SELFUSER.friends) {
        // 创建 QListWidgetItem
        QListWidgetItem *item = new QListWidgetItem(QIcon(":/res/_ava/boy.png"),
                                         friendData.name.c_str());
        item->setSizeHint(QSize(80,60));
        // 将 item 添加到 QListWidget
        friendListWidget->addItem(item);
    }
    // 设置项
    QToolButton *toolButton = ui->toolButton;
    toolButton->setText("Menu");
    toolButton->setPopupMode(QToolButton::MenuButtonPopup);

    // 创建 QMenu
    menu = new QMenu(this);
    // 添加菜单项
    QAction *menuItem = new QAction("修改密码 ", this);
    menu->addAction(menuItem);
    QAction *menuItemDeleteFriend = new QAction("删除好友",this);
    menu->addAction(menuItemDeleteFriend);
    connect(menuItemDeleteFriend, &QAction::triggered, this, &UserMain::onDeleteFriend);
    menuItem = new QAction("退出 ", this);
    menu->addAction(menuItem);

    // 将 QMenu 关联到 QToolButton
    toolButton->setMenu(menu);

    // 新的好友请求
    for(const auto it:SELFUSER.newFriends){
        std::cout<<"收到好友请求 "<<it.send_id<<", "<<it.receive_id<<std::endl;
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
void UserMain::onDeleteFriend() {
    // 处理删除好友的逻辑
    DelFriend *del = new DelFriend();
    del->show();
}

void UserMain::on_pushButton_add_clicked()
{
    AddNewTalk *ant = new AddNewTalk();
    ant->show();
}

void UserMain::on_toolButton_clicked()
{
    // 获取按钮的全局坐标
    QToolButton *toolButton = ui->toolButton;
    QPoint globalPos = toolButton->mapToGlobal(QPoint(0, toolButton->height()));

    // 调整位置以确保菜单向上展开
    int screenHeight = QApplication::desktop()->screenGeometry().height();
    int menuHeight = menu->sizeHint().height();

    if (globalPos.y() + menuHeight > screenHeight) {
        globalPos.setY(globalPos.y() - menuHeight - toolButton->height());
    }

    // 弹出菜单
    menu->exec(globalPos);
}
