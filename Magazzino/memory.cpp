#include "memory.h"

//
// Memory
//
Memory::Memory(QString typeName)
    : type_name(typeName){} // Memory

//
// Memory (copia)
//
Memory::Memory(const Memory &other)
    : type_name(other.type_name) {} // Memory (copia)

//
// ~Memory
//
Memory::~Memory() {} // ~Memory

//
// getTypeName
//
QString Memory::getTypeName() const
{
    return type_name;
} // getTypeName

QDataStream& operator<<(QDataStream& os, const Memory &mem)
{
    os << mem.getTypeName() << "\n";
    return os;
}
