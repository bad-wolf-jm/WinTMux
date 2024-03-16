#pragma once

#include <vector>

#include <cassert>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <vector>

template <class T>
class ringbuffer_t
{
    using value_type      = T;
    using reference       = T &;
    using const_reference = const T &;
    using size_type       = size_t;
    using container_type  = std::vector<value_type>;

    container_type  _array;
    size_type       _head;
    size_type       _tail;
    size_type       _contents_size;
    const size_type _array_size;

  public:
    ringbuffer_t( size_type size = 8 )
        : _array( size )
        , _array_size( size )
        , _head( 1 )
        , _tail( 0 )
        , _contents_size( 0 )
    {
        assert( _array_size > 1 && "size must be greater than 1" );
    }
    ringbuffer_t( std::initializer_list<T> l )
        : _array( l )
        , _array_size( l.size() )
        , _head( 0 )
        , _tail( l.size() - 1 )
        , _contents_size( l.size() )
    {
        assert( _array_size > 1 && "size must be greater than 1" );
    }

    template <bool isconst>
    struct my_iterator;
    reference front()
    {
        return _array[_head];
    }
    reference top()
    {
        return front();
    }
    reference back()
    {
        return _array[_tail];
    }
    const_reference front() const
    {
        return _array[_head];
    }
    const_reference back() const
    {
        return _array[_tail];
    }
    void clear();
    void push_back( const value_type &item );
    void push( const value_type &item )
    {
        push_back( item );
    }
    void pop_front()
    {
        increment_head();
    }
    void pop()
    {
        pop_front();
    }
    size_type size() const
    {
        return _contents_size;
    }
    size_type capacity() const
    {
        return _array_size;
    }
    bool empty() const;
    bool full() const;

    size_type max_size() const
    {
        return size_type( -1 ) / sizeof( value_type );
    }
    reference       operator[]( size_type index );
    const_reference operator[]( size_type index ) const;
    reference       at( size_type index );
    const_reference at( size_type index ) const;

    using iterator       = my_iterator<false>;
    using const_iterator = my_iterator<true>;
    iterator       begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator       rbegin();
    const_iterator rbegin() const;
    iterator       end();
    const_iterator end() const;
    const_iterator cend() const;
    iterator       rend();
    const_iterator rend() const;

  private:
    void increment_tail();
    void increment_head();

    template <bool isconst = false>
    struct my_iterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = long long;
        using reference         = typename std::conditional_t<isconst, T const &, T &>;
        using pointer           = typename std::conditional_t<isconst, T const *, T *>;
        using vec_pointer       = typename std::conditional_t<isconst, std::vector<T> const *, std::vector<T> *>;

      private:
        vec_pointer ptrToBuffer;
        size_type   offset;
        size_type   index;
        bool        reverse;

        bool comparable( const my_iterator &other )
        {
            return ( reverse == other.reverse );
        }

      public:
        my_iterator()
            : ptrToBuffer( nullptr )
            , offset( 0 )
            , index( 0 )
            , reverse( false )
        {
        } //
        my_iterator( const my_iterator & )            = delete;
        my_iterator( my_iterator && )                 = delete;
        my_iterator &operator=( const my_iterator & ) = delete;
        my_iterator &operator=( my_iterator && )      = delete;
        my_iterator( const ringbuffer_t<T>::my_iterator<false> &i )
            : ptrToBuffer( i.ptrToBuffer )
            , offset( i.offset )
            , index( i.index )
            , reverse( i.reverse )
        {
        }
        reference operator*()
        {
            if( reverse )
                return ( *ptrToBuffer )[( ptrToBuffer->size() + offset - index ) % ( ptrToBuffer->size() )];
            return ( *ptrToBuffer )[( offset + index ) % ( ptrToBuffer->size() )];
        }
        reference operator[]( size_type index )
        {
            my_iterator iter = *this;
            iter.index += index;
            return *iter;
        }
        pointer operator->()
        {
            return &( operator*() );
        }

        my_iterator &operator++()
        {
            ++index;
            return *this;
        };
        my_iterator operator++( int )
        {
            my_iterator iter = *this;
            ++index;
            return iter;
        }
        my_iterator &operator--()
        {
            --index;
            return *this;
        }
        my_iterator operator--( int )
        {
            my_iterator iter = *this;
            --index;
            return iter;
        }
        friend my_iterator operator+( my_iterator lhs, int rhs )
        {
            lhs.index += rhs;
            return lhs;
        }
        friend my_iterator operator+( int lhs, my_iterator rhs )
        {
            rhs.index += lhs;
            return rhs;
        }
        my_iterator &operator+=( int n )
        {
            index += n;
            return *this;
        }
        friend my_iterator operator-( my_iterator lhs, int rhs )
        {
            lhs.index -= rhs;
            return lhs;
        }
        friend difference_type operator-( const my_iterator &lhs, const my_iterator &rhs )
        {
            lhs.index -= rhs;
            return lhs.index - rhs.index;
        }
        my_iterator &operator-=( int n )
        {
            index -= n;
            return *this;
        }
        bool operator==( const my_iterator &other )
        {
            if( comparable( other ) )
                return ( index + offset == other.index + other.offset );
            return false;
        }
        bool operator!=( const my_iterator &other )
        {
            if( comparable( other ) )
                return !this->operator==( other );
            return true;
        }
        bool operator<( const my_iterator &other )
        {
            if( comparable( other ) )
                return ( index + offset < other.index + other.offset );
            return false;
        }
        bool operator<=( const my_iterator &other )
        {
            if( comparable( other ) )
                return ( index + offset <= other.index + other.offset );
            return false;
        }
        bool operator>( const my_iterator &other )
        {
            if( comparable( other ) )
                return !this->operator<=( other );
            return false;
        }
        bool operator>=( const my_iterator &other )
        {
            if( comparable( other ) )
                return !this->operator<( other );
            return false;
        }
        friend class ringbuffer_t<T>;
    };
};

