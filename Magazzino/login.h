#ifndef LOGIN_H
#define LOGIN_H

#include <account.h>

#include <QFrame>
#include <QDesktopWidget>
#include <QFont>
#include <QString>
#include <QKeyEvent>

namespace Ui {
class Login;
}

class Login : public QFrame
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

signals:
    void loginTry(const QString &, const QString &);

private slots:
    void on_login_clicked();

    void badLogin();

private:
    Ui::Login *ui;
    void keyPressEvent(QKeyEvent* e);
};

#endif // LOGIN_H
