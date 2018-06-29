#include "login.h"
#include "ui_login.h"


Login::Login(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    ui->icon->setPixmap(Definition::getFrameIcon());
    ui->name->setFont(QFont("Mathilde", 40));

    ui->error->setText(" ");

    setWindowTitle(QCoreApplication::applicationName());
    setWindowIcon(QIcon(":/icon.png"));
    setFixedSize(minimumSizeHint());
    setGeometry( QStyle::alignedRect( Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry() ) );
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_clicked()
{
    QString pass = ui->password->text(),
            usr  = ui->username->text();

    if(pass.isEmpty() || usr.isEmpty())
        ui->error->setText("Invalid Login");
    else
        emit loginTry(usr, Account::PWD::createPWD(pass).getEncrypted());
}

void Login::badLogin()
{
    ui->error->setText("Invalid Login");
}

void Login::keyPressEvent(QKeyEvent* e)
{
    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
        on_login_clicked();
}
