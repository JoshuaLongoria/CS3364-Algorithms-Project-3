#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum { BUILDINGS = 19, SOURCE = 15 };
#define INF LLONG_MAX

static const char *const names[BUILDINGS] = {
    "Bear Village Apt.", "Brewer-Hegeman", "Oak Tree Apt.",
    "New Business Building", "Maintenance College", "Speech Language Hearing",
    "Wingo", "Student Center", "Student Health Center", "Police Dept.",
    "Fine Art", "McALister Hall", "Old Main", "Prince Center",
    "Torreyson Library", "Computer Science", "Burdick",
    "Lewis Science Center", "College Square"
};

typedef struct {
    long long weight[BUILDINGS][BUILDINGS];
} Graph;

typedef struct {
    long long distance[BUILDINGS];
    int previous[BUILDINGS];
} Routes;

static bool load_graph(Graph *graph, const char *path)
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

static Routes dijkstra(const Graph *graph)
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

static Routes bellman_ford(const Graph *graph)
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

static void print_routes(const char *algorithm, const Routes *result)
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

int main(int argc, char **argv)
{
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [edge-file]\n", argv[0]);
        return EXIT_FAILURE;
    }
    Graph graph;
    if (!load_graph(&graph, argc == 2 ? argv[1] : "campus.txt"))
        return EXIT_FAILURE;

    Routes greedy = dijkstra(&graph);
    Routes dynamic = bellman_ford(&graph);
    for (int v = 0; v < BUILDINGS; ++v) {
        if (greedy.distance[v] != dynamic.distance[v]) {
            fprintf(stderr, "Algorithms disagree for %s\n", names[v]);
            return EXIT_FAILURE;
        }
    }
    print_routes("Dijkstra", &greedy);
    print_routes("Bellman-Ford", &dynamic);
    puts("\nBoth algorithms agree on all distances.");
    return EXIT_SUCCESS;
}
