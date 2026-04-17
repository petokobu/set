#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Set Set;

Set *set_init(bool lite = false);
void set_fini(Set *set);

bool set_add(Set *set, int key);
bool set_contains(Set *set, int key);
bool set_remove(Set *set, int key);

unsigned set_len(Set *set);

void set_reset_iter(Set *set);
bool set_get_next(Set *set, int *store);

void set_print(Set *set);

#ifdef __cplusplus
}
#endif
