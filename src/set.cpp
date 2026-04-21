#include <iostream>
#include "../lib/set.h"
#include "htable.h"
#include "cache.h"

Set::Set(bool lite)
{
    cache = new Cache(CACHE_SIZE);
    htable = new HTable(HTABLE_SIZE, lite);
    size = 0;
}

Set::~Set()
{
    delete cache;
    delete htable;
}

bool Set::add(int key)
{
    if (htable->contains(key)) return false;
    int rep;
    if (cache->add(key, &rep))
    {
        if (key == rep) return false;
        else htable->add(rep);
    }
    ++size;
    return true;
}

bool Set::contains(int key)
{ return cache->contains(key) || htable->contains(key); }

bool Set::remove(int key)
{
    bool in_cache = false;
    if (cache->remove(key)) in_cache = true;
    if (!htable->remove(key) && !in_cache) return false;
    --size;
    return true;
}

unsigned Set::len()
{ return size; }

void Set::reset_iter()
{
    flush();
    htable->reset_iter();
}

bool Set::get_next(int *store)
{ return htable->get_next(store); }

void Set::flush()
{
    int b_size = cache->b_size();
    for (int i = 0; i < b_size; ++i)
        if (cache->is_valid(i)) htable->add(cache->pop(i));
}

void print(Set &set)
{
    set.reset_iter();
    int key;
    while (set.get_next(&key)) std::cout << key << " ";
}

void print(Set *set)
{
    set->reset_iter();
    int key;
    while (set->get_next(&key)) std::cout << key << " ";
}
