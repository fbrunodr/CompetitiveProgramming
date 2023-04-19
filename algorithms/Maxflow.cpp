#include <bits/stdc++.h>
using namespace std;

class Maxflow{

    using i64 = long long;
    using edge = tuple<int, i64, i64>;
    using vi = vector<int>;
    using ii = pair<int, int>;

    const static i64 INF = 1e18; // large enough

private:
    int V;
    vector<edge> EL;
    vector<vi> AL;
    vi d, last;
    vector<ii> p;

    bool BFS(int s, int t){ // find augmenting path
        d.assign(V, -1);
        d[s] = 0;
        queue<int> q({s});
        p.assign(V, {-1, -1}); // record BFS sp tree
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (u == t)
                break; // stop as sink t reached
            for (auto &idx : AL[u])
            {                                                    // explore neighbors of u
                auto &[v, cap, flow] = EL[idx];                  // stored in EL[idx]
                if ((cap - flow > 0) && (d[v] == -1))            // positive residual edge
                    d[v] = d[u] + 1, q.push(v), p[v] = {u, idx}; // 3 lines in one!
            }
        }
        return d[t] != -1; // has an augmenting path
    }

    i64 send_one_flow(int s, int t, i64 f = INF){ // send one flow from s->t
        if (s == t)
            return f; // bottleneck edge f found
        auto &[u, idx] = p[t];
        auto &cap = get<1>(EL[idx]), &flow = get<2>(EL[idx]);
        i64 pushed = send_one_flow(s, u, min(f, cap - flow));
        flow += pushed;
        auto &rflow = get<2>(EL[idx ^ 1]); // back edge
        rflow -= pushed;                   // back flow
        return pushed;
    }

    i64 DFS(int u, int t, i64 f = INF){ // traverse from s->t
        if ((u == t) || (f == 0))
            return f;
        for (int &i = last[u]; i < (int)AL[u].size(); ++i){ // from last edge
            auto &[v, cap, flow] = EL[AL[u][i]];
            if (d[v] != d[u] + 1)
                continue; // not part of layer graph
            if (i64 pushed = DFS(v, t, min(f, cap - flow))){
                flow += pushed;
                auto &rflow = get<2>(EL[AL[u][i] ^ 1]); // back edge
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

public:
    Maxflow(int initialV) : V(initialV){
        EL.clear();
        AL.assign(V, vi());
    }

    // if you are adding a bidirectional edge u<->v with weight w into your
    // flow graph, set directed = false (default value is directed = true)
    void add_edge(int u, int v, i64 w, bool directed = true){
        if (u == v)
            return;                              // safeguard: no self loop
        EL.emplace_back(v, w, 0);                // u->v, cap w, flow 0
        AL[u].push_back(EL.size() - 1);          // remember this index
        EL.emplace_back(u, directed ? 0 : w, 0); // back edge
        AL[v].push_back(EL.size() - 1);          // remember this index
    }

    i64 edmonds_karp(int s, int t){
        i64 mf = 0; // mf stands for max_flow
        while (BFS(s, t)){  // an O(V*E^2) algorithm
            i64 f = send_one_flow(s, t); // find and send 1 flow f
            if (f == 0)
                break; // if f == 0, stop
            mf += f;   // if f > 0, add to mf
        }
        return mf;
    }

    i64 dinic(int s, int t){
        i64 mf = 0; // mf stands for max_flow
        while (BFS(s, t)){            // an O(V^2*E) algorithm
            last.assign(V, 0);        // important speedup
            while (i64 f = DFS(s, t)) // exhaust blocking flow
                mf += f;
        }
        return mf;
    }

    pair<vector<vi>, vector<edge>> getFlowGraph(){
        return {AL, EL};
    }
};
