#ifndef FBRUNODR_CENTER_OF_SUBTREE
#define FBRUNODR_CENTER_OF_SUBTREE

#include "../header.hpp"

pair<int, vi> getFurthestAndPath(int root, const vec<vi>& AL){
    int furthest;

    hash_map<int, int> parent;
    parent[root] = -1;
    queue<int> q;
    q.push(root);
    while(true){
        int u = q.front(); q.pop();
        for(auto& v : AL[u]){
            if(parent.count(v))
                continue;
            parent[v] = u;
            q.push(v);
        }
        if(q.empty()){
            furthest = u;
            break;
        }
    }

    vi path;
    int u = furthest;
    while(u != -1){
        path.push_back(u);
        u = parent[u];
    }

    reverse(path.begin(), path.end());
    return {furthest, path};
}

vi getCenter(int root, const vec<vi>& AL){
    auto [u, _] = getFurthestAndPath(root, AL);
    auto [v, path] = getFurthestAndPath(u, AL);
    // single center
    if(path.size() % 2 == 1){
        int k = path.size() / 2;
        return vi{path[k]};
    }
    // two center
    else{
        int k = path.size() / 2;
        return vi{path[k-1], path[k]};
    }
}


#endif
