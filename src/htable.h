#include "bucket.h"

#pragma once

enum
{
    BASE_SIZE = 256
};

class HTable
{
    public:
        HTable(bool lite = false);
        ~HTable();

        bool add(int key);
        bool contains(int key);
        bool remove(int key);

        void reset_iter();
        bool get_next(int *store);

    private:
        Bucket **buckets;
        int iter_inx;
        bool lite;

        unsigned hash(int key);
};
