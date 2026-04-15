#include "rbtree.h"

#pragma once

enum
{
    BASE_SIZE = 256
};

class Set
{
    public:
        Set();
        ~Set();

        bool add(int key);
        bool contains(int key);
        bool remove(int key);

        unsigned len();

        void reset_iter();
        bool get_next(int *store);

    private:
        RBTree *buckets;
        unsigned size;
        int iter_inx;

        unsigned hash(int key);

    friend void print(Set &set);
};

void print(Set &set);
