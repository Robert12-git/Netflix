// CIUREA Robert-Mihai - 313CBb
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef lists
#define lists

// Useful function declaration
typedef void (*FREE_SEZ) (void *);

// List struct
typedef struct list {
    void *info;
    struct list *next;
} Node, *LL;

// Define functions
LL init_list ();
LL create_node (void *info);
LL inser_before (LL pre, LL next, LL list_h, void *info);
LL insert_end_list (LL list_h, void *info);
int poz_node (LL head_h, void *info);
int list_size (LL list_);
void* pop_front(LL *list_);

#endif