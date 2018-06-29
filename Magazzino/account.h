#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <definition.h>
#include <memory.h>

#include <QString>
#include <QSharedPointer>
#include <QDate>
#include <QJsonObject>
#include <QCryptographicHash>

#define EMPTY QString()
#define TODAY QDate::currentDate()

//
// Account
//
class Account: virtual public Memory
{
public:
    // costanti per permessi di accesso
    static const unsigned char
        OWNER ,
        READER,
        CREATE,
        DELETE,
        EDIT  ;

    static const QString type_name;

    class PWD {
    public:
        // passare password criptata
        PWD(const QString &encrypted = EMPTY);

        PWD(const PWD &other);

        ~PWD();

        // passare password non criptata
        static PWD createPWD(const QString &clear);

        bool operator==(const PWD &other) const;
        bool operator!=(const PWD &other) const;

        /***
         * Passare password non criptate
         *
         * ritorna true sse oldOne è coincidente con quella salvata
         * newOne diventa la nuova password
         ***/
        bool editPWD(const QString &oldClear, const QString &newClear);

        // per salvataggio su file
        const QString getEncrypted() const;

    private:
        /***
         * pwd è sempre contenuta criptata
         ***/
        QString pwd;

        // metodo di criptazione
        static void crypt(QString &pwd);

    }; // class PWD

    /***
     * Costruttore a 7 6 5 4 3 2 parametri
     *  oggetto di classe Account non costruibile senza almeno username e password
     * Password viene gestita criptata, in chiaro solo per confronto
     ***/
    Account(const QString &username = EMPTY, const PWD &password = PWD(EMPTY),
            const unsigned char &capability = READER, const QString &nome = EMPTY,
            const QString &cognome = EMPTY, const QDate &birthdate = TODAY,
            const QString &phone = EMPTY, const QString &email = EMPTY);

    /***
     * costruttore di copia
     ***/
    Account(const Account &other);

    /***
     * Costruttore da Json
     ***/
    Account(const QJsonObject &obj);

    virtual ~Account();

    //
    // Overload Memory::getName
    //
    virtual QString getName() const;

    //
    // Overload Memory::print
    //
    virtual QDataStream& print(QDataStream& os) const;

    //
    // Overload Memory::compare
    //
    virtual bool compare(Memory const* other) const;

    //
    // Overload Memory::toJsonObj
    //
    virtual QJsonObject toJsonObj() const;

    /***
     * Operatori di uguaglianza
     ***/
    bool operator==(const Account &other) const;
    bool operator!=(const Account &other) const;

    /***
     * Metodi di accesso alle componenti dell'account
     *
     * getItem ritorna l'Item richiesto
     *
     * editItem modifica l'oggetto come richiesto
     *  ritorna true sse la modifica va a buon fine
     ***/
    QString getUsername() const;
    bool editUsername(const QString &newOne);

    const QString getEncryptedPassword() const;
    bool editPWD(const QString &oldOne, const QString &newOne);

    unsigned char getLevel() const;
    bool editLevel(const unsigned char &newOne);

    QString getPersonalName() const;
    bool editName(const QString &newOne);

    QString getSurname() const;
    bool editSurname(const QString &newOne);

    QDate getBirthdate() const;
    bool editBirthdate(const QDate &newOne);

    QString getPhone() const;
    bool editPhone(const QString &newOne);

    QString getEmail() const;
    bool editEmail(const QString &newOne);

private:
    // account info !null
    QString usrname;
    Account::PWD pwd;

    // livello di utenza e privilegi bit-a-bit
    unsigned char level;

    /***
     * personal info
     * possono essere null
     ***/
    QString name, surname, phone, email;
    QDate bdate;

};

#undef EMPTY

#endif // ACCOUNT_H
