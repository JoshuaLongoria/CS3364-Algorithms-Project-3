#ifndef GRAPH_H
#define GRAPH_H

#include <limits.h>
#include <stdbool.h>

enum { BUILDINGS = 19, SOURCE = 15 };
#define INF LLONG_MAX

/* Undirected graph with nonnegative integer walkway distances. */
typedef struct {
    long long weight[BUILDINGS][BUILDINGS];
} Graph;

extern const char *const names[BUILDINGS];

/* Load rows of "building-ID building-ID distance" from a text file. */
bool load_graph(Graph *graph, const char *path);

#endif
