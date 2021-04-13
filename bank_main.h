#ifndef BANK_MAIN_H
#define BANK_MAIN_H

#include <QMainWindow>
#include <bank_menu.h>
QT_BEGIN_NAMESPACE
namespace Ui { class Bank_Main; }
QT_END_NAMESPACE

class Bank_Main : public QMainWindow
{
    Q_OBJECT

public:
    Bank_Main(QWidget *parent = nullptr);
    ~Bank_Main();
    void checkLoginAndPassword();
    QString getName();

private slots:
    void on_pushButton_zaloguj_clicked();

private:
    Ui::Bank_Main *ui;
    Bank_Menu* bankMenu;
};
#endif // BANK_MAIN_H
