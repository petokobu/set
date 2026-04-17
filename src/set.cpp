#include <iostream>
#include "../lib/set.h"
#include "htable.h"

Set::Set(bool lite)
{
    htable = new HTable(lite);
    size = 0;
}

Set::~Set()
{ delete htable; }

bool Set::add(int key)
{
    if (!htable->add(key)) return false;
    ++size;
    return true;
}

bool Set::contains(int key)
{ return htable->contains(key); }

bool Set::remove(int key)
{
    if (!htable->remove(key)) return false;
    --size;
    return true;
}

unsigned Set::len()
{ return size; }

void Set::reset_iter()
{ htable->reset_iter(); }

bool Set::get_next(int *store)
{ return htable->get_next(store); }

void print(Set &set)
{
    set.reset_iter();
    int key;
    while (set.get_next(&key)) std::cout << key << " ";
}
