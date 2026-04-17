#include "llist.h"

LList::LList()
{
    head = 0;
    iter_node = 0;
}

LList::~LList()
{
    lnode *rem;
    while (head)
    {
        rem = head;
        head = head->next;
        delete rem;
    }
}

bool LList::add(int key)
{   // weak duplication detection
    if (head && head->key == key) return false;
    lnode *added = new lnode{key, 0};
    added->next = head;
    head = added;
    return true;
}

bool LList::contains(int key)
{
    lnode *pawn = head;
    while (pawn)
    {
        if (pawn->key == key) return true;
        pawn = pawn->next;
    }
    return false;
}

bool LList::remove(int key)
{
    lnode *pawn = head;
    lnode *prev = 0;
    while (pawn && pawn->key != key)
    {
        prev = pawn;
        pawn = pawn->next;
    }
    if (pawn == 0) return false;
    if (prev == 0) head = pawn->next;
    else prev->next = pawn->next;
    delete pawn;
    return true;
}

bool LList::is_empty()
{ return head == 0; }

void LList::reset_iter()
{ iter_node = head; }

bool LList::get_next(int *store)
{
    if (iter_node == 0)
    {
        reset_iter();
        return false;
    }
    *store = iter_node->key;
    iter_node = iter_node->next;
    return true;
}
