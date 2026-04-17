#include "rbtree.h"

RBTree::RBTree()
{
    NIL = new node{0, BLACK, 0, 0, 0};
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
    root = NIL;
    iter_node = NIL;
}

RBTree::~RBTree()
{
    tree_fini(root);
    node_fini(NIL);
}

bool RBTree::add(int key)
{
    node *pawn = root;
    node *parent = NIL;
    while (pawn != NIL && pawn->key != key)
    {
        parent = pawn;
        pawn = key < pawn->key ? pawn->left : pawn->right;
    }
    if (pawn != NIL) return false;
    pawn = node_init(key, RED);
    pawn->parent = parent;
    if (parent == NIL) root = pawn;
    else if (key < parent->key) parent->left = pawn;
    else parent->right = pawn;
    insert_fixup(pawn);
    return true;
}

bool RBTree::contains(int key)
{ return search(key) != NIL; }

bool RBTree::remove(int key)
{
    node *rem = search(key);
    if (rem == NIL) return false;
    node *rep = rem;
    int org_color = rep->color;

    node *inv;
    if (rem->left == NIL)
    {
        inv = rem->right;
        transplant(rem, rem->right);
    }
    else if (rem->right == NIL)
    {
        inv = rem->left;
        transplant(rem, rem->left);
    }
    else
    {
        rep = min(rem->right);
        org_color = rep->color;
        inv = rep->right;
        if (rep->parent == rem) inv->parent = rep;
        else
        {
            transplant(rep, rep->right);
            rep->right = rem->right;
            rep->right->parent = rep;
        }
        transplant(rem, rep);
        rep->left = rem->left;
        rep->left->parent = rep;
        rep->color = rem->color;
    }
    if (org_color == BLACK) remove_fixup(inv);
    return true;
}

bool RBTree::is_empty()
{ return root == NIL; }

void RBTree::reset_iter()
{ iter_node = min(root); }

bool RBTree::get_next(int *store)
{
    if (iter_node == NIL)
    {
        reset_iter();
        return false;
    }
    *store = iter_node->key;
    iter_node = succ(iter_node);
    return true;
}

node *RBTree::node_init(int key, int color)
{ return new node{key, color, NIL, NIL, NIL}; }

void RBTree::node_fini(node *node)
{ delete node; }

void RBTree::tree_fini(node *parent)
{
    if (parent != NIL)
    {
        node *left = parent->left;
        node *right = parent->right;
        node_fini(parent);
        tree_fini(left);
        tree_fini(right);
    }
}

node *RBTree::search(int key)
{
    node *pawn = root;
    while (pawn != NIL && pawn->key != key)
        pawn = key < pawn->key ? pawn->left : pawn->right;
    return pawn;
}

node *RBTree::pred(node *node)
{
    if (node == NIL) return NIL;
    if (node->left != NIL) return max(node->left);
    struct node *parent = node->parent;
    while (parent != NIL && node != parent->right)
    {
        node = parent;
        parent = node->parent;
    }
    return parent;
}

node *RBTree::succ(node *node)
{
    if (node == NIL) return NIL;
    if (node->right != NIL) return min(node->right);
    struct node *parent = node->parent;
    while (parent != NIL && node != parent->left)
    {
        node = parent;
        parent = node->parent;
    }
    return parent;
}

node *RBTree::min(node *node)
{
    if (node == NIL) return NIL;
    while (node->left != NIL) node = node->left;
    return node;
}

node *RBTree::max(node *node)
{
    if (node == NIL) return NIL;
    while (node->right != NIL) node = node->right;
    return node;
}

void RBTree::transplant(node *rem, node *rep)
{
    if (rem->parent == NIL) root = rep;
    else if (rem->parent->left == rem) rem->parent->left = rep;
    else rem->parent->right = rep;
    if (rep != NIL) rep->parent = rem->parent;
}

void RBTree::left_rotate(node *node)
{
    if (node != NIL && node->right != NIL)
    {
        struct node *sub = node->right;
        node->right = sub->left;
        if (node->right != NIL) node->right->parent = node;
        sub->parent = node->parent;
        if (node->parent == NIL) root = sub;
        else if (node->parent->left == node) node->parent->left = sub;
        else node->parent->right = sub;
        sub->left = node;
        node->parent = sub;
    }
}

void RBTree::right_rotate(node *node)
{
    if (node != NIL && node->left != NIL)
    {
        struct node *sub = node->left;
        node->left = sub->right;
        if (node->left != NIL) node->left->parent = node;
        sub->parent = node->parent;
        if (node->parent == NIL) root = sub;
        else if (node->parent->right == node) node->parent->right = sub;
        else node->parent->left = sub;
        sub->right = node;
        node->parent = sub;
    }
}

void RBTree::insert_fixup(node *node)
{
    struct node *uncle;
    while (node != root && node->parent->color == RED)
    {
        if (node->parent == node->parent->parent->left)
        {
            uncle = node->parent->parent->right;
            if (uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    left_rotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                right_rotate(node->parent->parent);
            }
        }
        else
        {
            uncle = node->parent->parent->left;
            if (uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    right_rotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                left_rotate(node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RBTree::remove_fixup(node *node)
{
    struct node *brother;
    while (node != root && node->color == BLACK)
    {
        if (node == node->parent->left)
        {
            brother = node->parent->right;
            if (brother->color == RED)
            {
                brother->color = BLACK;
                node->parent->color = RED;
                left_rotate(node->parent);
                brother = node->parent->right;
            }
            if (brother->left->color == BLACK
                && brother->right->color == BLACK)
            {
                brother->color = RED;
                node = node->parent;
            }
            else
            {
                if (brother->right->color == BLACK)
                {
                    brother->left->color = BLACK;
                    brother->color = RED;
                    right_rotate(brother);
                    brother = node->parent->right;
                }
                brother->color = node->parent->color;
                node->parent->color = BLACK;
                brother->right->color = BLACK;
                left_rotate(node->parent);
                node = root;
            }
        }
        else
        {
            brother = node->parent->left;
            if (brother->color == RED)
            {
                brother->color = BLACK;
                node->parent->color = RED;
                right_rotate(node->parent);
                brother = node->parent->left;
            }
            if (brother->right->color == BLACK
                && brother->left->color == BLACK)
            {
                brother->color = RED;
                node = node->parent;
            }
            else
            {
                if (brother->left->color == BLACK)
                {
                    brother->right->color = BLACK;
                    brother->color = RED;
                    left_rotate(brother);
                    brother = node->parent->left;
                }
                brother->color = node->parent->color;
                node->parent->color = BLACK;
                brother->left->color = BLACK;
                right_rotate(node->parent);
                node = root;
            }
        }
    }
    node->color = BLACK;
}
