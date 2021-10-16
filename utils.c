// CIUREA Robert-Mihai - 313CBb
#include "utils.h"

// Alloc initial memory for every structure of data needed
netflix init_movies (netflix structure) {
    LL node_top, copy;

    structure.categories = (LL *) calloc (CATEG, sizeof (LL));
    for (int i = 0; i < CATEG; i++)
        structure.categories[i] = init_list ();

    copy = structure.categories[TOP10];
    for (int i = 1; i < TOPN; i++) {
        node_top = init_list ();
        copy->info = NULL;
        copy->next = node_top;
        copy = copy->next;
    }
    structure.watch_later = init_queue ();
    structure.currently_watching = init_stack ();
    structure.history = init_stack ();

    return structure;
}

season *create_season (FILE *in, int *all_time) {
    season *season_data = NULL;
    int *time = NULL;

    // Alloc serial structure
    season_data = (season *) calloc (1, sizeof (season));
    if (!season_data) return NULL;

    // Init time queue
    season_data->time = init_queue ();

    fscanf (in, "%d", &(season_data->nr_ep));
    for (int i = 0; i < season_data->nr_ep; i++) {
        // Alloc each time variable
        time = (int *) calloc (1, sizeof (int));
        if (!time) {
            free (season_data);
            return NULL;
        }

        // Read each duration of episode
        fscanf (in, "%d", time);
        (*all_time) += *time;

        // Introduce in queue the value
        season_data->time = enqueue (season_data->time, time);
        time = NULL;
    }

    return season_data;
}

serial_form *create_data (FILE *in, char *buffer, int id) {
    serial_form *var = NULL;
    season *data_s = NULL;

    // Alloc serial data
    var = (serial_form *) calloc (1, sizeof (serial_form));
    if (!var) return NULL;

    // Set id
    var->data.id = id;
    fscanf (in, "%s", buffer);

    // Alloc memory for name
    var->data.name = (char *) calloc (strlen (buffer) + 2, sizeof (char));
    if (!var->data.name) {
        free (var);
        return NULL;
    }

    // Set time of serial initial to 0
    var->all_time = 0;

    // Set name of serial
    strcpy (var->data.name, buffer);

    // Read rating of serial
    fscanf (in, "%lf", &(var->data.rating));

    // Read number of seasons
    fscanf (in, "%d", &(var->data.num_sez));

    // Init seasons queue
    var->seasons = init_queue ();

    // Read data for each season
    for (int i = 0; i < var->data.num_sez; i++) {
        // Create one season structure
        data_s = create_season (in, &(var->all_time));
        var->seasons = enqueue (var->seasons, data_s);
    }

    return var;
}

void add (netflix *structure, char *buffer, FILE *in, FILE *out) {
    int id, poz, flag = 1;
    serial_form *serial_node = NULL, *ver;
    LL cell, copy, next, pre = NULL;

    // Read id of serial
    fscanf (in, "%d", &id);

    // Introduce info for serial node
    serial_node = create_data (in, buffer, id);
    
    // If category is empty, introduce info and make head
    if (!(structure->categories[id]->info))
        structure->categories[id]->info = serial_node;

    // If we have to introduce more data
    else  {
        copy = structure->categories[id];
       while (copy) {
           ver = copy->info;

           // Verify rating
           if (ver->data.rating < serial_node->data.rating) {
               next = copy;

               // Insert behinde first node bigger than new node
               structure->categories[id] = inser_before (pre, next,
                                        structure->categories[id], serial_node);

               // Insert done, stop function 
               break;

               // Ratings eq, sort by name
           } else if (ver->data.rating == serial_node->data.rating) {

               // Make sure all node to be verified have same rating
               while (ver->data.rating == serial_node->data.rating) {

                   // Compare names
                   if (strcmp (ver->data.name, serial_node->data.name) > 0) {
                       flag = -1;
                       next = copy;

                       // Insert behinde first node smaller than new node
                       structure->categories[id] = inser_before (pre, next,
                                        structure->categories[id], serial_node);
                        // if (id == 3)
                            // printf ("3.......%s\n", serial_node->data.name);

                       // Insert done, stop function
                       break;
                   }
                   pre = copy;
                   copy = copy->next;
                   if (!copy) break;
                   ver = copy->info;
               }
                if (flag == 1) {
                    next = copy;
                    structure->categories[id] = inser_before (pre, next, structure->categories[id], serial_node);
                }
               // Insert done, stop function
               break;
           }
           pre = copy;
           copy = copy->next;

           // If we get to end of list, introduce at the end
           if (!copy) {
               cell = structure->categories[id];
               cell = insert_end_list (cell, serial_node);
               break;
           }
       } 
    }

    poz = poz_node (structure->categories[id], serial_node);
    
    // Write output
    fprintf (out, "Serialul %s", serial_node->data.name);
    fprintf (out, " a fost adaugat la pozitia %d.\n", poz);

    return;
}

