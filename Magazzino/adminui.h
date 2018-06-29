#ifndef ADMINUI_H
#define ADMINUI_H

#include <definition.h>
#include <QFrame>
#include <QDesktopWidget>

namespace Ui {
class AdminUI;
}

class AdminUI : public QFrame
{
    Q_OBJECT

public:
    explicit AdminUI(QWidget *parent = 0);
    ~AdminUI();

signals:
    void itemsDbRequest();

    void accountsDbRequest();

    void quitRequest();

    void logoutRequest();

private slots:
    void on_manage_database_clicked();

    void on_manage_account_clicked();

    void on_quit_clicked();

    void on_logout_clicked();

private:
    Ui::AdminUI *ui;
};

#endif // ADMINUI_H
