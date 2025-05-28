#ifndef FBRUNODR_EULERIAN_TRAIL
#define FBRUNODR_EULERIAN_TRAIL

#include "../header.hpp"

// Hierholzer algorithm
template<bool undirected = false, typename MapLike, typename T>
vec<T> getEulerianTrail(MapLike adj, T start_vertex){
    stack<T> path;
    vec<T> circuit;

    T u = start_vertex;

    path.push(u);

    while (path.size() > 0) {
        T u = path.top();

        if (adj[u].size() > 0) {
            // Find and remove the next vertex that is
            // adjacent to the current vertex
            T v;
            if constexpr (std::is_same_v<MapLike, vec<vec<T>>>) {
                v = adj[u].back();
                adj[u].pop_back();
            } else {
                auto iterator_u = adj[u].begin();
                v = *iterator_u;
                adj[u].erase(iterator_u);
            }
            if constexpr (undirected) {
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

#endif