// Free all data of a node, without deleting node
void free_serial (serial_form *data) {
    season *aux;
    LL copy;

    if (!data) return;
    while (data->seasons) {
        aux = data->seasons->head->info;
        while (aux->time) {
            copy = aux->time->head;
            free (copy->info);
            aux->time->head = aux->time->head->next;
            free (copy);
            if (!(aux->time->head)) {
                aux->time->tail = NULL;
                free (aux->time);
                aux->time = NULL;
            }
        }
        copy = data->seasons->head;
        free (copy->info);
        data->seasons->head = data->seasons->head->next;
        free (copy);
        if (!(data->seasons->head)) {
            data->seasons->tail = NULL;
            free (data->seasons);
            data->seasons = NULL;
        }
    }
    // free (data);
}

// Access all data of all nodes and free them all, including pointers to nodes
void remove_data (netflix *structure) {
    serial_form *serial_node;
    season *aux;
    LL copy, var;

    for (int i = 0; i < CATEG; i++) {
        while (structure->categories[i]) {
        var = structure->categories[i];
        serial_node = structure->categories[i]->info;
        if (serial_node) {
            free (serial_node->data.name);
            while (serial_node->seasons) {
                aux = serial_node->seasons->head->info;
                while (aux->time) {
                    copy = aux->time->head;
                    free (copy->info);
                    aux->time->head = aux->time->head->next;
                    free (copy);
                    if (!(aux->time->head)) {
                        aux->time->tail = NULL;
                        free (aux->time);
                        aux->time = NULL;
                    }
                }
                copy = serial_node->seasons->head;
                free (copy->info);
                serial_node->seasons->head = serial_node->seasons->head->next;
                free (copy);
                if (!(serial_node->seasons->head)) {
                    serial_node->seasons->tail = NULL;
                    free (serial_node->seasons);
                    serial_node->seasons = NULL;
                }
            }
        }
        structure->categories[i] = structure->categories[i]->next;
        free (serial_node);
        free (var);
        }
    }

    void *node_ = NULL, *data;
    while (structure->watch_later->head) {
        node_ = structure->watch_later;
        data = structure->watch_later->head->info;
        structure->watch_later->head = structure->watch_later->head->next;
        if (node_) {
            free (node_);
            node_ = NULL;
        }
        free_serial (data);
    }
    free (structure->categories);
    free (structure->currently_watching);
    free (structure->history);
    free (structure->watch_later);
}

void add_sez (netflix structure, char *name, FILE *in, FILE *out) {
    int all_time = 0, k = 0;
    // Read name of serial to add season
    fscanf (in, "%s", name);

    // Create structure for the new season and read data
    season *new_sez = create_season (in, &all_time);
    LL copy;
    serial_form *node_in;
    int j = 1;

    // Get through all categories to find serial
    for (int i = 0; i < CATEG; i++) {
        copy = structure.categories[i];

        // If category is not empty
        if (copy && copy->info) {

            // Verify each serial to find out if matches name
            while (copy) {
                node_in = copy->info;

                // Check if names are the same
                if (k > OUT) return;
                if (!node_in) break;
                if (strcmp (node_in->data.name, name) == 0) {
                    node_in->all_time += all_time;

                    // If yes, set flag to stop loop
                    j = -1;

                    // Insert in queue new season
                    (node_in->data.num_sez)++;
                    node_in->seasons = enqueue (node_in->seasons, new_sez);
                    break;
                }

                // Get to next serial until find the good one
                copy = copy->next;
                k++;
            }
        }

        // If new season inserted, stop loop
        if (j < 0) break;
    }

    // Write output of insertion
    fprintf (out, "Serialul %s are un sezon nou.\n", name);
}

