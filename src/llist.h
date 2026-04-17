#include "bucket.h"

#pragma once

struct lnode
{
    int key;
    lnode* next;
};

class LList : public Bucket
{
    public:
        LList();
        ~LList();

        bool add(int key) override;
        bool contains(int key) override;
        bool remove(int key) override;
    
        bool is_empty() override;

        void reset_iter() override;
        bool get_next(int *store) override;

    private:
        lnode *head;
        lnode *iter_node;
};
