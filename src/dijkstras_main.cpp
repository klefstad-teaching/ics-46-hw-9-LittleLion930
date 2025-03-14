#include "dijkstras.h"
#include <vector>

int dijkstras_main() {
    Graph G;
    file_to_graph("graph.txt", G);

    int source = 0;
    vector<int> previous;
    vector<int> distances;
    distances = dijkstra_shortest_path(G, source, previous);

    for (int dest = 0; dest < G.numVertices; ++dest) {
        vector<int> path = extract_shortest_path(distances, previous, dest);
        print_path(path, distances[dest]);
    }

    return 0;
}