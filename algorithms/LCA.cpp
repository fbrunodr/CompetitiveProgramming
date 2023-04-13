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
        for (auto &v : AL[u])
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
        segTree = FrozenSegTree<int>(aux, conquerer, -1);
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
        for (auto &v : AL[u])
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
