#include <assert.h>

/* Compile the same implementation used by the command-line program. */
#define main routes_main
#include "routes.c"
#undef main

static void verify_path(const Graph *graph, const Routes *routes, int v,
                        long long expected)
{
    assert(routes->distance[v] == expected);
    if (expected == INF) {
        assert(routes->previous[v] == -1);
        return;
    }

    long long cost = 0;
    int steps = 0;
    while (v != SOURCE) {
        assert(++steps < BUILDINGS);
        int parent = routes->previous[v];
        assert(parent >= 0 && parent < BUILDINGS);
        assert(graph->weight[parent][v] != INF);
        cost += graph->weight[parent][v];
        v = parent;
    }
    assert(cost == expected);
}

static void verify(const Graph *graph)
{
    long long expected[BUILDINGS][BUILDINGS];
    for (int u = 0; u < BUILDINGS; ++u)
        for (int v = 0; v < BUILDINGS; ++v)
            expected[u][v] = u == v ? 0 : graph->weight[u][v];

    for (int k = 0; k < BUILDINGS; ++k)
        for (int u = 0; u < BUILDINGS; ++u)
            for (int v = 0; v < BUILDINGS; ++v)
                if (expected[u][k] != INF && expected[k][v] != INF) {
                    long long candidate = expected[u][k] + expected[k][v];
                    if (candidate < expected[u][v])
                        expected[u][v] = candidate;
                }

    Routes greedy = dijkstra(graph);
    Routes dynamic = bellman_ford(graph);
    for (int v = 0; v < BUILDINGS; ++v) {
        verify_path(graph, &greedy, v, expected[SOURCE][v]);
        verify_path(graph, &dynamic, v, expected[SOURCE][v]);
    }
}

static void check_input(const char *contents, bool valid, long long expected_edge)
{
    const char *path = "test_input.txt";
    FILE *file = fopen(path, "w");
    assert(file);
    assert(fputs(contents, file) >= 0);
    assert(fclose(file) == 0);

    Graph graph;
    bool loaded = load_graph(&graph, path);
    assert(remove(path) == 0);
    assert(loaded == valid);
    if (valid) {
        assert(graph.weight[SOURCE][1] == expected_edge);
        verify(&graph);
    }
}

int main(void)
{
    Graph graph;
    assert(load_graph(&graph, "campus.txt"));
    verify(&graph);
    check_input("", true, INF);
    check_input("15 0 999999999\n0 1 999999999\n1 2 999999999\n", true, INF);
    check_input("15 1 8\n15 1 0\n1 2 0\n15 2 0\n", true, 0);

    srand(3364);
    for (int trial = 0; trial < 50; ++trial) {
        for (int u = 0; u < BUILDINGS; ++u) {
            graph.weight[u][u] = INF;
            for (int v = u + 1; v < BUILDINGS; ++v) {
                long long cost = rand() % 100 < 15 ? rand() % 15 : INF;
                graph.weight[u][v] = graph.weight[v][u] = cost;
            }
        }
        verify(&graph);
    }

    check_input("15 0 -1\n", false, INF);
    check_input("15 19 1\n", false, INF);
    check_input("15 0 1 extra\n", false, INF);
    check_input("15 15 1\n", false, INF);
    puts("Passed 54 route cases against Floyd-Warshall and 4 invalid-input cases.");
    return EXIT_SUCCESS;
}
