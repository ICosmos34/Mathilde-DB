#ifndef IOFILE_H
#define IOFILE_H

#include <definition.h>
#include <memory.h>
#include <account.h>
#include <product.h>
#include <memorymanager.h>

#include <QDir>
#include <QDate>
#include <QIODevice>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class IOFile
{
public:
    IOFile();

    SPMM loadAccounts() const;
    SPMM loadProducts() const;

    bool edit(const SPM &old, const SPM &edited);
    bool add(const SPM &newOne);
    SPM at(const int &index);
    SPM search(const QString &content);

private:
    QDir path;
    MemoryManager db;
    QJsonArray doc;

    bool saveData(const QString &filename = DB_NAME);

    void first_start();

    void create_db();
    static void demo(MemoryManager &demo_obj);

    QJsonObject readJSonFile(const QString &filename) const;

    void load_mini();
};

#undef SPP

#endif // IOFILE_H
