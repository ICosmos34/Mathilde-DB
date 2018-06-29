#ifndef PRODUCT_H
#define PRODUCT_H

#ifndef SPP
#define SPP QSharedPointer<Product>
#endif // SPP

#include <definition.h>
#include <memory.h>

#include <QString>
#include <QSharedPointer>
#include <QJsonObject>
#include <QDataStream>

#define EMPTY QString()
/***
 * Classe di gestione dei prodotti (su RAM)
 * I/O su file
 ***/
class Product : virtual public Memory
{
public:

    static const QString type_name;

    /***
     * Costruttore a 2 1 0 parametri
     * Non valuta se il nodo generato sia valido o meno
     * Genera un nuovo elemento dell'albero slegato
     ***/
    Product(const QString& name, const int& quantity,
            const QString& marca = EMPTY, const QString& ean13 = EMPTY,
            const QString& description = EMPTY);

    /***
     * Costruttore di copia
     ***/
    Product(const Product&);

    /***
     * Costruttore da Json
     ***/
    Product(const QJsonObject &obj);

    /***
     * Distruttore
     ***/
    virtual ~Product();

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

    //
    // Overload operatori di uguaglianza
    //
    bool operator==(const Product& compare) const;
    bool operator!=(const Product& compare) const;
    // Overload operatori per analisi lessicografica sul nome
    bool operator> (const Product& compare) const;
    bool operator< (const Product& compare) const;
    bool operator>=(const Product& compare) const;
    bool operator<=(const Product& compare) const;

    bool editName(const QString& newName);

    int getQuantity() const;
    bool editQuantity(const int& newQuantity);
    void addQuantity(const int& add);

    QString getMarca() const;
    bool editMarca(const QString &newOne);

    QString getEan13() const;
    bool editEan13(const QString &newOne);

    QString getDescription() const;
    bool editDescription(const QString &newOne);


protected:

    QString name, marca, ean13, description;

    int qta;

}; // Product

#undef EMPTY

QDataStream& operator<<(QDataStream& os, const Product &pdc);

#endif // PRODUCT_H
