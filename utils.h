// CIUREA Robert-Mihai - 313CBb
#include "list.h"
#include "queue.h"
#include "stack.h"

#ifndef utils
#define utils

#define BUF 10000000
#define TOP10 0
#define CATEG 4
#define TOPN 10
#define OUT 50

typedef struct serial_info {
    int id, num_sez;
    char *name;
    double rating;
} serial;

typedef struct serial_seasons {
    QU seasons;
    serial data;
    int all_time;
} serial_form;

typedef struct episodes {
    int nr_ep;
    QU time;
} season;

typedef struct platform {
    LL *categories;
    QU watch_later;
    ST currently_watching;
    ST history;
} netflix;

// Utility functions
netflix init_movies (netflix structure);
void add (netflix *structure, char *buffer, FILE *in, FILE *out);
void remove_data (netflix *structure);
void add_sez (netflix structure, char *name, FILE *in, FILE *out);
void add_top (netflix structure, FILE *in, FILE *out, char *buffer);
void later (netflix structure, char *name, FILE *in, FILE *out);
void show (netflix structure, char *buffer, FILE *in, FILE *out);
void watch (netflix structure, char *buffer, FILE *in, FILE *out);

#endif