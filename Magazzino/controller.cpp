#include "controller.h"

//
// Controller
//
Controller::Controller()
    :QObject()
{
} // Controller

//
// ~Controller
//
Controller::~Controller() {} // ~Controller

//
// start
//
void Controller::start()
{
    gui = SPF(new Login());
    connect_login();

    gui->show();
} // start

//
// loginTry
//
void Controller::loginTry(const QString &username, const QString &password)
{
    logged = (iof.search(username)).dynamicCast<Account>();

    if(!logged.isNull()  && (logged->getEncryptedPassword() == password)) {

        // gestione GUI
        disconnect_login();
        gui.clear();
        if(logged->getLevel() == Account::OWNER) {
            gui = SPF(new AdminUI());
            connect_adminui();
        } else {
            is_product_view = true;
            gui = SPF(new DbAccess(iof.loadProducts(), "Mathilde DB", false, false));
            connect_dbaccess();
        }

        gui->show();

    } else {

        emit badLogin();
    }
} // loginTry

//
// itemsDbRequest
//
void Controller::itemsDbRequest()
{
    is_product_view = true;
    disconnect_adminui();
    gui.clear();

    gui = SPF(new DbAccess(iof.loadProducts(), "Mathilde DB - Products", logged->getLevel(), false));
    connect_dbaccess();
    gui->show();
} // itemsDbRequest

//
// accountsDbRequest
//
void Controller::accountsDbRequest()
{
    is_product_view = false;
    disconnect_adminui();
    gui.clear();

    gui = SPF(new DbAccess(iof.loadAccounts(), "Mathilde DB - Accounts", logged->getLevel(), true));
    connect_dbaccess();
    gui->show();
} // accountsDbRequest

//
// quitRequest
//
void Controller::quitRequest()
{
    exit(0);
} // quitRequest

//
// logoutRequest
//
void Controller::logoutRequest()
{
    // può provenire da AdminUI o DbAccess
    // disconnetto entrambi per evitare segnali pendenti
    if(dynamic_cast<AdminUI *>(gui.data())) {
        disconnect_adminui();
    }
    else if(dynamic_cast<DbAccess *>(gui.data())) {
        disconnect_dbaccess();
    }

    gui.clear();

    logged = SPA();

    gui = SPF(new Login());
    connect_login();
    gui->show();
} // logoutRequest

//
// adminRequest
//
void Controller::adminRequest()
{
    disconnect_dbaccess();
    gui.clear();

    gui = SPF(new AdminUI());
    connect_adminui();
    gui->show();
} // adminRequest

//
// editAccountRequest
//
void Controller::editAccountRequest()
{
    changing = logged;
    emit getMemory(changing);
} // editAccountRequest

//
// editRequest
//
void Controller::editRequest(const QString &content)
{
    changing = iof.search(content);

    if(logged->getLevel() & Account::EDIT)
        emit getMemory(changing);
} // editRequest

//
// edit
//
void Controller::edit(const SPM &edited)
{
    if(iof.edit(changing, edited)) {
        if(QSharedPointer<DbAccess> temp = gui.dynamicCast<DbAccess>()) {
            if(is_product_view) {
                temp->setTab(iof.loadProducts());
            } else {
                temp->setTab(iof.loadAccounts());
            }
        }
        emit goodEdit();
    } else {
        emit badLogin();
    }
} // edit

//
// editPasswordRequest
//
void Controller::editPasswordRequest(const QString &oldOne, const QString &newOne)
{
    if(logged->editPWD(oldOne, newOne))
        emit goodEdit();
    else
        emit badLogin();
} // editPasswordRequest

//
// reset
//
void Controller::reset()
{
    changing = SPM();
} // reset

//
// connect_login
//
void Controller::connect_login()
{
    QObject::connect(
                this        , SIGNAL(badLogin()),
                gui.data()  , SLOT  (badLogin())
                );
    QObject::connect(
                gui.data()  , SIGNAL(loginTry(const QString&, const QString&)),
                this        , SLOT  (loginTry(const QString&, const QString&))
                );
} // connect_login

//
// disconnect_login
//
void Controller::disconnect_login()
{
    QObject::disconnect(
                this        , SIGNAL(badLogin()),
                gui.data()  , SLOT  (badLogin())
                );
    QObject::disconnect(
                gui.data()  , SIGNAL(loginTry(const QString&, const QString&)),
                this        , SLOT  (loginTry(const QString&, const QString&))
                );
} // disconnect_login

