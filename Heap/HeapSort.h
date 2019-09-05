#pragma once

#include "Array/IArray.h"
#include "Array/VectorArray.h"

#include "Heap.h"

/// С выбором drown (итеративная или рекурсивная) и выбором компаратора
template< class Ty, class Drown, class Comp >
void HeapSortHelper( IArray< Ty >& arr, Drown drown, Comp comp = std::less< Ty >() )
{
    VectorArray< Ty > work_arr( arr.size() );
    for( size_t i = 0; i < arr.size(); ++i )
        work_arr.add( arr.get( i ) );

    size_t size = arr.size();
    arr.clear();
    BuildHeap( work_arr, drown, comp );
    for( size_t i = 0; i < size; ++i )
    {
        arr.add( work_arr.get( 0 ) );
        std::swap( work_arr.get( 0 ), work_arr.get( work_arr.size() - 1 ) );
        work_arr.remove( work_arr.size() - 1 );
        drown( work_arr, 0, comp );
    }
}

/// Пирамидальная сортировка через рекурсию
template< class Ty >
void HeapSort( IArray< Ty >& arr )
{
    HeapSortHelper( arr, &Drown< Ty, std::less< Ty > >, std::less< Ty >() );
}

/// Пирамидальная сортировка через итерирование
template< class Ty >
void HeapSortIter( IArray< Ty >& arr )
{
    HeapSortHelper( arr, &DrownIter< Ty, std::less< Ty > >, std::less< Ty >() );
}