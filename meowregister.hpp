#ifndef MEOWREGISTER_HPP
#define MEOWREGISTER_HPP

#include <QWidget>

namespace Ui {
class MeowRegister;
}

class MeowRegister : public QWidget
{
    Q_OBJECT

public:
    explicit MeowRegister(QWidget *parent = nullptr);
    ~MeowRegister();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_register_clicked();

private:
    Ui::MeowRegister *ui;
    int regId;
};

#endif // MEOWREGISTER_HPP
