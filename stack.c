// CIUREA Robert-Mihai - 313CBb
#include "utils.h"

ST init_stack () {
    ST new_stack = NULL;

    // Alloc stack
    new_stack = (ST) calloc (1, sizeof (st));
    if (!new_stack) return NULL;

    // Set head to NULL
    new_stack->top = NULL;

    return new_stack;
}

ST push (ST stack_form, void *info) {
    // Create new node for stack
    LL new_node = create_node (info);

    // Next of new node points to top of stack
    new_node->next = stack_form->top;
    // New node becomes top of stack
    stack_form->top = new_node;

    return stack_form;
}

void *pop (ST stack_form, FREE_SEZ fun) {
    LL copy;

    // Copy top of stack
    copy = stack_form->top;

    // Go to next node of stack
    stack_form->top = stack_form->top->next;

    void *ret = copy->info;
    free (copy);

    return ret;  
}

void pop_st_to_st (ST one, ST two) {
    // If stack is empty, just leave
    if (!(one->top)) return;

    // Copy top and next node of stack
    LL aux = one->top, next = one->top->next;

    // If buffer stack is empty, top of it is top of stack
    if (!(two->top)) {
        two->top = aux;
        two->top->next = next;
        one->top = one->top->next;
        return;
    }

    // If stack has elements, top of stack becomes top of buffer
    if (one->top) {
        aux->next = two->top;
        two->top = aux;
        one->top = next;
        return;
    }
}

int stack_size (ST stack_) {
    LL copy = stack_->top;
    int k = 0;

    // Get through stack and count each node
    while (copy) {
        k++;
        copy = copy->next;
    }

    // Return size of stack
    return k;
}

void show_stack (ST stack_, char *string, char *cat) {
    ST buffer = init_stack ();
    LL aux = stack_->top;
    serial_form *data;
    int len = 0;

    len += sprintf (string + len, "Categoria %s: [", cat);

    // Go through each node and write in buffer data needed for output
    while (aux) {
        data = aux->info;
        len += sprintf (string + len, "(%s, %.1lf), ",
                        data->data.name, data->data.rating);
        aux = aux->next;
    }

    free (buffer);
    return;
}