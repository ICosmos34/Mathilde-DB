#include "changeui.h"
#include "ui_changeui.h"

ChangeUI::ChangeUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeUI)
{
    ui->setupUi(this);

    setWindowTitle(QCoreApplication::applicationName());
    setWindowIcon(QIcon(":/icon.png"));
    setGeometry( QStyle::alignedRect( Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry() ) );
}

ChangeUI::~ChangeUI()
{
    delete ui;
}

void ChangeUI::set(const SPM &e_item, const unsigned char &level)
{
    ui->remove->setVisible(level & Account ::DELETE);

    item = e_item.data();

    if(item->getTypeName() == Account::type_name) {

        const Account * toshow = dynamic_cast<const Account *>(item);
        // parti non necessarie nascoste
        ui->description->hide();
        ui->scroll->hide();
        ui->aa->setMinimum(1900);   ui->aa->setMaximum(QDate::currentDate().year());
        ui->mm->setMinimum(1);      ui->mm->setMaximum(12);

        // riempimento campi
        QDate bday = toshow->getBirthdate();

        ui->e_uname->setText(toshow->getUsername());
        ui->e_name->setText(toshow->getPersonalName());
        ui->e_cognome->setText(toshow->getSurname());
        ui->e_telefono->setText(toshow->getPhone());
        ui->e_email->setText(toshow->getEmail());
        // data
        ui->aa->setValue(bday.year());
        ui->mm->setValue(bday.month());
        ui->dd->setValue(bday.day());
        dd_setup();
        // capacità
        if((toshow->getLevel() != Account::OWNER) && (level == Account::OWNER)) {
            ui->skills->show();
            ui->s_create->setChecked(toshow->getLevel() & Account::CREATE);
            ui->s_create->show();
            ui->s_edit->setChecked(toshow->getLevel() & Account::EDIT);
            ui->s_edit->show();
            ui->s_delete->setChecked(toshow->getLevel() & Account::DELETE);
            ui->s_delete->show();
            ui->skills->setMinimumSize(QSize(ui->labels->minimumSize().width(), ui->skills->minimumSize().height()));
        } else {
            ui->remove->hide();
            ui->skills->hide();
            ui->s_create->hide();
            ui->s_edit->hide();
            ui->s_delete->hide();
        }

    } else if(item->getTypeName() == Product::type_name) {

        const Product * toshow = dynamic_cast<const Product *>(item);
        ui->user->setText("Nome");
        ui->password->hide();           ui->edit_password->hide();
        ui->nome->setText("Marca");
        ui->cognome->hide();            ui->e_cognome->hide();
        ui->telefono->setText("ean13");
        ui->email->hide();              ui->e_email->hide();
        ui->bday->setText("Quantità");  ui->mm->hide(); ui->aa->hide();
        ui->dd->setMinimum(0);          ui->dd->setMaximum(1000);
        ui->skills->hide();             ui->s_create->hide();
        ui->s_edit->hide();             ui->s_delete->hide();
        ui->description->setMinimumSize(QSize(ui->labels->minimumSize().width(), ui->description->minimumSize().height()));

        ui->e_uname->setText(toshow->getName());
        ui->e_name->setText(toshow->getMarca());
        ui->e_telefono->setText(toshow->getEan13());
        ui->dd->setValue(toshow->getQuantity());
        ui->e_description->document()->setPlainText(toshow->getDescription());

    } else {

        reject();

    }
}

void ChangeUI::editError(const QString &error)
{
    ui->error->setText(error);
}

//
// dd_setup
//
void ChangeUI::dd_setup()
{
    int max = QDate(ui->aa->value(), ui->mm->value(), 1).daysInMonth();
    if(ui->dd->value() > max)
        ui->dd->setValue(max);

    ui->dd->setMaximum(max);
}

void ChangeUI::on_mm_editingFinished()
{
    dd_setup();
}

void ChangeUI::on_aa_editingFinished()
{
    dd_setup();
}

void ChangeUI::on_conferma_clicked()
{
    SPM changed;
    if(item->getTypeName() == Account::type_name) {
        Account * temp = dynamic_cast<Account *>(item);
        unsigned char level = temp->getLevel();
        if(level != Account::OWNER) {
            level = 0;
            if(ui->s_create->isChecked())
                level += Account::CREATE;
            if(ui->s_edit->isChecked())
                level += Account::EDIT;
            if(ui->s_delete->isChecked())
                level += Account::DELETE;
        }
        changed = SPM(new Account(ui->e_uname->text(), Account::PWD(temp->getEncryptedPassword()),
                                  level, ui->e_name->text(),
                                  ui->e_cognome->text(), QDate(ui->aa->value(), ui->mm->value(), ui->dd->value()),
                                  ui->e_telefono->text(), ui->e_email->text()));
    } else if(item->getTypeName() == Product::type_name) {
        changed = SPM(new Product(ui->e_uname->text(), ui->dd->value(),
                                  ui->e_name->text(), ui->e_telefono->text(),
                                  ui->e_description->toPlainText()));


    }
    emit edit(changed);
    accept();
}

void ChangeUI::on_edit_password_clicked()
{
    EditPassword e_pwd;

    QObject::connect(
                &e_pwd      , SIGNAL(editPassword(const QString &, const QString &)),
                this        , SLOT  (editPasswordRequest(const QString &, const QString &))
                );

    e_pwd.exec();

    QObject::disconnect(
                &e_pwd      , SIGNAL(editPassword(const QString &, const QString &)),
                this        , SLOT  (editPasswordRequest(const QString &, const QString &))
                );

}

void ChangeUI::editPasswordRequest(const QString &oldOne, const QString &newOne)
{
    emit editPassword(oldOne, newOne);
}

void ChangeUI::on_annulla_clicked()
{
    reject();
}

void ChangeUI::on_remove_clicked()
{
    emit remove();
}
