#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <chrono>

#include "Array/IArray.h"
#include "Array/VectorArray.h"
#include "HeapSort.h"
#include "PQueueHeap.h"

template< class Ty >
void VectorToIArray( const std::vector< Ty >& vec, IArray< Ty >& arr )
{
    for( auto& v : vec )
        arr.add( v );
}

template< class Ty >
bool CheckSort( IArray< Ty >& arr )
{
    for( size_t i = 1; i < arr.size(); ++i )
    {
        if( arr.get( i ) < arr.get( i - 1 ) )
            return false;
    }

    return true;
}

template< class S  >
void TestSort( S funcSort )
{
    constexpr size_t size = 10000;
    std::vector< int > v( size );
    std::iota( v.begin(), v.end(), 0 );

    for( size_t i = 0; i < 10000; ++i )
    {
        std::random_shuffle( v.begin(), v.end() );

        VectorArray< int > arr( size );
        VectorToIArray( v, arr );
        v = std::vector< int >();
        funcSort( arr );
        if( CheckSort( arr ) == false )
            throw std::runtime_error( "Fail sort!" );
    }
}

#define CHECK( x ) Check( x,#x " (" __FUNCSIG__  ")" );
void Check( bool b, const char* str )
{
    if( b == false )
        throw std::runtime_error( str );
}

void TestPQueue()
{
    PQueueHeap<int> p;
    p.enqueue( 10, 0 );
    p.enqueue( 11, 1 );
    p.enqueue( 9, 2 );
    p.enqueue( 8, 5 );
    p.enqueue( 7, 4 );
    p.enqueue( 6, 3 );
    p.enqueue( 5, 11 );

    // 11 - 5
    // 5  - 8
    // 4  - 7
    // 3  - 6
    // 2  - 9
    // 1  - 11
    // 0  - 10

    CHECK( p.dequeue() == 5 );
    CHECK( p.dequeue() == 8 );
    CHECK( p.dequeue() == 7 );
    CHECK( p.dequeue() == 6 );
    CHECK( p.dequeue() == 9 );
    CHECK( p.dequeue() == 11 );
    CHECK( p.dequeue() == 10 );
}

int main()
{
    try
    {
        /// Тестируем работу
        TestPQueue();
        TestSort( HeapSort<int> );
        TestSort( HeapSortIter<int> );
    }
    catch( const std::exception& err )
    {
        std::cerr << err.what() << '\n';
        return 1;
    }

    return 0;
}