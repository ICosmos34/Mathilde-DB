#include "iofile.h"

//
// IOFile
//
IOFile::IOFile()
{
    path = QDir(QDir::currentPath() + "/mathilde");

    if(!path.exists() || !QFile(path.absolutePath() + QDir::separator() + DB_NAME).exists())
        first_start();
    else
        load_mini();
} // IOFile

//
// loadAccounts
//
SPMM IOFile::loadAccounts() const
{
    SPMM select = SPMM(new MemoryManager());
    for(int i=0; i < db.size(); i++) {
        if(db[i]->getTypeName() == Account::type_name)
            select->add(db[i]);
    }

    return select;
} // loadAccounts

//
// loadProducts
//
SPMM IOFile::loadProducts() const
{
    SPMM select = SPMM(new MemoryManager());
    for(int i=0; i < db.size(); i++) {
        if(db[i]->getTypeName() == Product::type_name)
            select->add(db[i]);
    }

    return select;
}

//
// saveData
//
bool IOFile::saveData(const QString &filename)
{
    doc = QJsonArray();
    QFile file;
    file.setFileName(path.absolutePath() + "/" + filename);

    QJsonObject temp;
    const MemoryManager &data = db;

    for(int i = 0; i < db.size(); i++) {
        temp = data[i]->toJsonObj();
        temp["typename"] = data[i]->getTypeName();
        doc.append(temp);
    }

    temp = QJsonObject();
    temp["db"] = doc;
    if(file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(temp).toJson());
        file.close();
        return true;
    }
    return false;
} // saveData

//
// edit
//
bool IOFile::edit(const SPM &old, const SPM &edited)
{
    if(!(old.isNull()) || !(edited.isNull())) {
        // non esiste il vecchio => aggiunta add
        if(old.isNull() && !(edited.isNull())) {
            db.add(edited);
        }
        // non esiste il nuovo => rimozione old
        else if(!(old.isNull()) && edited.isNull()) {
            SPA temp = old.dynamicCast<Account>();
            if(
                    !(temp.isNull()) &&
                    temp->getLevel() == Account::OWNER
                )
                return false;
            else
                db.rm(old);
        }
        // old è in db e edited è valido
        else {

            if(
                old->getTypeName() == Account::type_name &&
                edited->getTypeName() == Account::type_name
            ) {
                SPA t1 = old.dynamicCast<Account>(),
                    t2 = edited.dynamicCast<Account>();
                t1->editUsername(t2->getUsername());
                t1->editLevel(t2->getLevel());
                t1->editName(t2->getPersonalName());
                t1->editSurname(t2->getSurname());
                t1->editPhone(t2->getPhone());
                t1->editEmail(t2->getEmail());
                t1->editBirthdate(t2->getBirthdate());
            } else if(
                  old->getTypeName() == Product::type_name &&
                  edited->getTypeName() == Product::type_name
              ) {
                QSharedPointer<Product> t1 = old.dynamicCast<Product>(),
                    t2 = edited.dynamicCast<Product>();
                t1->editName(t2->getName());
                t1->editQuantity(t2->getQuantity());
                t1->editMarca(t2->getMarca());
                t1->editEan13(t2->getEan13());
                t1->editDescription(t2->getDescription());
            }
        }
        return saveData();
    }
    return false;

} // edit

//
// add
//
bool IOFile::add(const SPM &newOne)
{
    if(db.add(newOne))
        return saveData();
    return false;
} // add

//
// search
//
SPM IOFile::search(const QString &content)
{
    return db.search(content);
} // search

//
// at
//
SPM IOFile::at(const int &index)
{
    if(index < 0 || index >= db.size())
        return SPM();

    return db[index];
} // at

//
// first_start
//
void IOFile::first_start()
{
    QDir().mkpath( path.absolutePath() );

    create_db();
} // first_start

//
// create_accounts
//
void IOFile::create_db()
{
    MemoryManager all;
    all.add(SPM(new Account("admin", Account::PWD::createPWD("admin"), Account::OWNER)));
    demo(all);

    db = all;
    saveData();
} // create_db

//
// demo
//
void IOFile::demo(MemoryManager &demo_obj)
{
    MemoryManager::add(demo_obj, SPM(new Account("reader", Account::PWD::createPWD("reader"), Account::READER)));
    MemoryManager::add(demo_obj, SPM(new Product("Tastiera G910", 1, "Logitech", "0097855107671", "G910 Orion Spark Mechanical Gaming Keyboard")));
    MemoryManager::add(demo_obj, SPM(new Product("Mouse G502", 1, "Logitech", "0097855105103", "G502 Proteus Core Tunable Gaming Mouse")));
    MemoryManager::add(demo_obj, SPM(new Product("PRO", 1, "Logitech", "0097855127327", "Logitech Pro Mechanical Gaming Keyboard")));
    MemoryManager::add(demo_obj, SPM(new Product("X56 H.O.T.A.S.", 1, "Logitech", "0097855127860", "Logitech Saitek Pro Flight X56 Rhino Hotas")));
}

//
// readJSonFile
//
QJsonObject IOFile::readJSonFile(const QString &filename) const
{
    QFile file;
    file.setFileName(path.absolutePath() + QDir::separator() + filename);

    QString data = QString();
    if(file.open(QIODevice::ReadOnly)) {
        data = QString(file.readAll());
        file.close();
    }
    return QJsonDocument::fromJson(data.toUtf8()).object();
} // readJsonFile

//
// load_mini
//
void IOFile::load_mini()
{
    doc = readJSonFile("db.json")["db"].toArray();

    bool admin_missing = true;
    QJsonArray::const_iterator it;
    SPM mem;
    QJsonObject temp;

    for ( it = doc.begin(); it != doc.end(); it++ ) {
        temp = (*it).toObject();
        if(temp["typename"] == Account::type_name) {
            mem = SPM(new Account(temp));
            if(admin_missing)
                admin_missing = !(temp["level"].toInt() == Account::OWNER);
        } else if(temp["typename"] == Product::type_name)
            mem = SPM(new Product(temp));

        db.add(mem);
    }

    if(admin_missing) {
        db.add(SPM(new Account("admin", Account::PWD::createPWD("admin"), Account::OWNER)));
    }
} // load_mini