template <class T>
void ringbuffer_t<T>::push_back( const value_type &item )
{
    increment_tail();
    if( _contents_size > _array_size )
        increment_head(); // > full, == comma
    _array[_tail] = item;
}

template <class T>
void ringbuffer_t<T>::clear()
{
    _head = 1;
    _tail = _contents_size = 0;
}

template <class T>
bool ringbuffer_t<T>::empty() const
{
    if( _contents_size == 0 )
        return true;
    return false;
}

template <class T>
inline bool ringbuffer_t<T>::full() const
{
    if( _contents_size == _array_size )
        return true;
    return false;
}

template <class T>
typename ringbuffer_t<T>::const_reference ringbuffer_t<T>::operator[]( size_type index ) const
{
    index += _head;
    index %= _array_size;
    return _array[index];
}

template <class T>
typename ringbuffer_t<T>::reference ringbuffer_t<T>::operator[]( size_type index )
{
    const ringbuffer_t<T> &constMe = *this;
    return const_cast<reference>( constMe.operator[]( index ) );
    //  return const_cast<reference>(static_cast<const ring<T>&>(*this)[index]);
}
//*/

template <class T>
typename ringbuffer_t<T>::reference ringbuffer_t<T>::at( size_type index )
{
    if( index < _contents_size )
        return this->operator[]( index );
    throw std::out_of_range( "index too large" );
}

template <class T>
typename ringbuffer_t<T>::const_reference ringbuffer_t<T>::at( size_type index ) const
{
    if( index < _contents_size )
        return this->operator[]( index );
    throw std::out_of_range( "index too large" );
}

template <class T>
typename ringbuffer_t<T>::iterator ringbuffer_t<T>::begin()
{
    iterator iter;
    iter.ptrToBuffer = &_array;
    iter.offset      = _head;
    iter.index       = 0;
    iter.reverse     = false;
    return iter;
}

template <class T>
typename ringbuffer_t<T>::const_iterator ringbuffer_t<T>::begin() const
{
    const_iterator iter;
    iter.ptrToBuffer = &_array;
    iter.offset      = _head;
    iter.index       = 0;
    iter.reverse     = false;
    return iter;
}

template <class T>
typename ringbuffer_t<T>::const_iterator ringbuffer_t<T>::cbegin() const
{
    const_iterator iter;
    iter.ptrToBuffer = &_array;
    iter.offset      = _head;
    iter.index       = 0;
    iter.reverse     = false;
    return iter;
}

template <class T>
typename ringbuffer_t<T>::iterator ringbuffer_t<T>::rbegin()
{
    iterator iter;
    iter.ptrToBuffer = &_array;
    iter.offset      = _tail;
    iter.index       = 0;
    iter.reverse     = true;
    return iter;
}

template <class T>
typename ringbuffer_t<T>::const_iterator ringbuffer_t<T>::rbegin() const
{
    const_iterator iter;
    iter.ptrToBuffer = &_array;
    iter.offset      = _tail;
    iter.index       = 0;
    iter.reverse     = true;
    return iter;
}

template <class T>
typename ringbuffer_t<T>::iterator ringbuffer_t<T>::end()
{
    iterator iter;
    iter.ptrToBuffer = &_array;
    iter.offset      = _head;
    iter.index       = _contents_size;
    iter.reverse     = false;
    return iter;
}

template <class T>
typename ringbuffer_t<T>::const_iterator ringbuffer_t<T>::end() const
{
    const_iterator iter;
    iter.ptrToBuffer = &_array;
    iter.offset      = _head;
    iter.index       = _contents_size;
    iter.reverse     = false;
    return iter;
}

template <class T>
typename ringbuffer_t<T>::const_iterator ringbuffer_t<T>::cend() const
{
    const_iterator iter;
    iter.ptrToBuffer = &_array;
    iter.offset      = _head;
    iter.index       = _contents_size;
    iter.reverse     = false;
    return iter;
}

template <class T>
typename ringbuffer_t<T>::iterator ringbuffer_t<T>::rend()
{
    iterator iter;
    iter.ptrToBuffer = &_array;
    iter.offset      = _tail;
    iter.index       = _contents_size;
    iter.reverse     = true;
    return iter;
}

template <class T>
typename ringbuffer_t<T>::const_iterator ringbuffer_t<T>::rend() const
{
    const_iterator iter;
    iter.ptrToBuffer = &_array;
    iter.offset      = _tail;
    iter.index       = _contents_size;
    iter.reverse     = true;
    return iter;
}

template <class T>
void ringbuffer_t<T>::increment_tail()
{
    ++_tail;
    ++_contents_size;
    if( _tail == _array_size )
        _tail = 0;
}

template <class T>
void ringbuffer_t<T>::increment_head()
{
    if( _contents_size == 0 )
        return;
    ++_head;
    --_contents_size;
    if( _head == _array_size )
        _head = 0;
}
