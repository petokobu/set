#include <iostream>
#include "set.h"

Set::Set()
{
    buckets = new RBTree[BASE_SIZE];
    size = 0;
    iter_inx = 0;
}

Set::~Set()
{ delete[] buckets; }

bool Set::add(int key)
{
    unsigned inx = hash(key) % BASE_SIZE;
    if (!buckets[inx].add(key)) return false;
    ++size;
    return true;
}

bool Set::contains(int key)
{
    unsigned inx = hash(key) % BASE_SIZE;
    return buckets[inx].contains(key);
}

bool Set::remove(int key)
{
    unsigned inx = hash(key) % BASE_SIZE;
    if (!buckets[inx].remove(key)) return false;
    --size;
    return true;
}

unsigned Set::len()
{ return size; }

void Set::reset_iter()
{
    iter_inx = 0;
    if (!buckets[iter_inx].is_empty())
    {
        buckets[iter_inx].reset_iter();
    }
}

bool Set::get_next(int *store)
{
    if (!buckets[iter_inx].get_next(store))
    {
        for (++iter_inx; iter_inx < BASE_SIZE
             && buckets[iter_inx].is_empty(); ++iter_inx) ;
        if (iter_inx == BASE_SIZE)
        {
            reset_iter();
            return false;
        }
        buckets[iter_inx].reset_iter();
        return buckets[iter_inx].get_next(store);
    }
    return true;
}

unsigned Set::hash(int key)
{
    unsigned ukey = (unsigned)key;
    ukey ^= ukey >> 16;
    ukey *= 0x7feb352du;
    ukey ^= ukey >> 15;
    ukey *= 0x846ca68du;
    ukey ^= ukey >> 16;
    return ukey;
}

void print(Set &set)
{
    set.reset_iter();
    int key;
    while (set.get_next(&key)) std::cout << key << " ";
}
