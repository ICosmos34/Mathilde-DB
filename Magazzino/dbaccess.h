#ifndef DBACCESS_H
#define DBACCESS_H

#include <definition.h>
#include <memorymanager.h>
#include <memory.h>
#include <account.h>
#include <product.h>

#include <changeui.h>

#include <QString>
#include <QFrame>
#include <QDialog>
#include <QHeaderView>
#include <QDesktopWidget>


namespace Ui {
class DbAccess;
}

class DbAccess : public QFrame
{
    Q_OBJECT

public:
    explicit DbAccess(QWidget *parent = 0);
    explicit DbAccess(const SPMM &content, const QString &title, const unsigned char &level, const bool &areAccounts, QWidget *parent = 0);

    ~DbAccess();

    void setTab(const SPMM &content);

signals:
    void logoutRequest();
    void adminRequest();
    void editAccountRequest();
    void editRequest(const QString &content);
    void edit(const SPM &edited);
    void editPasswordRequest(const QString &oldOne, const QString &newOne);
    void reset();

private slots:
    void on_logout_clicked();
    void on_edit_account_clicked();
    void on_go_back_clicked();
    void on_contentview_doubleClicked(const QModelIndex &index);
    void on_add_clicked();

    void getMemory(const SPM &data);
    void badLogin();
    void goodEdit();

    void edit_(const SPM &edited);
    void editPassword_(const QString &oldOne, const QString &newOne);
    void remove();

    void head_clicked(QModelIndex index);

private:
    Ui::DbAccess *ui;
    ChangeUI changes;
    unsigned char lvl;
    bool isAccount;
    static const QStringList account_head, product_head;

    void build();

    void connect_changes();
    void disconnect_changes();
};

#endif // DBACCESS_H
