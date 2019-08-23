#pragma once

#include <algorithm>
#include <inttypes.h>

namespace util
{
/**
 * Basisklasse aller Speicher
 */
template <class T, class TAlloc = std::allocator<T>>
class StorageBase
{
protected:
    TAlloc allocator;

public:
    virtual T &At(uint32_t);
    virtual const T &At(uint32_t) const;

    virtual void Add(const T &);
    virtual void Add(T &&);
    virtual void Remove(const T &);
};

/**
 * Speicher für ein Array fester Länge.
 * N: Anzahl der Elemente im Array.
 */
template <class T, uint32_t N, class TAlloc = std::allocator<T>>
class FixedArrayStorage
{
};

/**
 * Speicher für ein Array fester Länge, wobei die Größe des Arrays bei der Initialisierung festgelegt wird.
 */
template <class T, class TAlloc = std::allocator<T>>
class StaticArrayStorage
{
};

/**
 * Speicher für ein dynamisch vergrößerbares Array.
 */
template <class T, class TAlloc = std::allocator<T>>
class DynamicArrayStorage
{
};

/**
 * Speicher für eine verlinkte Liste von Arrays.
 * B: Anzahl Elemente pro Block.
 */
template <class T, uint32_t B, class TAlloc = std::allocator<T>>
class LinkedArrayStorage
{
};
} // namespace util