void add_top (netflix structure, FILE *in, FILE *out, char *buffer) {
    int poz_top, size;
    serial_form *serial_node = NULL;
    LL copy;
    serial_form *aux, *var;
    char *string;

    // Read poz of serial in top10
    fscanf (in, "%d", &poz_top);

    // Introduce info for serial node
    serial_node = create_data (in, buffer, TOP10);

    copy = structure.categories[TOP10];

    // Check each node
    for (int i = 0; i < TOPN; i++) {

        // If node poz == read poz
        if ((i + 1) == poz_top) {
            if (!copy) break;
            aux = copy->info;
            copy->info = serial_node;
            copy = copy->next;
            while (copy && copy->info) {
                var = copy->info;
                copy->info = aux;
                aux = var;
                if (!(copy->next)) {
                    copy = copy->next;
                    break;
                }
                copy = copy->next;
            }
            
            if (!(copy)) free_serial (aux);
            else {
                copy->info = aux;
                // copy->next->info = aux;
            }

            break;
        }

        // Go to next node until find good node to introduce serial
        if (!copy) break;
        copy = copy->next;
    }

    // Alloc enough memory for buffer to print output
    string = (char *) calloc (100000, sizeof (char));
    if (!string) {
        remove_data (&structure);
        return;
    }
    
    copy = structure.categories[TOP10];
    size = sprintf (string, "Categoria top10: [");
    for (int i = 0; i < TOPN; i++) {
        if (copy)
        if (copy->info) {
            serial_node = copy->info;
            size += sprintf (string + size, "(%s, %.1lf), ",
                            serial_node->data.name, serial_node->data.rating);
        }

        if (copy) copy = copy->next;
        else break;
    }
    
    sprintf (string + size - 2, "].\n");

    // Write in file
    fprintf (out, "%s", string);

    // Free buffer
    free (string);
}

void later (netflix structure, char *name, FILE *in, FILE *out) {
    LL copy, pre;
    serial_form *node_h;

    fscanf (in, "%s", name);

    // Search for certain serial in each category
    for (int i = 0; i < CATEG; i++) {
        pre = NULL;
        copy = structure.categories[i];
        if (!copy || !(copy->info)) {
            continue;
        } else {
            while (copy->info) {
                node_h = copy->info;

                // If serial found
                if (strcmp (node_h->data.name, name) == 0) {

                    // Introduce serial in watch_later queue
                    structure.watch_later = enqueue (structure.watch_later,
                                                                     node_h);

                    // If first node and not top10 category
                    if (!pre && i) {

                            // Second node of list becomes the first one
                        structure.categories[i] = structure.categories[i]->next;

                        // If list becomes null, init it again
                        if (structure.categories[i] == NULL)
                            structure.categories[i] = init_list();

                        // Free old node
                        free (copy);
                        return;

        // If not first node of list, just get to the next one and free old node
                    } else if (pre && i) {
                        pre->next = copy->next;
                        free (copy);
                    }

                    // If working on top10 category
                    else if (!i) {

                        // Get all info of nodes one node back
                        while (copy && copy->info) {
                            if (!(copy->next)) return;
                            copy->info = copy->next->info;
                            if (!(copy->next->next)) {
                                copy->next->info = NULL;
                                return;
                            }

                            if (!copy) return;
                            copy = copy->next;
                            
                        }
                    }
                    
                    return;
                }

                // Retain current node and get to next one
                pre = copy;
                copy = copy->next;
                if (!(copy)) break;
            }
        }
    }
}

void watch (netflix structure, char *buffer, FILE *in, FILE *out) {
    int durata, flag = 1, k = 0;
    LL copy, pre = NULL;
    serial_form *node_h;
    QU copy_qu = init_queue ();

    fscanf (in, "%s %d", buffer, &durata);

    // Serch for needed serial in all categories, and if found move to watch stack
    for (int i = 0; i < CATEG; i++) {
        copy = structure.categories[i];
        if (!copy) continue;
        else if (copy->info) {
            while (copy) {
                node_h = copy->info;
                
                // If found serial, push in stack
                if (strcmp (node_h->data.name, buffer) == 0) {
                    structure.currently_watching = 
                    push (structure.currently_watching, node_h);
                    if (!pre) structure.categories[i] = copy->next;
                    else pre->next = copy->next;
                    flag = -1;
                    break;
                }
                pre = copy;
                copy = copy->next;
                k++;
            }
        }
    }
    
    if (flag != -1) {

        // Serch in watch_later queue if didn't find serial in categories
        while (structure.watch_later->head) {
            node_h = structure.watch_later->head->info;

            // If found
            if (strcmp (node_h->data.name, buffer) == 0) {

                // Push serial in stack
                structure.currently_watching = 
                push (structure.currently_watching, node_h);
                structure.watch_later->head = structure.watch_later->head->next;
                flag = -1;
            }

            // If didn't find in current node, put data in buffer stack and analyze next node
            q_to_q (structure.watch_later, copy_qu);
        }

        // Put all serials back to initial stack
        while (copy_qu->head) q_to_q (copy_qu, structure.watch_later);
    }

    // Search serial in current_watching stack and give needed output with watched entire serial
    LL aux = structure.currently_watching->top;
    if (aux && strcmp(((serial_form *)(aux->info))->data.name, buffer)) {
        node_h = (serial_form *)(pop_front(&(structure.currently_watching->top)));
        node_h->all_time -= durata;
        if (node_h->all_time <= 0) {
            
            push(structure.history, node_h);
            fprintf (out, "Serialul %s", node_h->data.name);
            fprintf (out, " a fost vizionat integral.\n");
        }
        else {
            push(structure.currently_watching, node_h);
        }
        return;
    }
    else
        while (aux) {
            if (!aux->next) return;
            node_h = aux->next->info;
            if (k > OUT) return;
            if (!node_h) return;
            if (strcmp (node_h->data.name, buffer) == 0) {
                    node_h->all_time -= durata;
                    if (node_h->all_time <= 0) {
                        aux->next = aux->next->next;
                        push(structure.history, node_h);
                        fprintf (out, "Serialul %s", node_h->data.name);
                        fprintf (out, " a fost vizionat integral.\n");
                    }
                    else {
                        push(structure.currently_watching, node_h);
                    }

                    return;
                }
                aux = aux->next;
                k++;
            }
}

