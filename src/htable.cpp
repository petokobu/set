#include "htable.h"
#include "bucket.h"
#include "rbtree.h"
#include "llist.h"

HTable::HTable(bool lite)
{
    buckets = new Bucket*[BASE_SIZE];
    for (int i = 0; i < BASE_SIZE; ++i)
    {
        if (lite) buckets[i] = new LList();
        else buckets[i] = new RBTree();
    }
    iter_inx = 0; 
}

HTable::~HTable()
{
    for (int i = 0; i < BASE_SIZE; ++i) delete buckets[i];
    delete[] buckets;
}

bool HTable::add(int key)
{
    unsigned inx = hash(key) % BASE_SIZE;
    return buckets[inx]->add(key);
}

bool HTable::contains(int key)
{
    unsigned inx = hash(key) % BASE_SIZE;
    return buckets[inx]->contains(key);
}

bool HTable::remove(int key)
{
    unsigned inx = hash(key) % BASE_SIZE;
    return buckets[inx]->remove(key);
}

void HTable::reset_iter()
{
    iter_inx = 0;
    if (!buckets[iter_inx]->is_empty())
        buckets[iter_inx]->reset_iter();
}

bool HTable::get_next(int *store)
{
    if (buckets[iter_inx]->is_empty()
        || !buckets[iter_inx]->get_next(store))
    {
        for (++iter_inx; iter_inx < BASE_SIZE
             && buckets[iter_inx]->is_empty(); ++iter_inx) ;
        if (iter_inx == BASE_SIZE)
        {
            reset_iter();
            return false;
        }
        buckets[iter_inx]->reset_iter();
        return buckets[iter_inx]->get_next(store);
    }
    return true;
}

unsigned HTable::hash(int key)
{
    unsigned ukey = (unsigned)key;
    ukey ^= ukey >> 16;
    ukey *= 0x7feb352du;
    ukey ^= ukey >> 15;
    ukey *= 0x846ca68du;
    ukey ^= ukey >> 16;
    return ukey;
}
