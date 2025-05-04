#ifndef FBRUNODR_CENTER_OF_SUBTREE
#define FBRUNODR_CENTER_OF_SUBTREE

#include "../header.hpp"

pair<int, vi> getFurthestAndPath(const vec<vi>& AL, int root, int boundary){
    int furthest;

    hash_map<int, int> parent;
    parent[root] = -1;
    queue<int> q;
    q.push(root);
    while(true){
        int u = q.front(); q.pop();
        int p = parent[u];
        for(auto& v : AL[u]){
            if(v == p || v == boundary) continue;
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

vi subtreeCenter(const vec<vi>& AL, int root, int u){
    f<int(int,int)> boundaryDfs = [&](int x, int p){
        int ans = -1;
        for(int y : AL[x]){
            if(y == p) continue;
            if(y == u)
                return x;
            else
                ans = max(ans, boundaryDfs(y, x));
        }
        return ans;
    };
    int boundary = -1;
    if(root == u)
        boundary = -1;
    else{
        boundary = boundaryDfs(root, -1);
        assert(boundary != -1);
    }

    auto [v, _path] = getFurthestAndPath(AL, root, boundary);
    auto [_v, path] = getFurthestAndPath(AL, v, boundary);
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

vi treeCenter(const vec<vi>& AL, int start){
    return subtreeCenter(AL, start, start);
}


#endif
