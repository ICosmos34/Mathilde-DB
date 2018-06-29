#include "adminui.h"
#include "ui_adminui.h"

AdminUI::AdminUI(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::AdminUI)
{
    ui->setupUi(this);

    ui->name->setFont(QFont("Mathilde", 40));

    setWindowTitle(QCoreApplication::applicationName());
    setWindowIcon(QIcon(":/icon.png"));
    setFixedSize(minimumSizeHint());
    setGeometry( QStyle::alignedRect( Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry() ) );
}

AdminUI::~AdminUI()
{
    delete ui;
}

void AdminUI::on_manage_database_clicked()
{
    emit itemsDbRequest();
}

void AdminUI::on_manage_account_clicked()
{
    emit accountsDbRequest();
}

void AdminUI::on_quit_clicked()
{
    emit quitRequest();
}

void AdminUI::on_logout_clicked()
{
    emit logoutRequest();
}
