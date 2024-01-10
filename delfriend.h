#ifndef DELFRIEND_H
#define DELFRIEND_H

#include <QWidget>

namespace Ui {
class DelFriend;
}

class DelFriend : public QWidget
{
    Q_OBJECT

public:
    explicit DelFriend(QWidget *parent = nullptr);
    ~DelFriend();

private slots:
    void on_pushButton_clicked();
    
private:
    Ui::DelFriend *ui;
};

#endif // DELFRIEND_H
