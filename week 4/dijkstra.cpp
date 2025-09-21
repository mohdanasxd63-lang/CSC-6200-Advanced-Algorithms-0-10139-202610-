#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <stack>
#include <climits>
#include <cctype>
using namespace std;

class Graph {
    unordered_map<char, vector<pair<char,int>>> adj;

public:
    void addEdge(char u, char v, int weight) {
        adj[u].push_back({v, weight});
    }

    void dijkstra(char start, char end) {
        unordered_map<char,int> dist;
        unordered_map<char,char> parent;
        auto cmp = [&](pair<int,char> &a, pair<int,char> &b) {
            return a.first > b.first;
        };
        priority_queue<pair<int,char>, vector<pair<int,char>>, decltype(cmp)> pq(cmp);

        // initialize distances
        for (auto &node : adj) dist[node.first] = INT_MAX;
        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [d,u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue;

            for (auto &[v,w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        // no path
        if (dist[end] == INT_MAX) {
            cout << "No path exists from " << start << " to " << end << endl;
            cout << "-----------------------" << endl;
            return;
        }

        // shortest distance
        cout << "Shortest distance from " << start << " to " << end 
             << " is " << dist[end] << endl;

        // reconstruct path
        stack<char> path;
        char node = end;
        while (node != start) {
            path.push(node);
            node = parent[node];
        }
        path.push(start);

        cout << "Path: ";
        while (!path.empty()) {
            cout << path.top();
            path.pop();
            if (!path.empty()) cout << " -> ";
        }
        cout << endl;
        cout << "-----------------------" << endl;
    }
};

int main() {
    Graph g;

    // Hard-coded graph from class diagram
    g.addEdge('A','B',10);
    g.addEdge('A','E',3);
    g.addEdge('B','C',2);
    g.addEdge('B','E',4);
    g.addEdge('E','B',1);
    g.addEdge('E','C',8);
    g.addEdge('E','D',2);
    g.addEdge('C','D',9);
    g.addEdge('D','C',7);

    char start, end;
    // Loop through multiple test cases (works with redirected input)
    while (cin >> start >> end) {
        // Normalize to uppercase if lowercase given
        start = toupper(start);
        end   = toupper(end);
        g.dijkstra(start, end);
    }

    return 0;
}
