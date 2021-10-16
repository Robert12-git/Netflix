// CIUREA Robert-Mihai - 313CBb
#include "list.h"

LL init_list () {
    LL list_struct = NULL;

    // Alloc list
    list_struct = (LL) calloc (1, sizeof (Node));
    if (!list_struct) return NULL;

    // Set info and next to NULL
    list_struct->info = NULL;
    list_struct->next = NULL;

    return list_struct;
}

LL create_node (void *info) {
    LL head = NULL;

    // Alloc list
    head = (LL) calloc (1, sizeof (Node));
    if (!head) return NULL;

    // Set all NULL
    head->info = info;
    head->next = NULL;

    return head;
}

LL inser_before (LL pre, LL next, LL list_h, void *info) {
    // Create new node with data
    LL node_h = create_node (info);

    // If behinde there is no other node make new node first
    if (!pre) {
        node_h->next = list_h;
        list_h = node_h;
        return list_h;
    }

    // Next of node from behinde must point to new node
    pre->next = node_h;
    // New node points to links to next node of pre
    node_h->next = next;

    return list_h;
}

LL insert_end_list (LL list_h, void *info) {
    // Create new node with data
    LL node_h = create_node (info), copy = list_h;

    // Get to end of the list
    while (copy->next)
        copy = copy->next;

    // End of list points to the node to create new end of list
    copy->next = node_h;

    return list_h;
}

int poz_node (LL head_h, void *info) {
    LL copy = head_h;
    int cont = 1;

    // Get through list untill find certain node
    while (copy) {
        // If certain node was found, break;
        if (copy->info == info) break;
        
        // Increment variable for poz of node
        cont++;

        // Get to next node
        copy = copy->next;
    }
    
    // Return poz
    return cont;
}

int list_size (LL list_) {
    LL copy = list_;
    int k = 0;

    // Get through nodes of list and count each node
    while (copy) {
        k++;
        copy = copy->next;
    }

    // Return number of nodes
    return k;
}


void *pop_front(LL *list_) {
    if (!(*list_)) return NULL;

    // Pointer retains data of node
    void *return_value = (*list_)->info;

    // Lists head gets to next node
    *list_ = (*list_)->next;

    // Return first element of old list
    return return_value;
}