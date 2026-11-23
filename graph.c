#include "graph.h"

#include <stdio.h>

const char *const names[BUILDINGS] = {
    "Bear Village Apt.", "Brewer-Hegeman", "Oak Tree Apt.",
    "New Business Building", "Maintenance College", "Speech Language Hearing",
    "Wingo", "Student Center", "Student Health Center", "Police Dept.",
    "Fine Art", "McALister Hall", "Old Main", "Prince Center",
    "Torreyson Library", "Computer Science", "Burdick",
    "Lewis Science Center", "College Square"
};

bool load_graph(Graph *graph, const char *path)
{
    for (int u = 0; u < BUILDINGS; ++u)
        for (int v = 0; v < BUILDINGS; ++v)
            graph->weight[u][v] = INF;

    FILE *file = fopen(path, "r");
    if (!file) {
        perror(path);
        return false;
    }

    char line[256];
    unsigned number = 0;
    bool valid = true;
    while (fgets(line, sizeof line, file)) {
        ++number;
        int u, v, weight;
        char extra;
        int fields = sscanf(line, "%6d %6d %9d %c", &u, &v, &weight, &extra);
        if (fields == EOF)
            continue;
        if (fields != 3 || u < 0 || u >= BUILDINGS || v < 0 ||
            v >= BUILDINGS || u == v || weight < 0) {
            fprintf(stderr, "%s line %u: expected two distinct IDs (0–18) and a nonnegative weight.\n",
                    path, number);
            valid = false;
            break;
        }
        if (weight < graph->weight[u][v]) {
            graph->weight[u][v] = weight;
            graph->weight[v][u] = weight;
        }
    }
    if (ferror(file)) {
        perror(path);
        valid = false;
    }
    fclose(file);
    return valid;
}

