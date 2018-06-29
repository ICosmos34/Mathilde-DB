#ifndef CHANGEUI_H
#define CHANGEUI_H

#include <memory.h>
#include <account.h>
#include <product.h>

#include <editpassword.h>

#include <QDate>
#include <QDialog>
#include <QDesktopWidget>

namespace Ui {
class ChangeUI;
}

class ChangeUI : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeUI(QWidget *parent = 0);

    ChangeUI(const ChangeUI &);

    ~ChangeUI();

    void set(const SPM &item, const unsigned char &level);

    void editError(const QString &);

signals:
    void edit(const SPM edited);
    void editPassword(const QString &oldOne, const QString &newOne);
    void remove();

private slots:
    void on_mm_editingFinished();
    void on_aa_editingFinished();
    void on_conferma_clicked();
    void on_edit_password_clicked();
    void editPasswordRequest(const QString &oldOne, const QString &newOne);
    void on_annulla_clicked();
    void on_remove_clicked();

private:
    Ui::ChangeUI *ui;
    Memory * item;

    void dd_setup();
};

#endif // CHANGEUI_H
