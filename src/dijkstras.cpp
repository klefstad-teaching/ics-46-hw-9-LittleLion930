#include "dijkstras.h"
#include <algorithm>

/* function dijkstra(source, graph):
    n = graph.adjacencyList.size()

    graph.distance.resize(n, INT_MAX)
    graph.previous.resize(n, -1)
    graph.visited.resize(n, false)

    priorityQueue pq
    pq.push(Node(source, 0))
    graph.distance[source] = 0

    while !pq.empty():
        current = pq.pop_top()

        u = current.vertex

        if graph.visited[u]:
            continue

        graph.visited[u] = true

        for each neighbor in graph.adjacencyList[u]:
            v = neighbor.vertex
            weight = neighbor.weight


            if !graph.visited[v] and graph.distance[u] + weight < graph.distance[v]:
                graph.distance[v] = graph.distance[u] + weight
                graph.previous[v] = u
                pq.push(Node(v, graph.distance[v]))

end function */

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    const int n = G.numVertices;
    vector<int> distances(n, INF);

    previous.resize(n, -1);
    vector<bool> visited(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    distances[source] = 0;
    pq.emplace(0, source);

    while (!pq.empty()) {
        auto [dist_u, u] = pq.top();
        pq.pop();

        if (visited[u]) 
            continue;

        visited[u] = true;

        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;

            if (!visited[v] && distances[v] > dist_u + weight) {
                distances[v] = dist_u + weight;
                previous[v] = u;
                pq.emplace(distances[v], v);
            }

        }
    }
    return distances;
} 

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) return path;

    for (int current = destination; current != -1; current = previous[current]) {
        path.push_back(current);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    if (v.empty()) {
        cout << "No path exists" << endl;
        return;
    }

    cout << "Path: ";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i < v.size() - 1) cout << " ";
    }
    cout << " " << endl;
    cout << "Total cost is " << total << endl;
}