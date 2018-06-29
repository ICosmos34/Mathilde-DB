#include "account.h"

//
// permessi
//
const unsigned char
    Account::OWNER   = 0xFF,
    Account::READER  = 0x00,
    Account::CREATE  = 0x01,
    Account::DELETE  = 0x02,
    Account::EDIT    = 0x04;

const QString Account::type_name = "Account";

//
// PWD
//
Account::PWD::PWD(const QString &encrypted)
    : pwd(encrypted) {} // PWD

//
// PWD (copia)
//
Account::PWD::PWD(const PWD &other)
    : pwd(other.pwd)
{} // PWD (copia)

//
// ~PWD
//
Account::PWD::~PWD() {} // ~PWD

//
// createPWD
//
Account::PWD Account::PWD::createPWD(const QString &clear)
{
    PWD tmp = PWD(clear);
    PWD::crypt(tmp.pwd);
    return tmp;
} // createPWD

//
// operator ==
//
bool Account::PWD::operator==(const Account::PWD &other) const
{
    return *pwd.data() == *other.pwd.data();
} // operator ==

//
// operator !=
//
bool Account::PWD::operator!=(const Account::PWD &other) const
{
    return !(*this==other);
} // operator !=

//
// editPWD
//
bool Account::PWD::editPWD(const QString &oldClear, const QString &newClear)
{
    QString tmp = oldClear;
    crypt(tmp);
    if(tmp == pwd) {
        tmp = newClear;
        crypt(tmp);
        pwd = tmp;
        return true;
    }
    tmp.clear();
    return false;
} // editPWD

//
// getEncrypted
//
const QString Account::PWD::getEncrypted() const
{
    return pwd;
} // getEncrypted

//
// crypt
//
void Account::PWD::crypt(QString &pwd)
{
    QCryptographicHash password (QCryptographicHash::Md4);
    password.addData(pwd.toUtf8());
    pwd = QString(password.result().toHex());
} // crypt

//
// Account
//
Account::Account(const QString & username, const PWD &password,
                 const unsigned char &capability, const QString & nome,
                 const QString & cognome, const QDate & birthdate,
                 const QString & phone, const QString & email)
    :Memory(type_name), usrname(username), pwd(password), level(capability),
      name(nome), surname(cognome), phone(phone), email(email), bdate(birthdate)
{} // Account

//
// Account (copia)
//
Account::Account(const Account &other)
    :Memory(type_name), pwd(other.pwd) {} // Account (copia)

//
// Account (Json)
//
Account::Account(const QJsonObject &obj)
    : Memory("Account")
{
    if(!obj["username"].isNull() && !obj["pwd"].isNull()) {
        usrname = obj["username"].toString();
        pwd = obj["pwd"].toString();
        level = (unsigned char) obj["level"].toInt();
        name = obj["name"].toString();
        surname = obj["surname"].toString();
        bdate = QDate::fromString(obj["bdate"].toString(), "yyyy/MM/dd");
        phone = obj["phone"].toString();
        email = obj["email"].toString();

    }
}

//
// ~Account
//
Account::~Account() {} // ~Account

//
// getName
//
QString Account::getName() const
{
    return usrname;
}

//
// print
//
QDataStream& Account::print(QDataStream &os) const
{

    return operator<<(os, *this);
} // print

//
// compare
//
bool Account::compare(Memory const* other) const
{
    Account const* tmp = dynamic_cast<Account const*>(other);
    if(tmp == 0)
        return false;
    return operator ==(*tmp);
} // compare

//
// toJsonObj
//
QJsonObject Account::toJsonObj() const
{
    QJsonObject item;
    item["username"]= getUsername();
    item["pwd"]     = getEncryptedPassword();
    item["level"]   = getLevel();
    item["name"]    = getPersonalName();
    item["surname"] = getSurname();
    item["bdate"]   = getBirthdate().toString("yyyy/MM/dd");
    item["phone"]   = getPhone();
    item["email"]   = getEmail();
    return item;
} // toJsonObj

//
//Operatori
//
bool Account::operator==(const Account& right) const
{
    return (name      ==  right.name)     &&
            (pwd      ==  right.pwd)      &&
            (level    ==  right.level)    &&
            (name     ==  right.name)     &&
            (surname  ==  right.surname)  &&
            (bdate    ==  right.bdate)    &&
            (phone    ==  right.phone)    &&
            (email    ==  right.email);
} // operator==

bool Account::operator!=(const Account& right) const
{
    return !(*this==right);
} // operator!=

//
// getUsername
//
QString Account::getUsername() const
{
    return usrname;
} // getUsername

//
// editUsername
//
bool Account::editUsername(const QString &newOne)
{
    if(!newOne.isEmpty()) {
        usrname = newOne;
        return true;
    }
    return false;
} // editUsername

//
// getEncryptedPassword
//
const QString Account::getEncryptedPassword() const
{
    return pwd.getEncrypted();
} // getEncryptedPassword

//
// editPWD
//
bool Account::editPWD(const QString &oldOne, const QString &newOne)
{
    return pwd.editPWD(oldOne, newOne);
} // editPWD

//
// getLevel
//
unsigned char Account::getLevel() const
{
    return level;
} // getlevel

//
// editLevel
//
bool Account::editLevel(const unsigned char &newOne)
{
    unsigned char temp = 0;
    temp |= (newOne & CREATE);
    temp |= (newOne & DELETE);
    temp |= (newOne & EDIT  );

    // verifico se newOne è costruito con le maschere adatte
    if(temp == newOne || newOne == OWNER) {
        level = newOne;
        return true;
    }
    return false;
} // editLevel

//
// getName
//
QString Account::getPersonalName() const
{
    return name;
} // getName

//
// editName
//
bool Account::editName(const QString &newOne)
{
    if(!newOne.isEmpty()) {
        name = newOne;
        return true;
    }
    return false;
} // editName

//
// getSurname
//
QString Account::getSurname() const
{
    return surname;
} // getSurname

//
// editSurname
//
bool Account::editSurname(const QString &newOne)
{
    if(!newOne.isEmpty()) {
        surname = newOne;
        return true;
    }
    return false;
} // editSurname

//
// getBirthdate
//
QDate Account::getBirthdate() const
{
    return bdate;
} // getBirtdate

//
// editBirthdate
//
bool Account::editBirthdate(const QDate &newOne)
{
    if(!newOne.isValid()) {
        bdate = newOne;
        return true;
    }
    return false;
} // editBirthdate

//
// getPhone
//
QString Account::getPhone() const
{
    return phone;
} // getPhone

//
// editPhone
//
bool Account::editPhone(const QString &newOne)
{
    if(!newOne.isEmpty()) {
        phone = newOne;
        return true;
    }
    return false;
} // editPhone

//
// getEmail
//
QString Account::getEmail() const
{
    return email;
} // getEmail

//
// editEmail
//
bool Account::editEmail(const QString &newOne)
{
    if(!newOne.isEmpty()) {
        email = newOne;
        return true;
    }
    return false;
} // editEmail




























