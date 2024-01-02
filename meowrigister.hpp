#ifndef MEOWRIGISTER_HPP
#define MEOWRIGISTER_HPP

#include <QWidget>

namespace Ui {
class MeowRigister;
}

class MeowRigister : public QWidget
{
    Q_OBJECT

public:
    explicit MeowRigister(QWidget *parent = nullptr);
    ~MeowRigister();

private:
    Ui::MeowRigister *ui;
};

#endif // MEOWRIGISTER_HPP
