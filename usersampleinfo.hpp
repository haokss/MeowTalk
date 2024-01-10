#ifndef USERSAMPLEINFO_HPP
#define USERSAMPLEINFO_HPP

#include <QWidget>
#include "meowuser.h"
namespace Ui {
class UserSampleInfo;
}

class UserSampleInfo : public QWidget
{
    Q_OBJECT

public:
    explicit UserSampleInfo(const MeowUserData &data,QWidget *parent = nullptr);
    ~UserSampleInfo();

private:
    Ui::UserSampleInfo *ui;
};

#endif // USERSAMPLEINFO_HPP
