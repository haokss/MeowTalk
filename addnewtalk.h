#ifndef ADDNEWTALK_H
#define ADDNEWTALK_H

#include <QMainWindow>

namespace Ui {
class AddNewTalk;
}

class AddNewTalk : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddNewTalk(QWidget *parent = nullptr);
    ~AddNewTalk();

private slots:
    void on_pushButton_clicked();
    void onSearchChanged(const QString& newText);

private:
    Ui::AddNewTalk *ui;
    QString search;
};

#endif // ADDNEWTALK_H
