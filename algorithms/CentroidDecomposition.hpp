#ifndef FBRUNODR_CENTROID_DECOMPOSITION
#define FBRUNODR_CENTROID_DECOMPOSITION

#include "../header.hpp"

class CentroidDecomposition{
    vec<vi> adj;
    vi subtree_size;
    vec<bool> is_removed;
    vec<vi> ancestors;

    int get_subtree_size(int node, int parent = -1) {
        subtree_size[node] = 1;
        for (int child : adj[node]) {
            if (child == parent || is_removed[child])
                continue;
            subtree_size[node] += get_subtree_size(child, node);
        }
        return subtree_size[node];
    }

    int get_centroid(int node, int tree_size, int parent = -1) {
        for (int child : adj[node]){
            if (child == parent || is_removed[child])
                continue;
            if (subtree_size[child] * 2 > tree_size)
                return get_centroid(child, tree_size, node);
        }
        return node;
    }

    void set_ancestors(int node, int centroid, int parent = -1) {
        ancestors[node].push_back(centroid);
        for (int child : adj[node]) {
            if (child == parent || is_removed[child])
                continue;
            set_ancestors(child, centroid, node);
        }
    }

    void build_centroid_decomp(int node) {
        int centroid = get_centroid(node, get_subtree_size(node));

        for (int child : adj[centroid]) {
            if (is_removed[child])
                continue;
            set_ancestors(child, centroid, centroid);
        }

        is_removed[centroid] = true;
        for (int child : adj[centroid]) {
            if (is_removed[child])
                continue;
            // build the centroid decomposition for all child components
            build_centroid_decomp(child);
        }
    }

    public:
    CentroidDecomposition(vec<vi>& _adj, int start_node=0){
        adj = _adj;
        int size = adj.size();
        subtree_size = vi(size);
        is_removed = vec<bool>(size);
        ancestors = vec<vi>(size);
        build_centroid_decomp(start_node);
    }

    vi get_ancestors(int u){
        return ancestors[u];
    }
};

#endif
