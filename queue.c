// CIUREA Robert-Mihai - 313CBb
#include "utils.h"

QU init_queue () {
    QU new_queue = NULL;

    // Alloc queue
    new_queue = (QU) calloc (1, sizeof (qu));
    if (!new_queue) return NULL;

    // Set head and tail to NULL
    new_queue->head = new_queue->tail = NULL;
    new_queue->size = 0;

    return new_queue;
}

QU enqueue (QU initial, void *info) {
    LL node = create_node (info);

    // Empty queue case
    if (!(initial->head)) {
        initial->head = initial->tail = node;
        (initial->size)++;
        return initial;
    }

    // Add new node at end of queue
    initial->tail->next = node;
    initial->tail = node;
    (initial->size)++;

    return initial;
}

QU dequeu (QU q) {
    // If queue is empty, return NULL
    if (!(q->head)) return q;

    // Store previous front and move one node ahead
    q->head = q->head->next;
    (q->size)--;

    // If head becomes NULL, tail also becomes NULL
    if (!(q->head)) {
        q->tail = NULL;
        return q;
    }

    // Return queue modified
    return q;
}

void show_queue (QU initial, char *string, char *buffer) {
    QU aux = initial;
    QU copy = init_queue();
    serial_form *data;
    int len = 0;

    len += sprintf (string + len, "Categoria %s: [", buffer);

    // Get through each node to access certain data
    while (aux->head) {
        data = aux->head->info;
        len += sprintf (string + len, "(%s, %.1lf), ",
                        data->data.name, data->data.rating);
        // Get to next node of queue
        aux = dequeu (aux);

        // Introduce in copy of queue old data of last node accessed
        copy = enqueue (copy, data);
    }

    // Access buffer queue to create old queue
    while (copy->head) {
        data = copy->head->info;
        copy = dequeu (copy);
        initial = enqueue (initial, data);
    }

    free (copy);

    return;
}

void q_to_q (QU one, QU two) {
    // If initial queue is empty, just leave
    if (!(one->head)) return;

    // Copy head and next element of head of the queue
    LL aux = one->head, next = one->head->next;

    // If buffer queue is empty, head of queue becomes head and tail of buffer
    if (!(two->head)) {
        two->head = two->tail = aux;
        one->head = one->head->next;
        if (!(one->head)) one->tail = NULL;
        return;
    }

    // Tail of buffer queue becomes head of queue
    // Queue's head gets to next node
    if (one->head) {
        two->tail->next = aux;
        two->tail = aux;
        one->head = next;
        return;
    }
}