//
// connect_adminui
//
void Controller::connect_adminui()
{
    QObject::connect(
                gui.data()  , SIGNAL(itemsDbRequest()),
                this        , SLOT  (itemsDbRequest())
                );
    QObject::connect(
                gui.data()  , SIGNAL(accountsDbRequest()),
                this        , SLOT  (accountsDbRequest())
                );
    QObject::connect(
                gui.data()  , SIGNAL(quitRequest()),
                this        , SLOT  (quitRequest())
                );
    QObject::connect(
                gui.data()  , SIGNAL(logoutRequest()),
                this        , SLOT  (logoutRequest())
                );
} // connect_adminui

//
// disconnect_adminui
//
void Controller::disconnect_adminui()
{
    QObject::disconnect(
                gui.data()  , SIGNAL(itemsDbRequest()),
                this        , SLOT  (itemsDbRequest())
                );
    QObject::disconnect(
                gui.data()  , SIGNAL(accountsDbRequest()),
                this        , SLOT  (accountsDbRequest())
                );
    QObject::disconnect(
                gui.data()  , SIGNAL(quitRequest()),
                this        , SLOT  (quitRequest())
                );
    QObject::disconnect(
                gui.data()  , SIGNAL(logoutRequest()),
                this        , SLOT  (logoutRequest())
                );
} // disconnect_adminui

//
// connect_dbaccess
//
void Controller::connect_dbaccess()
{
    QObject::connect(
                gui.data()  , SIGNAL(logoutRequest()),
                this        , SLOT  (logoutRequest())
                );
    QObject::connect(
                gui.data()  , SIGNAL(adminRequest()),
                this        , SLOT  (adminRequest())
                );
    QObject::connect(
                gui.data()  , SIGNAL(editAccountRequest()),
                this        , SLOT  (editAccountRequest())
                );
    QObject::connect(
                gui.data()  , SIGNAL(editRequest(const QString&)),
                this        , SLOT  (editRequest(const QString&))
                );
    QObject::connect(
                gui.data()  , SIGNAL(edit(const QSharedPointer<Memory>&)),
                this        , SLOT  (edit(const QSharedPointer<Memory>&))
                );
    QObject::connect(
                gui.data()  , SIGNAL(editPasswordRequest(const QString &, const QString &)),
                this        , SLOT  (editPasswordRequest(const QString &, const QString &))
                );
    QObject::connect(
                gui.data()  , SIGNAL(reset()),
                this        , SLOT  (reset())
                );
    QObject::connect(
                this        , SIGNAL(getMemory(const QSharedPointer<Memory>&)),
                gui.data()  , SLOT  (getMemory(const QSharedPointer<Memory>&))
                );
    QObject::connect(
                this        , SIGNAL(badLogin()),
                gui.data()  , SLOT  (badLogin())
                );
    QObject::connect(
                this        , SIGNAL(goodEdit()),
                gui.data()  , SLOT  (goodEdit())
                );
} // connect_dbaccess

//
// disconnect_dbaccess
//
void Controller::disconnect_dbaccess()
{
    QObject::disconnect(
                gui.data()  , SIGNAL(logoutRequest()),
                this        , SLOT  (logoutRequest())
                );
    QObject::disconnect(
                gui.data()  , SIGNAL(adminRequest()),
                this        , SLOT  (adminRequest())
                );
    QObject::disconnect(
                gui.data()  , SIGNAL(editAccountRequest()),
                this        , SLOT  (editAccountRequest())
                );
    QObject::disconnect(
                gui.data()  , SIGNAL(editRequest(const QString&)),
                this        , SLOT  (editRequest(const QString&))
                );
    QObject::disconnect(
                gui.data()  , SIGNAL(edit(const QSharedPointer<Memory>&)),
                this        , SLOT  (edit(const QSharedPointer<Memory>&))
                );
    QObject::disconnect(
                gui.data()  , SIGNAL(editPasswordRequest(const QString &, const QString &)),
                this        , SLOT  (editPasswordRequest(const QString &, const QString &))
                );
    QObject::disconnect(
                gui.data()  , SIGNAL(reset()),
                this        , SLOT  (reset())
                );
    QObject::disconnect(
                this        , SIGNAL(getMemory(const QSharedPointer<Memory>&)),
                gui.data()  , SLOT  (getMemory(const QSharedPointer<Memory>&))
                );
    QObject::disconnect(
                this        , SIGNAL(badLogin()),
                gui.data()  , SLOT  (badLogin())
                );
    QObject::disconnect(
                this        , SIGNAL(goodEdit()),
                gui.data()  , SLOT  (goodEdit())
                );
} // disconnect_dbaccess













