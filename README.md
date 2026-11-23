# Shortest Paths from the Computer Science Building

**CS 3364-001: Design and Analysis of Algorithms - Project 3**
Texas Tech University - Dr. Victor Sheng

This project finds the shortest walking route from the Computer Science building
to other buildings on the Texas Tech Campus. The campus is modeled as a weighted graph,
and the problem is solved in two ways: 

- **Dijkstra's Algorithm** (Greedy)
- **Bellman-Ford Algorithm** (Dynamic programming)

---

## Team

| Member | Contributions |
|---|---|
| Joshua Longoria | _TODO_ |
| Kylon Ford | Test Output and Sample Output |
| Mason Womack | _TODO_ |
| Marvin Stephens | _TODO_ |
| Mia Troncoso | _TODO_ |

---

## How the Problem Is Modeled

- **Vertices:** Campus buildings
- **Edges:** walkways between buildings
- **Weights:** walking distances
- **Source:** The Computer Science building

For every other building, the program outputs:
1. The shortest distance from the CS building
2. The route taken (the sequence of buildings)

---

## Algorithms

### Dijkstra's Algorithm (Greedy)
At each step it picks the closest bulding that hasn't been finalized
yet, then updates the distances to that building's neighbors. It is 
fast but **does not work with negative edge weights**

- Time: O((V + E) log V) with a binary heap (O(V^2) with a simple array)
- Space: O(V + E)

### Bellman-Ford Algorithm (Dynamic Programming)
It checks every edge V - 1 times. After pass *k*, it has the best path
that uses at most *k* edges. One extra pass detects **negative 
cycles**: if any distance still improves, a negative cycle exists.

- Time: O(V * E)
- Space: O(V + E)

### Path Reconstruction
Each algorithm stores the previous building on the best path to every
building. To get the full route, the program follows those links back
to the CS building and reverses the result.
