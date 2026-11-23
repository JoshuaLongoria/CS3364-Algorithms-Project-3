#ifndef SHORTEST_PATHS_H
#define SHORTEST_PATHS_H

#include "graph.h"

typedef struct {
    long long distance[BUILDINGS];
    int previous[BUILDINGS];
} Routes;

/* Both algorithms start at the Computer Science building (SOURCE). */
Routes dijkstra(const Graph *graph);
Routes bellman_ford(const Graph *graph);
void print_routes(const char *algorithm, const Routes *result);

#endif
