#include "shortest_paths.h"

#include <stdio.h>
#include <stdlib.h>

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
