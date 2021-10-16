// CIUREA Robert-Mihai - 313CBb
#include "list.h"

#ifndef queue
#define queue

typedef struct queue_form {
    LL head, tail;
    int size;
} qu, *QU;

// Utility functions
QU init_queue ();
QU enqueue (QU initial, void *info);
QU dequeu (QU q);
void show_queue (QU initial, char *string, char *buffer);
void q_to_q (QU one, QU two);

#endif