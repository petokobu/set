#include <stdio.h>
#include "../lib/cset.h"

bool is_b_happy(unsigned num, unsigned base);

int main()
{
    if (is_b_happy(13, 3)) printf("Is B happy\n");
    else printf("Is not B happy\n");

    return 0;
}

unsigned convert(unsigned num, unsigned base)
{
    unsigned res = 0;
    unsigned rem;
    while (num > 0)
    {
        rem = num % base;
        res += rem * rem;
        num /= base;
    }
    return res;
}

bool is_b_happy(unsigned num, unsigned base)
{
    Set *seen = set_init();
    do
    {
        set_add(seen, (int)num);
        num = convert(num, base);
    }
    while (num != 1u && !set_contains(seen, (int)num));
    return num == 1u;
    set_fini(seen);
}
