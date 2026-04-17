#pragma once

class Bucket
{
    public:
        virtual bool add(int key) = 0;
        virtual bool contains(int key) = 0;
        virtual bool remove(int key) = 0;

        virtual bool is_empty() = 0;

        virtual void reset_iter() = 0;
        virtual bool get_next(int *store) = 0;
};
