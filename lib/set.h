#include "../src/htable.h"

#pragma once

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

    private:
        HTable *htable;
        unsigned size;

    friend void print(Set &set);
};

void print(Set &set);
