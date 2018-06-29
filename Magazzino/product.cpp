#include "product.h"

const QString Product::type_name = "Product";

//
//Costruttore a 2 1 0 parametri
//
Product::Product(const QString& name, const int& quantity,
                 const QString& marca, const QString& ean13,
                 const QString& description)
    :Memory("Product"), name(name), marca(marca), ean13(ean13),
      description(description), qta(quantity) {} // Product

//
// Product (copia)
//
Product::Product(const Product &i)
    :Memory("Product"), name(i.name), qta(i.qta) {} // Product (copia)

//
// Product (Json)
//
Product::Product(const QJsonObject & obj)
    : Memory("Product")
{
    if(!obj["name"].isNull()) {
        name        = obj["name"].toString();
        qta         = obj["quantity"].toInt();
        marca       = obj["marca"].toString();
        ean13       = obj["ean13"].toString();
        description = obj["description"].toString();
    }
}

//
//Distruttore
// va bene il distruttore di default senza ridefinizione
//
Product::~Product() {} // ~Product

//
// getName
//
QString Product::getName() const
{
    return name;
}

//
// print
//
QDataStream& Product::print(QDataStream &os) const
{

    return operator<<(os, *this);
} // print

//
// compare
//
bool Product::compare(Memory const* other) const
{
    Product const* tmp = dynamic_cast<Product const*>(other);
    if(tmp == 0)
        return false;
    return operator ==(*tmp);
} // compare

//
// toJsonObj
//
QJsonObject Product::toJsonObj() const
{
    QJsonObject item;
    item["name"]        = getName();
    item["quantity"]    = getQuantity();
    item["marca"]       = getMarca();
    item["ean13"]       = getEan13();
    item["description"] = getDescription();
    return item;
} // toJsonObj

//
//Operatori
//
bool Product::operator==(const Product& right) const
{
    return (qta==right.qta) && (name==right.name);
} // operator==

bool Product::operator!=(const Product& right) const
{
    return !(*this==right);
} // operator!=

bool Product::operator>(const Product& right) const
{
    return QString::compare(name, right.name, Qt::CaseInsensitive) > 0;
} // operator>

bool Product::operator<(const Product& right) const
{
    return QString::compare(name, right.name, Qt::CaseInsensitive) < 0;
} // operator<

bool Product::operator>=(const Product& right) const
{
    return !(operator <(right));
} // operator>=

bool Product::operator<=(const Product& right) const
{
    return !(operator >(right));
} // operator<=

//
//editName
//
bool Product::editName(const QString& newName)
{
    if(newName.isEmpty())
        return false;

    name = newName;
    return true;
} // editName

//
// getQuantity
//
int Product::getQuantity() const
{
    return qta;
} // getQuantity

//
//editQuantity
//
bool Product::editQuantity(const int& newQuantity)
{
    if(newQuantity <= -1)
        return false;

    qta = newQuantity;
    return true;
} // editQuantity

//
//addQuantity
//
void Product::addQuantity(const int& add)
{
    qta += add;

    if(qta <= -1)
        qta = -1;
} // addQuantity

//
// getMarca
//
QString Product::getMarca() const
{
    return marca;
} // getMarca

//
// editMarca
//
bool Product::editMarca(const QString &newOne)
{
    if(newOne.isEmpty())
        return false;

    marca = newOne;
    return true;
} // editMarca

//
// getEan13
//
QString Product::getEan13() const
{
    return ean13;
} // getEan13

//
// editEan13
//
bool Product::editEan13(const QString &newOne)
{
    if(newOne.isEmpty())
        return false;

    ean13 = newOne;
    return true;
} // editEan13

//
// getDescription
//
QString Product::getDescription() const
{
    return description;
} // getDescription

//
// editDescription
//
bool Product::editDescription(const QString &newOne)
{
    if(newOne.isEmpty())
        return false;

    description = newOne;
    return true;
} // editDescription

//
// operator<<
//
QDataStream& operator<<(QDataStream& os, const Product &pdc)
{
    os << "name = " << pdc.getName() << " (" << pdc.getQuantity() << ")\n";
    return os;
} // operator<<


