#ifndef DLL_H
#define DLL_H

#include <stdbool.h>

struct double_ll_node {
    struct double_ll_node *prev, *next;
};

inline void dll_init(struct double_ll_node *list);
inline void dll_add_after(struct double_ll_node *head, struct double_ll_node *new);
inline void dll_add_before(struct double_ll_node *head, struct double_ll_node *new);
inline void dll_delete(struct double_ll_node *node);
inline bool dll_empty(struct double_ll_node *head);

#endif // DLL_H