#pragma once

#include <Array/FactorArray.h>

template< class Ty, class Cont = FactorArray< std::pair< size_t, Ty > > >
class PQueueHeap
{
public:
    using size_type = size_t;
    using priority_type = size_t;
    using value_type = std::pair< priority_type, Ty >;

    PQueueHeap() = default;
    ~PQueueHeap() = default;

    void enqueue( const Ty& item, priority_type priority = 0 )
    {
        AddElement( m_data, std::make_pair( priority, item ), &compare );
    }
    Ty dequeue()
    {
        Ty item = m_data.get( 0 ).second;
        RemoveElement( m_data, 0, &compare );
        return item;
    }
    bool isEmpty() const
    {
        return m_data.size() == 0;
    }
private:

    static bool compare( const value_type& lhs, const value_type& rhs )
    {
        /// подставляем больше, т.к. хотим более приоритетный(больший) элемент был наверху
        return lhs.first > rhs.first;
    }

    size_type m_size = 0;
    size_type m_last = 0;
    Cont m_data;
};