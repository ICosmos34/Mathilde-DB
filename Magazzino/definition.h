#ifndef DEFINITION_H
#define DEFINITION_H

#include <QDebug>

#define SPS QSharedPointer<QString>

#define SPMM QSharedPointer<MemoryManager>

#define SPM QSharedPointer<Memory>

#define SPP QSharedPointer<Product>

#define SPA QSharedPointer<Account>

#define SPF QSharedPointer<QFrame>

#define DB_NAME "db.json"

#define LOCAL_DIR QDir::currentPath()


#include <QPixmap>

namespace Definition
{
    inline QPixmap getFrameIcon() {
        QPixmap temp (":/MathildeW.bmp");
        return temp.scaledToHeight(100);
    }
}

#endif // DEFINITION_H
