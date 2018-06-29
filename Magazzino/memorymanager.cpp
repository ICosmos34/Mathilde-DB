#include <memorymanager.h>

//
// MemoryManager
//
MemoryManager::MemoryManager(SPM item)
{
    // aggiunta del primo oggetto se non nullo
    if(!item.isNull())
        mem.append(item);
} // MemoryManager

//
// MemoryManager da File
//
MemoryManager::MemoryManager(const QList<SPM> &items)
    : mem(items)
{
    // costruzione di copia nel sottooggetto da items
} // MemoryManager

//
// MemoryManager di copia
//
MemoryManager::MemoryManager(const MemoryManager &pm)
    : mem(pm.mem)
{
    // copia sul sottooggetto
} // MemoryManager

//
// ~MemoryManager
//
MemoryManager::~MemoryManager() {} // ~MemoryManager

//
// operator[]
//
const SPM MemoryManager::operator [](int i) const
{
    if(this->mem.isEmpty() || i >= mem.size() || i < 0)
        return SPM();

    return this->mem.at(i);
} // operator[]

int MemoryManager::size() const
{
    return mem.size();
}

//
// add (Da MemoryManager)
//
void MemoryManager::add(MemoryManager &pm)
{
    if(mem.isEmpty()) {
        *this = pm;
    } else {
        for(int i = 0; i < pm.mem.size(); i++) {
            if(this->add(pm[i]))
                pm.rm(pm[i]);
        }
    }
} // add

//
// add (Da MemoryManager)
//
void MemoryManager::add(MemoryManager &radix, MemoryManager &pm)
{
    radix.add(pm);
} // add

//
// add (Da Memory)
//
bool MemoryManager::add(const SPM &item)
{
    if(search(item))
        return false;

    mem.push_back(item);

    return true;
} // add

//
// add (Da Memory)
//
bool MemoryManager::add(MemoryManager &radix, const SPM &item)
{
    return radix.add(item);
} // add

//
// rm (da Memory)
//
bool MemoryManager::rm(const SPM &item)
{
    if(this->mem.isEmpty())
        return false;

    int index;
    if((index = mem.indexOf(item)) != -1){
        mem.removeAt(index);
        return true;
    }

    return false;
} // rm

//
// rm (da Memory)
//
bool MemoryManager::rm(MemoryManager &radix, const SPM &item)
{
    return radix.rm(item);
} // rm

//
// rm (da QString)
//
bool MemoryManager::rm(const QString &item)
{
    for(int i = 0; i < mem.size(); i++) {
        if(mem.at(i)->getName() == item)
            mem.removeAt(i);
            return true;
    }
    return false;
} // rm

//
// rm (da QString)
//
bool MemoryManager::rm(MemoryManager &radix, const QString &item)
{
    return radix.rm(item);
} // rm

//
// search (da Memory)
//
bool MemoryManager::search(const SPM &item) const
{
    if(mem.isEmpty())
        return false;

    return mem.indexOf(item) != -1;
} // search

//
// search (da Memory)
//
bool MemoryManager::search(const MemoryManager &radix, const SPM &item)
{
    return radix.search(item);
} // search

//
// search (da QString)
//
const SPM MemoryManager::search(const QString &item) const
{
    if(mem.isEmpty())
        return SPM();

    for(int i = 0; i < mem.size(); i++) {
        if(mem.at(i)->getName() == item)
            return SPM(mem.at(i));
    }
    return SPM();
} // search

//
// search (da QString)
//
const SPM MemoryManager::search(const MemoryManager &radix, const QString &item)
{
    return radix.search(item);
} // search

//
// operator[]
//
SPM MemoryManager::operator[](int i)
{
    if(mem.isEmpty() || i < 0 || i > mem.size())
        return SPM();

    return mem.at(i);
}

//
// operator<<
//
QDataStream& operator <<(QDataStream& os, const MemoryManager& pm)
{
    for(int i = 0; i < pm.size(); i++) {
        os << pm[i].data();
    }
    return os;
} // operator<<











