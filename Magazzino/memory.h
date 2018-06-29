#ifndef MEMORY_H
#define MEMORY_H

#include <definition.h>

#include <QString>
#include <QDataStream>

//
// Classe Memory astratta
//  prototipo per MemoryManager per gli overload necessari
class Memory
{
public:
    Memory(QString typeName);

    Memory(const Memory &other);

    virtual ~Memory() = 0;

    /***
     * getName deve ritornare una QString
     *  tale che identifichi l'oggetto
     ***/
    virtual QString getName() const =0;

    /***
     * print deve ritornare un QDataStream
     *  tale che sia equivalente a operator<<
     ***/
    virtual QDataStream& print(QDataStream& os) const =0;

    /***
     * compare deve ritornare un bool
     *  tale che sia equivalente a operator== della sottoclasse
     ***/
    virtual bool compare(Memory const* other) const =0;

    /***
     * toJsonObj deve ritornare un QJsonObject
     *  tale che contenga tutte le informazioni della classe
     ***/
    virtual QJsonObject toJsonObj() const =0;

    /***
     * getTypeName
     *  unico metodo concreto di Memory
     ***/
    QString getTypeName() const;


private:
    QString type_name;
};

QDataStream& operator<<(QDataStream& os, const Memory &mem);

#endif // MEMORY_H
