#include "dbaccess.h"
#include "ui_dbaccess.h"

const QStringList
    DbAccess::account_head = QStringList("Username") << "Nome"
                             << "Cognome" << "Email" << "Telefono" << "Data di Nascita",
    DbAccess::product_head = QStringList("Modello") << "Marca"
                             << "Quantità" << "EAN13" << "Descrizione";

DbAccess::DbAccess(QWidget *parent) :
    QFrame(parent), ui(new Ui::DbAccess),
    lvl(0), isAccount(false)
{
    build();
}

DbAccess::DbAccess(const SPMM &content, const QString &title, const unsigned char &level, const bool &areAccounts, QWidget *parent)
    : QFrame(parent), ui(new Ui::DbAccess), lvl(level), isAccount(areAccounts)
{
    build();
    ui->name->setText(title);

    if(lvl == Account::OWNER) {
        ui->edit_account->hide();
    } else {
        if(!(lvl & Account::CREATE))
            ui->add->hide();
        ui->go_back->hide();
    }

    setTab(content);

}

DbAccess::~DbAccess()
{
    delete ui;
}

void DbAccess::setTab(const SPMM &content)
{

    QObject::disconnect(
                ui->contentview->horizontalHeader(),
                            SIGNAL(clicked(QModelIndex)),
                this,       SLOT(head_clicked(QModelIndex))
                );
    if(content->size() == 0) {
        ui->contentview->setColumnCount(1);
        ui->contentview->setHorizontalHeaderLabels(QStringList("Contenuto"));
        ui->contentview->setRowCount(1);
        ui->contentview->setItem(0, 0, new QTableWidgetItem("Nessun contenuto"));
        ui->contentview->horizontalHeader()->setStretchLastSection(true);
    } else {

        SPA acc = (content->operator [](0)).dynamicCast<Account>();

        SPP pdc = (content->operator [](0)).dynamicCast<Product>();

        if(!acc.isNull()) {

            ui->contentview->setColumnCount(6);
            ui->contentview->setHorizontalHeaderLabels(QStringList(account_head));
            ui->contentview->setRowCount(content->size());

            for(int i = 0; i < content->size(); i++) {
                acc = (content->operator [](i)).dynamicCast<Account>();
                if(acc.isNull()) continue;
                ui->contentview->setItem(i, 0, new QTableWidgetItem(acc->getUsername()));
                ui->contentview->setItem(i, 1, new QTableWidgetItem(acc->getPersonalName()));
                ui->contentview->setItem(i, 2, new QTableWidgetItem(acc->getSurname()));
                ui->contentview->setItem(i, 3, new QTableWidgetItem(acc->getEmail()));
                ui->contentview->setItem(i, 4, new QTableWidgetItem(acc->getPhone()));
                ui->contentview->setItem(i, 5, new QTableWidgetItem(acc->getBirthdate().toString()));
            }

        }else if(!pdc.isNull()) {
            ui->contentview->setColumnCount(5);
            ui->contentview->setHorizontalHeaderLabels(QStringList(product_head));
            ui->contentview->setRowCount(content->size());

            for(int i = 0; i < content->size(); i++) {
                pdc = (content->operator [](i)).dynamicCast<Product>();
                if(pdc.isNull()) continue;
                ui->contentview->setItem(i, 0, new QTableWidgetItem(pdc->getName()));
                ui->contentview->setItem(i, 1, new QTableWidgetItem(pdc->getMarca()));
                ui->contentview->setItem(i, 2, new QTableWidgetItem(pdc->getQuantity()));
                ui->contentview->setItem(i, 3, new QTableWidgetItem(pdc->getEan13()));
                ui->contentview->setItem(i, 4, new QTableWidgetItem(pdc->getDescription()));
            }
        }
        ui->contentview->horizontalHeader()->setStretchLastSection(true);
        QObject::connect(
                    ui->contentview->horizontalHeader(),
                                SIGNAL(clicked(QModelIndex)),
                    this,       SLOT(head_clicked(QModelIndex))
                    );
    }
}

void DbAccess::on_logout_clicked()
{
    emit logoutRequest();
}

void DbAccess::on_edit_account_clicked()
{
    emit editAccountRequest();
}

void DbAccess::on_go_back_clicked()
{
    emit adminRequest();
}

void DbAccess::on_contentview_doubleClicked(const QModelIndex &index)
{
    emit editRequest(ui->contentview->item(index.row(), 0)->text());
}

void DbAccess::on_add_clicked()
{
    emit reset();

    SPM data;
    if(isAccount)
        data = SPM(new Account());
    else
        data = SPM(new Product("", 0));

    changes.set(data, false);
    connect_changes();

    changes.exec();

    disconnect_changes();
}

void DbAccess::getMemory(const SPM &data)
{
    changes.set(data, lvl);

    connect_changes();
    changes.exec();
    disconnect_changes();
}

void DbAccess::badLogin()
{
    changes.editError("Modifica non valida");
}

void DbAccess::goodEdit()
{
    changes.accept();
}

void DbAccess::edit_(const SPM &edited)
{
    emit edit(edited);
}

void DbAccess::editPassword_(const QString &oldOne, const QString &newOne)
{
    emit editPasswordRequest(oldOne, newOne);
}

void DbAccess::remove()
{
    changes.accept();
    emit edit(SPM());
}

void DbAccess::head_clicked(QModelIndex index)
{
    if(ui->contentview->rowCount() >= 2) {
        if(ui->contentview->item(0, index.column())->text() > ui->contentview->item(1,index.column())->text())
            ui->contentview->sortByColumn(index.column(), Qt::AscendingOrder);
        else
            ui->contentview->sortByColumn(index.column(), Qt::DescendingOrder);
    }
}

void DbAccess::build()
{
    ui->setupUi(this);

    ui->name->setFont(QFont("Mathilde", 40));

    setWindowTitle(QCoreApplication::applicationName());
    setWindowIcon(QIcon(":/icon.png"));
    setGeometry( QStyle::alignedRect( Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry() ) );
    ui->contentview->setEditTriggers( QAbstractItemView::NoEditTriggers );
}

void DbAccess::connect_changes()
{
    QObject::connect(
                &changes,   SIGNAL(edit(const QSharedPointer<Memory>&)),
                this,       SLOT(edit_(const QSharedPointer<Memory>&))
                );
    QObject::connect(
                &changes,   SIGNAL(editPassword(const QString &, const QString &)),
                this,       SLOT(editPassword_(const QString &, const QString &))
                );
    QObject::connect(
                &changes,   SIGNAL(remove()),
                this,       SLOT(remove())
                );
}

void DbAccess::disconnect_changes()
{
    QObject::disconnect(
                &changes,   SIGNAL(edit(const QSharedPointer<Memory>&)),
                this,       SLOT(edit_(const QSharedPointer<Memory>&))
                );
    QObject::disconnect(
                &changes,   SIGNAL(editPassword(const QString &, const QString &)),
                this,       SLOT(editPassword_(const QString &, const QString &))
                );
    QObject::disconnect(
                &changes,   SIGNAL(remove()),
                this,       SLOT(remove())
                );
}
