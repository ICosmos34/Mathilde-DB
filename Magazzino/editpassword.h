#ifndef EDITPASSWORD_H
#define EDITPASSWORD_H

#include <QDialog>
#include <QDesktopWidget>

namespace Ui {
class EditPassword;
}

class EditPassword : public QDialog
{
    Q_OBJECT

public:
    explicit EditPassword(QWidget *parent = 0);
    ~EditPassword();

signals:
    bool editPassword(const QString &oldOne, const QString &newOne);

private slots:
    void on_cancel_clicked();

    void on_confirm_clicked();

private:
    Ui::EditPassword *ui;
};

#endif // EDITPASSWORD_H
