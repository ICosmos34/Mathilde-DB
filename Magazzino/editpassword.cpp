#include "editpassword.h"
#include "ui_editpassword.h"

EditPassword::EditPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPassword)
{
    ui->setupUi(this);

    setWindowTitle(QCoreApplication::applicationName());
    setWindowIcon(QIcon(":/icon.png"));
    setGeometry( QStyle::alignedRect( Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry() ) );
}

EditPassword::~EditPassword()
{
    delete ui;
}



void EditPassword::on_cancel_clicked()
{
    emit rejected();
}

void EditPassword::on_confirm_clicked()
{
    bool worked = emit editPassword(ui->ev_pass->text(), ui->en_pass->text());

    if(worked)
        reject();
    else
        ui->error->setText("Password non valida");
}
