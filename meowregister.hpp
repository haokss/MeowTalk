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

private:
    Ui::MeowRegister *ui;
};

#endif // MEOWREGISTER_HPP
