// CIUREA Robert-Mihai - 313CBb
#include "list.h"

#ifndef stack
#define stack

// Definition of pattern for functions
typedef void (*FREE_SEZ) (void *);

typedef struct stack_form {
    LL top;
} st, *ST;

// Utility functions
ST init_stack ();
ST push (ST stack_form, void *info);
void *pop (ST stack_form, FREE_SEZ fun);
void pop_st_to_st (ST one, ST two);
void show_stack (ST stack_, char *string, char *cat);

#endif