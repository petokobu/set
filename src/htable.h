#include "bucket.h"
#include "cache.h"

#pragma once

class HTable
{
    public:
        HTable(int base_size, bool lite = false);
        ~HTable();

        bool add(int key);
        bool contains(int key);
        bool remove(int key);

        void reset_iter();
        bool get_next(int *store);

    private:
        Bucket **buckets;
        int base_size;
        int iter_inx;
        bool lite;

        unsigned hash(int key);
};
