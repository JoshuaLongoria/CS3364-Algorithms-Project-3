
## Problem

The goal of this program was to design and implement 2 different algorithms to map routes between buildings at Texas Tech. Those algorithms are the Dijkstra strategy and the Bellman-Ford Strategy. The Dijkstra strategy(aka the greedy strategy) looks at the available options and takes the path that is best in the moment. The Bellman-Ford strategy(aka Dynamic First Programming) is meant to find the shortest path by taking a layered approach, searching node by node and finding distance through iterations.

## Methodology

We designed two different algorithms to map routes between the buildings at Texas Tech. For this, we used the Dijkstra strategy and the Bellman-Ford strategy in the same file to map the routes on inception. We then tested these routes by implementing them in the test_routes.c file. This makes choosing the best route always possible so that it can always choose the best route.

The Dijkstra algorithm is designed to take the easiest path in the moment over and over again until it finds the optimal path to travel. This is done by first creating and setting all of the initial routes to be infinite and settle values to be false. Next, the algorithm checks for the closest building and if the building has been visited. If the building was visited, the path to that building is relaxed. The resulting map is then printed and the graph values and distances are stored.

The Bellman-Ford strategy is designed to take each level and find the shortest path level by level. This approach takes into account variables between levels and accounts for the shortest path. It also updates all paths to the shortest possible path. This also relaxes all untaken paths along the way. This approach ensures the quickest path is always taken. The resulting map is printed and the graph values and distances are stored.

## Experiment





## Conclusion