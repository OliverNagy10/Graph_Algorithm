# Graph Algorithms in C++

This C++ project is an implementation of fundamental graph algorithms for analyzing road distance data sourced from the OpenStreetMap (OSM) project. The program, `streets.cc`, demonstrates proficiency in handling graph-related queries. Below is an overview of the algorithms and techniques employed:

## Graph Representation

The graph is represented using an adjacency list format. Each vertex stores its neighbors in a linked list, organized within a vector. This allows for efficient storage and retrieval of adjacency information.

## Query 2: Most Edges

The algorithm identifies the vertex with the maximum number of edges. It iterates through the vertices, counting their edges and tracking the vertex with the highest count.

## Query 3: Average Edges

This query calculates the average number of edges across all vertices in the graph.

## Query 4 and Query 5: Neighbors

The `Neighbours` function finds neighbors of a vertex, either 1 edge away or k edges away, using a breadth-first search (BFS)-like approach.

## Query 6: Shortest Path Using XYZ (Dijkstra's Algorithm)

The algorithm employs Dijkstra's algorithm to find the shortest path between two specified nodes using x-y coordinates.

## Query 7: Shortest Path Using Edges (BFS)

This query utilizes Breadth-First Search (BFS) to find the shortest path between two nodes based on the edges.

These algorithms, implemented in C++, offer efficient solutions for various graph-related queriers.
![Graph](https://github.com/OliverNagy10/Graph_Algorithm/blob/main/sample_data/Graphs.png)
