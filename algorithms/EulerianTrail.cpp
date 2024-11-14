#include<bits/stdc++.h>
using namespace std;
template<typename T>
using vec = vector<T>;

// Hierholzer algorithm
template<typename MapLike, typename T>
vec<T> getEulerianTrail(MapLike adj, T start_vertex, bool undirected=false){
    stack<T> path;
    vec<T> circuit;

    T u = start_vertex;

    path.push(u);

    while (path.size() > 0) {
        T u = path.top();

        if (adj[u].size() > 0) {
            // Find and remove the next vertex that is
            // adjacent to the current vertex
            auto iterator_u = adj[u].begin();
            T v = *iterator_u;
            adj[u].erase(iterator_u);
            if(undirected){
                auto iterator_v = adj[v].find(u);
                if(iterator_v != adj[v].end())
                    adj[v].erase(iterator_v);
            }

            path.push(v);
        }
        // back-track to find remaining circuit
        else {
            circuit.push_back(path.top());
            path.pop();
        }
    }

    reverse(circuit.begin(), circuit.end());
    return circuit;
}