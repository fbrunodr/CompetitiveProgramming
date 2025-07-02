#ifndef FBRUNODR_HDL
#define FBRUNODR_HDL

#include "../algorithms/LCA.hpp"

void setParentSizeInOutChainTop(vec<vi> al, int root, vi& parent, vi& siz, vi& in, vi& out, vi& chainTop){
    int n = al.size();
    parent = vi(n, -1);
    siz = vi(n, 0);
    f<void(int, int)> dfs_size = [&](int u, int p) {
        siz[u] = 1;
        for(int& v : al[u]) {
            if(v == p) continue;
            parent[v] = u;
            dfs_size(v, u);
            siz[u] += siz[v];
            // heavy child stays in the first position
            if(al[u][0] == p || siz[v] > siz[al[u][0]])
                swap(v, al[u][0]);
        }
    };
    dfs_size(root, -1);

    int t = 0;
    in = vi(n), out = vi(n), chainTop = vi(n);
    f<void(int, int)> dfs_hld = [&](int u, int p) {
        in[u] = t++;
        for(auto v : al[u]) {
            if(v == p) continue;
            chainTop[v] = ((v == al[u][0]) ? chainTop[u] : v);
            dfs_hld(v, u);
        }
        out[u] = t;
    };
    chainTop[root] = root;
    dfs_hld(root, -1);
}


// Best with max / min / gcd / lcm / etc. operations
template<typename T>
class IdempotentHLD {
    private:
    f<T(T,T)> merge;
    SparseTable<T> st;

    vi in, out, chainTop, parent, siz;
    vec<T> a;

    T queryDescending(int ancestor, int u){
        T ans = a[in[u]];
        while(chainTop[u] != chainTop[ancestor]){
            ans = merge(ans, st.RQ(in[chainTop[u]], in[u]));
            u = parent[chainTop[u]];
        }
        return merge(ans, st.RQ(in[ancestor], in[u]));
    }

    public:
    SpTLCA lca;

    IdempotentHLD() {}

    IdempotentHLD(const vec<vi>& al, const vec<T>& _vals, int root, f<T(T,T)> _merge) : lca(al, root), merge(_merge) {
        setParentSizeInOutChainTop(al, root, parent, siz, in, out, chainTop);

        int n = al.size();
        a = vec<T>(n);
        for(int u = 0; u < n; u++)
            a[in[u]] = _vals[u];

        st = SparseTable<T>(a, merge);
    }

    T queryPath(int u, int v){
        int l = lca.lca(u, v);
        return merge(queryDescending(l, u), queryDescending(l, v));
    }

    T querySubtree(int u){
        return st.RQ(in[u], out[u] - 1);
    }
};


template<
    typename DataType,
    typename LazyType,
    typename internalUpdatorType = f<void(DataType&, LazyType)>
>
class LazyHLD {
    using T = DataType;
    using Q = LazyType;

    private:
    f<T(T,T)> merge;
    LazySegTree<T, Q, internalUpdatorType> lazySegTree;

    vi in, out, chainTop, parent, siz;
    vec<T> a;

    T queryDescending(int ancestor, int u){
        T ans = a[in[u]];
        while(chainTop[u] != chainTop[ancestor]){
            ans = merge(ans, lazySegTree.RQ(in[chainTop[u]], in[u]));
            u = parent[chainTop[u]];
        }
        return merge(ans, lazySegTree.RQ(in[ancestor], in[u]));
    }

    void updateDescending(int ancestor, int u, Q val){
        while(chainTop[u] != chainTop[ancestor]){
            lazySegTree.rangeUpdate(in[chainTop[u]], in[u], val);
            u = parent[chainTop[u]];
        }
        lazySegTree.rangeUpdate(in[ancestor], in[u], val);
    }

    public:
    BinaryLiftLCA lca;

    LazyHLD() {}

    LazyHLD(
        const vec<vi>& al,
        const vec<T>& _vals,
        int root,
        f<T(T,T)> _merge,
        internalUpdatorType _nodeUpdator,
        f<void(Q&,Q)> _lazyUpdator
    ) : lca(al, root), merge(_merge) {
        setParentSizeInOutChainTop(al, root, parent, siz, in, out, chainTop);

        int n = al.size();
        a = vec<T>(n);
        for(int u = 0; u < n; u++)
            a[in[u]] = _vals[u];

        lazySegTree = LazySegTree<T, Q, internalUpdatorType>(a, merge, _nodeUpdator, _lazyUpdator);
    }

    T queryPath(int u, int v){
        int l = lca.lca(u, v);
        if(l == v)
            return queryDescending(l, u);
        int l2 = lca.k_ancestor(v, lca.depth(v) - lca.depth(l) - 1);
        return merge(queryDescending(l, u), queryDescending(l2, v));
    }

    void updatePath(int u, int v, Q val){
        int l = lca.lca(u, v);
        updateDescending(l, u, val);

        if(l != v){
            int l2 = lca.k_ancestor(v, lca.depth(v) - lca.depth(l) - 1);
            updateDescending(l2, v, val);
        }
    }

    T querySubtree(int u){
        return lazySegTree.RQ(in[u], out[u] - 1);
    }

    void updateSubtree(int u, Q val){
        lazySegTree.rangeUpdate(in[u], out[u] - 1, val);
    }
};

#endif