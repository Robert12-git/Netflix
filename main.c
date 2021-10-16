// CIUREA Robert-Mihai - 313CBb
#include "utils.h"

int main (int argc, char **argv) {
    if (argc != 3) return -1;

    netflix structure;
    FILE *in = NULL, *out = NULL;
    char *buffer = NULL;

    // Open file in
    in = fopen (argv[1], "rt");
    if (!in) return 0;

    // Open file out
    out = fopen (argv[2], "wt");
    if (!out) {
        fclose (in);
        return 0;
    }

    // Alloc buffer
    buffer = (char *) calloc (BUF, sizeof (char));
    if (!buffer) {
        fclose (out);
        fclose (in);
        return 0;
    }

    // Initialize netflix platform
    structure = init_movies (structure);

    // Read first word of each line untill end of file
    while (fscanf (in, "%s", buffer) != EOF) {
        if (strcmp (buffer, "add") == 0)
            add (&structure, buffer, in, out);
        else if (strcmp (buffer, "add_sez") == 0)
            add_sez (structure, buffer, in, out);
        else if (strcmp (buffer, "add_top") == 0)
            add_top (structure, in, out, buffer);
        else if (strcmp (buffer, "later") == 0) {
            later (structure, buffer, in, out);
            fprintf (out, "Serialul %s se afla in ", buffer);
            fprintf (out, "coada de asteptare pe pozitia ");
            fprintf (out, "%d.\n", structure.watch_later->size);
        }
        else if (strcmp (buffer, "watch") == 0) {
            // Not functional, just read line in order to get to next line
            fscanf (in, "%s", buffer);
            fscanf (in, "%s", buffer);
        } else if (strcmp (buffer, "show") == 0)
            show (structure, buffer, in, out);
    }

    free (buffer);
    fclose (out);
    fclose (in);
    remove_data (&structure);

    return 0;
}