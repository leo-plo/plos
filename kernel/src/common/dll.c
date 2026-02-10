#include <common/dll.h>
#include <stdbool.h>

// Initializes the list
inline void dll_init(struct double_ll_node *list)
{
    list->next = list;
    list->prev = list;
}

// Adds a node (new) between 2 nodes (prev and next)
static inline void _dll_add(struct double_ll_node *new, struct double_ll_node *prev, struct double_ll_node *next)
{
    prev->next = new;
    new->prev = prev;
    new->next = next;
    next->prev = new;
}

// Adds a node after the current one
inline void dll_add_after(struct double_ll_node *head, struct double_ll_node *new)
{
    _dll_add(new, head, head->next);
}

// Adds a node after the current one
inline void dll_add_before(struct double_ll_node *head, struct double_ll_node *new)
{
    _dll_add(new, head->prev, head);
}

// Deletes a node by linking the prev with the next
inline void dll_delete(struct double_ll_node *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

// Returns true if the list is empty
inline bool dll_empty(struct double_ll_node *head)
{
    return head->next == head && head->prev == head;
}