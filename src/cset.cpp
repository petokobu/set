#include <stdio.h>
#include "../lib/cset.h"
#include "../lib/set.h"

extern "C" {

Set *set_init(bool lite)
{ return new Set(lite); }

void set_fini(Set *set)
{ delete set; }

bool set_add(Set *set, int key)
{ return set->add(key); }

bool set_contains(Set *set, int key)
{ return set->contains(key); }

bool set_remove(Set *set, int key)
{ return set->remove(key); }

unsigned set_len(Set *set)
{ return set->len(); }

void set_reset_iter(Set *set)
{ set->reset_iter(); }

bool set_get_next(Set *set, int *store)
{ return set->get_next(store); }

void set_print(Set *set)
{
    set_reset_iter(set);
    int key;
    while (set_get_next(set, &key)) printf("%s ", key);
}

}
