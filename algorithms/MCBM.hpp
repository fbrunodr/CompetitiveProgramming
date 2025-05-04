#ifndef FBRUNODR_MCBM
#define FBRUNODR_MCBM

#include "../header.hpp"


pair<int, vi> MCBM(vec<vi>& AL, int nLeft){
    hash_set<int> freeV;
    for (int L = 0; L < nLeft; ++L)
        freeV.insert(L);                             // initial assumption
    int n = AL.size();
    vi match(n, -1);
    int cardinality = 0;
    // Greedy pre-processing for trivial Augmenting Paths
    // try commenting versus un-commenting this for-loop
    for (int L = 0; L < nLeft; L++) {               // O(V+E)
        vi candidates;
        for (auto& R : AL[L])
            if (match[R] == -1)
                candidates.push_back(R);
        if ((int)candidates.size() > 0) {
            ++cardinality;
            freeV.erase(L);                         // L is matched
            int a = rng_32() % candidates.size();   // randomize this
            int R = candidates[a];
            match[L] = R;
            match[R] = L;
        }
    }

    vi vis;
    f<int(int)> aug = [&](int L) {
        if (vis[L]) return 0;                       // L visited, return 0
        vis[L] = 1;
        for (auto &R : AL[L])
            if((match[R] == -1) || aug(match[R])) {
                match[L] = R;                       // flip status
                match[R] = L;
                return 1;                           // found 1 matching
            }

        return 0;                                   // no matching
    };

    for (auto& f : freeV) {                         // for each free vertex (in random order)
        vis = vi(nLeft, 0);                         // reset first
        cardinality += aug(f);                      // try to match f
    }

    return {cardinality, match};
}


#endif
