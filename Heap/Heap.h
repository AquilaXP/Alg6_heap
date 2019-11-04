#pragma once

#include <cmath>

#include <functional>

#include "Array/IArray.h"

template< class Ty, class Comp >
void Drown( IArray< Ty >& arr, size_t idx, Comp comp = std::less< Ty >() )
{
    size_t smallest = idx;
    size_t left = 2 * idx + 1;
    size_t right = 2 * idx + 2;

    if( left < arr.size() && comp( arr.get( left ), arr.get( smallest ) ) )
        smallest = left;
    if( right < arr.size() && comp( arr.get( right ), arr.get( smallest ) ) )
        smallest = right;
    if( smallest != idx )
    {
        std::swap( arr.get(smallest), arr.get(idx) );
        Drown( arr, smallest, comp );
    }
}

template< class Ty, class Comp >
void DrownIter( IArray< Ty >& arr, size_t idx, Comp comp = std::less< Ty >() )
{
    while( true )
    {
        size_t smallest = idx;
        size_t left = 2 * idx + 1;
        size_t right = 2 * idx + 2;

        if( left < arr.size() && comp( arr.get( left ), arr.get( smallest ) ) )
            smallest = left;
        if( right < arr.size() && comp( arr.get( right ), arr.get( smallest ) ) )
            smallest = right;
        if( smallest == idx )
            break;

        std::swap( arr.get(smallest), arr.get(idx) );
        idx = smallest;
    }
}

template< class Ty, class Comp >
void ComeUp( IArray< Ty >& arr, const Ty& v, size_t& idx, Comp comp = std::less< Ty >() )
{
    // Сравниваем с родителем, если не удовлетворяет условию меняем местами и т.д.
    // Поднимаем вверх, элемент хочет всплыть
    while( idx > 0 )
    {
        size_t parent = ( idx - 1 ) / 2;
        if( comp( arr.get( idx ), arr.get( parent ) ) )
        {
            std::swap( arr.get( idx ), arr.get( parent ) );
            idx = parent;
        }
        else
        {
            // стоит где нужно
            break;
        }
    }
}

template< class Ty, class D, class Comp >
void BuildHeap( IArray< Ty >& arr, D drown, Comp comp = std::less< Ty >() )
{
    for( ptrdiff_t i = ptrdiff_t(arr.size() - 1); i >= 0; --i )
        drown( arr, i, comp );
}

template< class Ty, class Comp >
void BuildHeap( IArray< Ty >& arr, Comp comp = std::less< Ty >() )
{
    BuildHeap( arr, &DrownIter, comp );
}

template< class Ty, class Comp >
void RemoveElement( IArray< Ty >& arr, size_t idx, Comp comp = std::less< Ty >() )
{
    std::swap( arr.get( idx ), arr.get( arr.size() - 1 ) );
    arr.remove( arr.size() - 1 );

    // "всплывает" элемент, если он не удовлетворяет условиню
    size_t p = idx;
    ComeUp( arr, arr.get( idx ), p, comp );
    // Элемент не изменил своего положения,"топим"!
    if( p == idx )
        Drown( arr, p, comp );
}

template< class Ty, class Comp >
void AddElement( IArray< Ty >& arr, const Ty& v, Comp comp = std::less< Ty >() )
{
    // Добавляем в конец
    arr.add( v );

    size_t p = arr.size() - 1;
    ComeUp( arr, v, p, comp );
}
