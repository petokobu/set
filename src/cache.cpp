#include "cache.h"

Cache::Cache(int base_size)
{
    buckets = new int[base_size]{ 0 };
    this->base_size = base_size;
    int inx = hash(0) % base_size;
    sentinel = inx;
    sentinel_occ = false;
}

Cache::~Cache()
{ delete buckets; }

bool Cache::add(int key, int *rep)
{
    int inx = hash(key) % base_size;
    if (inx == sentinel)
    {
        if (!sentinel_occ)
        {
            buckets[inx] = key;
            sentinel_occ = true;
            return false;
        }
        *rep = buckets[inx];
        buckets[inx] = key;
        return true;
    }
    if (buckets[inx] == 0)
    {
        buckets[inx] = key;
        return false;
    }
    *rep = buckets[inx];
    buckets[inx] = key;
    return true;
}

bool Cache::contains(int key)
{
    int inx = hash(key) % base_size;
    if (inx == sentinel) return sentinel_occ;
    return buckets[inx] != 0;
}

bool Cache::remove(int key)
{
    int inx = hash(key) % base_size;
    if (buckets[inx] != key) return false;
    if (inx == sentinel)
    {
        if (!sentinel_occ) return false;
        sentinel_occ = false;
        return true;
    }
    if (buckets[inx] == 0) return false;
    buckets[inx] = 0;
    return true;
}

bool Cache::is_valid(int inx)
{
    if (inx == sentinel) return sentinel_occ;
    return buckets[inx] != 0;
}

int Cache::pop(int inx)
{
    if (inx == sentinel)
    {
        sentinel_occ = false;
        return buckets[inx];
    }
    int popped = buckets[inx];
    buckets[inx] = 0;
    return popped;
}

int Cache::b_size()
{ return base_size; }

unsigned Cache::hash(int key)
{
    unsigned ukey = (unsigned)key;
    ukey ^= ukey >> 16;
    ukey *= 0x7feb352du;
    ukey ^= ukey >> 15;
    ukey *= 0x846ca68du;
    ukey ^= ukey >> 16;
    return ukey;
}
