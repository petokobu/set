#pragma once

class Cache
{
    public:
        Cache(int base_size);
        ~Cache();

        bool add(int key, int *rep);
        bool contains(int key);
        bool remove(int key);

        bool is_valid(int inx);
        int pop(int inx);
        int b_size();

    private:
        int *buckets;
        int base_size;
        int sentinel;
        bool sentinel_occ;

        unsigned hash(int key);
};
