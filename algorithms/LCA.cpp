#include "../dataStructures/FrozenSegTree.cpp"
#include "../dataStructures/SparseTable.cpp"

class SegLCA{

    using vi = vector<int>;

    private:
    int n;
    vector<vi> AL;
    vi L, E, H;
    FrozenSegTree<int> segTree;

    int idx;
    vector<bool> vis;
    void dfs(int u, int depth){
        vis[u] = true;
        H[u] = idx;
        E[idx] = u;
        L[idx++] = depth;
        for(auto &v : AL[u])
            if(!vis[v]){
                dfs(v, depth+1);
                E[idx] = u; // backtrack to current node
                L[idx++] = depth;
            }
    }

    public:
    SegLCA(const vector<vi>& AL_, int root){
        AL = AL_;
        n = AL.size();

        L = vi(2*n);
        E = vi(2*n);
        H = vi(n, -1);
        idx = 0;
        vis = vector<bool>(n, false);
        dfs(root,0);

        auto conquerer = [this](int i, int j){
            return this->L[i] < this->L[j] ? i : j;
        };

        vi aux(2*n);
        for(int i = 0; i < 2*n; i++)
            aux[i] = i;
        segTree = FrozenSegTree<int>(aux, conquerer);
    }

    int lca(int u, int v){
        if(H[u] > H[v])
            swap(u, v);
        return E[segTree.RQ(H[u], H[v])];
    }

    int depth(int u){
        return L[H[u]];
    }
};


class SpTLCA{

    using vi = vector<int>;

    private:
    int n;
    vector<vi> AL;
    vi L, E, H;
    SparseTable<int> sparseTable;

    int idx;
    vector<bool> vis;
    void dfs(int u, int depth){
        vis[u] = true;
        H[u] = idx;
        E[idx] = u;
        L[idx++] = depth;
        for(auto &v : AL[u])
            if(!vis[v]){
                dfs(v, depth+1);
                E[idx] = u; // backtrack to current node
                L[idx++] = depth;
            }
    }

    public:
    SpTLCA(const vector<vi>& AL_, int root){
        AL = AL_;
        n = AL.size();

        L = vi(2*n);
        E = vi(2*n);
        H = vi(n, -1);
        idx = 0;
        vis = vector<bool>(n, false);
        dfs(root,0);

        auto conquerer = [this](int i, int j){
            return this->L[i] < this->L[j] ? i : j;
        };

        vi aux(2*n);
        for(int i = 0; i < 2*n; i++)
            aux[i] = i;
        sparseTable = SparseTable<int>(aux, conquerer);
    }

    int lca(int u, int v){
        if(H[u] > H[v])
            swap(u, v);
        return E[sparseTable.RQ(H[u], H[v])];
    }

    int depth(int u){
        return L[H[u]];
    }
};


class BinaryLiftLCA {
    using vi = vector<int>;

    private:
    int n;
    int L2_n;
    vector<vi> AL;
    vi _depth;
    vector<vi> ancestor;

    void dfs(int u, int d){
        _depth[u] = d;
        for(auto &v : AL[u])
            if(_depth[v] == -1){
                ancestor[0][v] = u;
                dfs(v, d+1);
            }
    }

    int _lca(int u, int v){
        if(u == v) return u;
        for(int h = 1; h < L2_n; h++)
            if(ancestor[h][u] == ancestor[h][v])
                return _lca(ancestor[h-1][u], ancestor[h-1][v]);
        return _lca(ancestor[L2_n - 1][u], ancestor[L2_n - 1][v]);
    }

    public:
    BinaryLiftLCA(const vector<vi>& _AL, int root){
        AL = _AL;
        n = AL.size();
        _depth = vi(n, -1);

        L2_n = (int)log2(n) + 1;
        ancestor = vector<vi>(L2_n, vi(n, -1));

        dfs(root, 0);
        for(int h = 1; h < L2_n; h++)
            for(int u = 0; u < n; u++){
                int k_ancestor = ancestor[h-1][u];
                if(k_ancestor == -1) continue;
                ancestor[h][u] = ancestor[h-1][k_ancestor];
            }
    }

    int k_ancestor(int u, int k){
        if(k == 0) return u;
        if(k > _depth[u]) return -1;

        while(k){
            int h = (int)log2(k);
            u = ancestor[h][u];
            k -= (1<<h);
        }

        return u;
    }

    int lca(int u, int v){
        if(_depth[u] > _depth[v]) swap(u, v);
        int k = _depth[v] - _depth[u];
        v = k_ancestor(v, k);
        return _lca(u, v);
    }

    int depth(int u){
        return _depth[u];
    }
};
