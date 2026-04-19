#include <iostream>
#include "../lib/set.h"

void speed_test();
void display_test();

int main()
{
    speed_test();

    return 0;
}

void speed_test()
{
    int limit = 0xfffff;

    Set *rb_set = new Set();
    Set *ll_set = new Set(true);

    std::cout << "RB Set START\n";
    for (int i = 0; i <= limit; ++i)
        if (!rb_set->add(i)) std::cout << "add FAIL for " << i << "\n";
    for (int i = limit; i >= 0; --i)
        if (!rb_set->contains(i)) std::cout << "contains FAIL for " << i << "\n";
    for (int i = 0; i <= limit; ++i)
        if (!rb_set->remove(i)) std::cout << "remove FAIL for " << i << "\n";
    std::cout << "RB Set END\n";

    std::cout << "LL Set START\n";
    for (int i = 0; i <= limit; ++i)
        if (!ll_set->add(i)) std::cout << "add FAIL for " << i << "\n";
    for (int i = limit; i >= 0; --i)
        if (!ll_set->contains(i)) std::cout << "contains FAIL for " << i << "\n";
    for (int i = 0; i <= limit; ++i)
        if (!ll_set->remove(i)) std::cout << "remove FAIL for " << i << "\n";
    std::cout << "LL Set END\n";

    delete rb_set;
    delete ll_set;
}

void display_test()
{
    Set *set = new Set();

    set->add(1);
    set->add(2);

    print(set);

    delete set;
}