// Find which data structure must be written in output and write
void show (netflix structure, char *buffer, FILE *in, FILE *out) {
    int index, len = 0;
    LL access;
    serial_form *node_h;
    char *string = NULL;

    string = (char *) calloc (BUF, sizeof (char));
    if (!string)  return;
    fscanf (in, "%s", buffer);
    if (strcmp (buffer, "1") == 0) {
        index = atoi (buffer);
        access = structure.categories[index];
        if (!(access) || !(access->info)) {
            fprintf (out, "Categoria 1: [].\n");
            free (string);
            return;
        } else {
            len = sprintf (string + len, "Categoria %d: [", index);
            while (access && access->info) {
                node_h = access->info;
                len += sprintf (string + len, "(%s, %.1lf), ",
                        node_h->data.name, node_h->data.rating);
                access = access->next;
            }
        }
    } else if (strcmp (buffer, "2") == 0) {
        index = atoi (buffer);
        access = structure.categories[index];
        if (!(access) || !(access->info)) {
            fprintf (out, "Categoria 2: [].\n");
            free (string);
            return;
        } else {
            len = sprintf (string + len, "Categoria %d: [", index);
            while (access && access->info) {
                node_h = access->info;
                len += sprintf (string + len, "(%s, %.1lf), ",
                        node_h->data.name, node_h->data.rating);
                access = access->next;
            }
        }
    } else if (strcmp (buffer, "3") == 0) {
        index = atoi (buffer);
        access = structure.categories[index];
        if (!(access) || !(access->info)) {
            fprintf (out, "Categoria 3: [].\n");
            free (string);
            return;
        } else {
            len = sprintf (string + len, "Categoria %d: [", index);
            while (access && access->info) {
                node_h = access->info;
                len += sprintf (string + len, "(%s, %.1lf), ",
                        node_h->data.name, node_h->data.rating);
                access = access->next;
            }
        }
    } else if (strcmp (buffer, "top10") == 0) {
        access = structure.categories[TOP10];
        if (!(access) || !(access->info)) {
            fprintf (out, "Categoria top10: [].\n");
            free (string);
            return;
        }
        else {
            len += sprintf (string + len, "Categoria %s: [", buffer);
            while (access && access->info) {
                node_h = access->info;
                len += sprintf (string + len, "(%s, %.1lf), ",
                        node_h->data.name, node_h->data.rating);
                access = access->next;
            }
        }
    } else if (strcmp (buffer, "history") == 0) {
        if (!(structure.history->top) || !(structure.history->top->info)) {
            fprintf (out, "Categoria history: [].\n");
            free (string);
            return;
        }
        show_stack (structure.history, string, buffer);
    }
    else if (strcmp (buffer, "watching") == 0) {
        if (!(structure.currently_watching->top) ||
                    !(structure.currently_watching->top->info)) {
            fprintf (out, "Categoria watching: [].\n");
            free (string);
            return;
        }
        show_stack (structure.currently_watching, string, buffer);
    }
    else if (strcmp (buffer, "later") == 0) {
        if (!(structure.watch_later->head) || !(structure.watch_later->head->info)) {
            fprintf (out, "Categoria later: [].\n");
            free (string);
            return;
        }
        show_queue (structure.watch_later, string, buffer);
    }

    sprintf (string + strlen (string) - 2, "].\n");
    fprintf (out, "%s", string);

    free (string);
    return;
}