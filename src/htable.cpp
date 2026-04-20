#include "htable.h"
#include "bucket.h"
#include "rbtree.h"
#include "llist.h"

HTable::HTable(int base_size, bool lite)
{
    buckets = new Bucket*[base_size]{ 0 };
    this->lite = lite;
    this->base_size = base_size;
    iter_inx = 0; 
}

HTable::~HTable()
{
    for (int i = 0; i < base_size; ++i) delete buckets[i];
    delete[] buckets;
}

bool HTable::add(int key)
{
    unsigned inx = hash(key) % base_size;
    if (buckets[inx] == 0)
    {
        if (lite) buckets[inx] = new LList();
        else buckets[inx] = new RBTree();
    }
    return buckets[inx]->add(key);
}

bool HTable::contains(int key)
{
    unsigned inx = hash(key) % base_size;
    if (buckets[inx] == 0) return false;
    return buckets[inx]->contains(key);
}

bool HTable::remove(int key)
{
    unsigned inx = hash(key) % base_size;
    if (buckets[inx] == 0) return false;
    return buckets[inx]->remove(key);
}

void HTable::reset_iter()
{
    iter_inx = 0;
    if (buckets[iter_inx] != 0
        && !buckets[iter_inx]->is_empty()) buckets[iter_inx]->reset_iter();
}

bool HTable::get_next(int *store)
{
    if (buckets[iter_inx] == 0
        || buckets[iter_inx]->is_empty()
        || !buckets[iter_inx]->get_next(store))
    {
        for (++iter_inx; iter_inx < base_size
             && (buckets[iter_inx] == 0
                 || buckets[iter_inx]->is_empty()); ++iter_inx) ;
        if (iter_inx == base_size)
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
