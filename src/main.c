#include <stdio.h>
#include "../lib/cset.h"

int main()
{
    Set *set = set_init();

    if (!set_add(set, 0)) printf("Add 0 FAIL\n");
    if (set_add(set, 0)) printf("Duplicate 0 FAIL\n");
    set_print(set);
    if (!set_contains(set, 0)) printf("Contains 0 FAIL\n");
    if (!set_len(set) == 1u) printf("Size FAIL\n");
    if (set_contains(set, 1)) printf("Contains 1 FAIL\n");
    set_print(set);
    if (!set_remove(set, 0)) printf("Remove 0 FAIL\n");
    if (set_remove(set, 1)) printf("Remove 1 FAIL\n");
    set_print(set);
    if (!set_len(set) == 0u) printf("Size FAIL\n");

    set_fini(set);

    return 0;
}
