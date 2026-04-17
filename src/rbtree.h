#include "bucket.h"

#pragma once

enum
{
    RED,
    BLACK
};

struct node
{
    int key;
    int color;
    node *left;
    node *right;
    node *parent;
};

class RBTree : public Bucket
{
    public:
        RBTree();
        ~RBTree();

        bool add(int key) override;
        bool contains(int key) override;
        bool remove(int key) override;

        bool is_empty() override;

        void reset_iter() override;
        bool get_next(int *store) override;

    private:
        node *root;
        node *NIL;
        node *iter_node;

        node *node_init(int key, int color);
        void node_fini(node *node);
        void tree_fini(node *node);

        node *search(int key);
        node *pred(node *node);
        node *succ(node *node);
        node *min(node *node);
        node *max(node *node);

        void transplant(node *rem, node *rep);
        void left_rotate(node *node);
        void right_rotate(node *node);
        void insert_fixup(node *node);
        void remove_fixup(node *node);
};
