#include "shortest_paths.h"

#include <stdio.h>

static Routes initial_routes(void)
{
    Routes result;
    for (int v = 0; v < BUILDINGS; ++v) {
        result.distance[v] = INF;
        result.previous[v] = -1;
    }
    result.distance[SOURCE] = 0;
    return result;
}

static bool relax(Routes *result, int u, int v, long long weight)
{
    if (weight == INF || result->distance[u] == INF)
        return false;
    long long candidate = result->distance[u] + weight;
    if (candidate >= result->distance[v])
        return false;
    result->distance[v] = candidate;
    result->previous[v] = u;
    return true;
}

Routes dijkstra(const Graph *graph)
{
    Routes result = initial_routes();
    bool settled[BUILDINGS] = {false};
    for (int step = 0; step < BUILDINGS; ++step) {
        int nearest = -1;
        for (int v = 0; v < BUILDINGS; ++v) {
            if (!settled[v] && result.distance[v] != INF &&
                (nearest < 0 || result.distance[v] < result.distance[nearest]))
                nearest = v;
        }
        if (nearest < 0)
            break;

        settled[nearest] = true;
        for (int v = 0; v < BUILDINGS; ++v)
            if (!settled[v])
                relax(&result, nearest, v, graph->weight[nearest][v]);
    }
    return result;
}

Routes bellman_ford(const Graph *graph)
{
    Routes result = initial_routes();
    for (int pass = 1; pass < BUILDINGS; ++pass) {
        bool changed = false;
        for (int u = 0; u < BUILDINGS; ++u)
            for (int v = 0; v < BUILDINGS; ++v)
                if (relax(&result, u, v, graph->weight[u][v]))
                    changed = true;
        if (!changed)
            break;
    }
    return result;
}

void print_routes(const char *algorithm, const Routes *result)
{
    printf("\n%s\n", algorithm);
    for (int v = 0; v < BUILDINGS; ++v) {
        printf("%s: ", names[v]);
        if (result->distance[v] == INF) {
            puts("unreachable");
            continue;
        }

        int path[BUILDINGS];
        int length = 0;
        for (int current = v; current != -1; current = result->previous[current])
            path[length++] = current;

        printf("%lld units | ", result->distance[v]);
        while (length > 0) {
            printf("%s", names[path[--length]]);
            if (length > 0)
                printf(" -> ");
        }
        putchar('\n');
    }
}

