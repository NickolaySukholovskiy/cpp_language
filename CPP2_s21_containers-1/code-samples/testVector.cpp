#include "testVector.h"

/*
IMPLEMENTATION FILE
*/

template <typename T>
void Vector<T>::reserve_more_capacity(size_t Size)
{
    if (Size > m_capacity)
    {
        value_type *buff = new value_type[Size];
        for (size_t i = 0; i < m_size; ++i)
            buff[i] = std::move(arr[i]);
        delete[] arr;
        arr = buff;
        m_capacity = Size;
    }
}

// initializer list constructor (allows creating lists with initializer lists, see main.cpp)
template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const &items)
{
    arr = new value_type[items.Size()];
    int i = 0;
    for (auto it = items.begin(); it != items.end(); it++)
    {
        arr[i] = *it;
        i++;
    }
    m_size = items.Size();
    m_capacity = items.Size();
};

template <typename T>
size_t Vector<T>::Size()
{
    return m_size;
}

template <typename T>
T Vector<T>::At(size_type i)
{
    return arr[i];
}

template <typename T>
void Vector<T>::push_back(T v)
{
    if (m_size == m_capacity)
    {
        reserve_more_capacity(m_size * 2);
    }
    arr[m_size++] = v;
}

// externalizing template instances for correct linking, feel free to find more information
template class Vector<int>;
