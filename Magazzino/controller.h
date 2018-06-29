#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <definition.h>

#include <iofile.h>

#include <memorymanager.h>
#include <account.h>

#include <login.h>
#include <adminui.h>
#include <dbaccess.h>
#include <changeui.h>

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT

public:

    Controller();

    virtual ~Controller();

    void start();

signals:
    // login frame
    void badLogin();

    // dbaccess frame
    // void badLogin(); duplicato
    void goodEdit();
    void getMemory(const SPM &content);

private slots:
    // login frame
    void loginTry(const QString &username, const QString &password);

    // admin frame
    void itemsDbRequest();
    void accountsDbRequest();
    void quitRequest();
    void logoutRequest();

    // dbaccess frame
    // void logoutRequest(); duplicato
    void adminRequest();
    void editAccountRequest();
    void editRequest(const QString &content);
    void edit(const SPM &edited);
    void editPasswordRequest(const QString &oldOne, const QString &newOne);
    void reset();

private:
    bool is_product_view;
    IOFile iof;
    SPA logged;
    SPF gui;
    SPM changing;

    void connect_login();
    void disconnect_login();
    
    void connect_adminui();
    void disconnect_adminui();
    
    void connect_dbaccess();
    void disconnect_dbaccess();

    void connect_changes();
    void disconnect_changes();
};

#endif // CONTROLLER_H
