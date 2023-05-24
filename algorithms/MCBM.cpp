#include<bits/stdc++.h>
using namespace std;

class MCBM{

    using vi = vector<int>;
    using ii = pair<int, int>;
    using vii = vector<ii>;

private:
    int V, VLeft;
    vector<vi>& AL;

    vi match, vis;

    int Aug(int L) {
        if (vis[L]) return 0;                          // L visited, return 0
        vis[L] = 1;
        for (auto &R : AL[L])
            if((match[R] == -1) || Aug(match[R])) {
                match[L] = R;                          // flip status
                match[R] = L;
                return 1;                              // found 1 matching
            }

        return 0;                                      // no matching
    }

public:

    MCBM(vector<vi>& _AL, int _VLeft) : AL(_AL), VLeft(_VLeft) {}

    /**
     * Returns MCBM and the matches
    */
    pair<int, vi> get(){
        unordered_set<int> freeV;
        for (int L = 0; L < VLeft; ++L)
            freeV.insert(L);                             // initial assumption
        V = AL.size();
        match = vi(V, -1);
        int MCBM = 0;
        // Greedy pre-processing for trivial Augmenting Paths
        // try commenting versus un-commenting this for-loop
        for (int L = 0; L < VLeft; L++) {              // O(V+E)
            vi candidates;
            for (auto& R : AL[L])
                if (match[R] == -1)
                    candidates.push_back(R);
            if ((int)candidates.size() > 0) {
                ++MCBM;
                freeV.erase(L);                            // L is matched
                int a = rand()%(int)candidates.size();     // randomize this
                int R = candidates[a];
                match[L] = R;
                match[R] = L;
            }
        }                                              // for each free vertex
        for (auto& f : freeV) {                        // (in random order)
            vis = vi(VLeft, 0);                        // reset first
            MCBM += Aug(f);                            // try to match f
        }

        return {MCBM, match};
    }

};
