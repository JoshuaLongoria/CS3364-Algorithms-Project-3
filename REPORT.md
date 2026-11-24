
## Problem

The goal of this program was to design and implement 2 different algorithms to map routes between buildings at Texas Tech. Those algorithms are the Dijkstra strategy and the Bellman-Ford Strategy. The Dijkstra strategy(aka the greedy strategy) looks at the available options and takes the path that is best in the moment. The Bellman-Ford strategy(aka Dynamic First Programming) is meant to find the shortest path by taking a layered approach, searching node by node and finding distance through iterations.

## Methodology

We designed two different algorithms to map routes between the buildings at Texas Tech. For this, we used the Dijkstra strategy and the Bellman-Ford strategy in the same file to map the routes on inception. We then tested these routes by implementing them in the test_routes.c file. This makes choosing the best route always possible so that it can always choose the best route.

The Dijkstra algorithm is designed to take the easiest path in the moment over and over again until it finds the optimal path to travel. This is done by first creating and setting all of the initial routes to be infinite and settle values to be false. Next, the algorithm checks for the closest building and if the building has been visited. If the building was visited, the path to that building is relaxed. The resulting map is then printed and the graph values and distances are stored.

The Bellman-Ford strategy is designed to take each level and find the shortest path level by level. This approach takes into account variables between levels and accounts for the shortest path. It also updates all paths to the shortest possible path. This also relaxes all untaken paths along the way. This approach ensures the quickest path is always taken. The resulting map is printed and the graph values and distances are stored.

## Experiment

We tested the algorithm with the tests found in test_routes.c. The tools used include verify_path, verify, and check_input. verify_path checks if the destination is reachable. Then, verify checks edges against Bellman-ford and Dijkstra to confirm the same output. Lastly, check_input creates a test graph with that input and validifies that the outcome is possible. The first test verifies that Campus.txt can be ran as a graph. The next test adds a node with an empty edge to verify that an isolated node can be detected. Test 3 checks how to algorithm would function when there are duplicate edges. Test 4 checks the output of a graph with a known solution to confirm they match. Test 5 randomly creates 50 different graphs to check for any potential errors. Test 6 checks the output after creating 4 different nodes that have invalid inputs. After running, test_routes.c printed that 54 of the tests worked perfectly, and the 4 invalid inputs were properly detected.

When the program is run, the file correctly compiles and prints out the results found in SampleOutput.txt. The first paragraph displays the outputs from Dijkstra algorithm, and the second paragraph is for Bellman-ford. The format of the list is name, then distance from computer science building, followed by the path taken. The path is orchestrated by source -> destination.



## Conclusion
