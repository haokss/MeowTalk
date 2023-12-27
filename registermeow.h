#ifndef REGISTERMEOW_H
#define REGISTERMEOW_H

#include <QMainWindow>

namespace Ui {
class RegisterMeow;
}

class RegisterMeow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterMeow(QWidget *parent = nullptr);
    ~RegisterMeow();

private:
    Ui::RegisterMeow *ui;
};

#endif // REGISTERMEOW_H
