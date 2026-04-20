#include "../src/htable.h"
#include "../src/cache.h"

#pragma once

enum
{
    HTABLE_SIZE = 256,
    CACHE_SIZE = HTABLE_SIZE / 4
};

class Set
{
    public:
        Set(bool lite = false);
        ~Set();

        bool add(int key);
        bool contains(int key);
        bool remove(int key);

        unsigned len();

        void reset_iter();
        bool get_next(int *store);

        void flush();

    private:
        HTable *htable;
        Cache *cache;
        unsigned size;

    friend void print(Set &set);
    friend void print(Set *set);
};

void print(Set &set);
void print(Set *set);
