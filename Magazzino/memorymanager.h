#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <memory.h>
#include <definition.h>

#include <QList>
#include <QSharedPointer>
#include <QDataStream>

class MemoryManager
{
public:
    /***
     * Costruttore a 1 0 parametri
     * punta ad un Memory passato per indirizzo
     ***/
    MemoryManager(SPM item = SPM());

    /***
     * Costruttore dedicato alla preparazione di un oggetto da lettura su disco
     ***/
    MemoryManager(const QList<SPM> &items);

    /***
     * Copia profonda
     ***/
    MemoryManager(const MemoryManager &mm);

    /***
     * Distruttore virtuale
     ***/
    virtual ~MemoryManager();

    const SPM operator[](int i) const;
          SPM operator[](int i);

    int size() const;

    /***
     * Metodo di aggiunta di un nuovo Memory
     *
     * radix/this   è il riferimento all'oggetto contenitore
     * mm           è il riferimento all'oggetto da aggiungere
     *
     * radix/this   al termine contiene tutti gli oggetti di radix e mm
     * mm           al termine contiene gli oggetti già presenti precedentemente
     *              in radix che sarebbero duplicati, se non ce ne sono è un oggetto vuoto
     ***/
    void add(MemoryManager &mm);
    static void add(MemoryManager &radix, MemoryManager &mm);

    /***
     * Metodo di aggiunta di un nuovo Memory o serie di prodotti
     *
     * radix/this   è il riferimento all'oggetto contenitore
     * item         è il riferimento al Memory da aggiungere
     *
     * radix/this   al termine contiene tutti gli oggetti di radix e mm
     * se item è già presente in radix, viene ritornato false
     ***/
    bool add(const SPM &item);
    static bool add(MemoryManager &radix, const SPM &item);

    /***
     * Metodo di rimozione di un Memory dall'elenco
     *
     * radix    è il riferimento all'oggetto contenitore
     * item      è il riferimento al Memory da rimuovere
     *
     * se item non è presente in radix, viene ritornato false
     ***/
    bool rm(const SPM &item);
    static bool rm(MemoryManager &radix, const SPM &item);

    /***
     * Metodi di rimozione di un Memory data una caratteristica
     *
     * radix    è il riferimento all'oggetto contenitore
     * item      è il riferimento alla caratteristica del Memory da rimuovere
     *
     * se item non è presente in radix, viene ritornato false
     ***/
    bool rm(const QString &item);
    static bool rm(MemoryManager &radix, const QString &item);

    /***
     * Metodo di ricerca di un Memory, all'interno della struttura
     *
     * radix    è il riferimento all'oggetto contenitore
     * item      è il riferimento al Memory da trovare
     *
     * se item non è presente in radix, viene ritornato false
     ***/
    bool search(const SPM &item) const;
    static bool search(const MemoryManager &radix, const SPM &item);

    /***
     * Metodo di ricerca di un Memory, all'interno della struttura
     *
     * radix    è il riferimento all'oggetto contenitore
     * item      è il riferimento ad un attributo dell'oggetto
     *
     * ritorna il puntatore costante al Memory con il campo uguale a item
     *  se non viene trovato, il puntatore è nullo
     ***/
    const SPM search(const QString &item) const;
    static const SPM search(const MemoryManager &radix, const QString &item);

private:
    QList<SPM> mem;

}; // MemoryManager

QDataStream& operator<<(QDataStream& os, const MemoryManager& mm);

#endif // MEMORYMANAGER_H
