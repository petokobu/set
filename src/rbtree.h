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

class RBTree
{
    public:
        RBTree();
        ~RBTree();

        bool add(int key);
        bool contains(int key);
        bool remove(int key);

        bool is_empty();

        void reset_iter();
        bool get_next(int *store);

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
