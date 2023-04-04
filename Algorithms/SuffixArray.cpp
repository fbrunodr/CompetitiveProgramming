#include <bits/stdc++.h>
using namespace std;


class SuffixArray{

using ii = pair<int, int>;
using vi = vector<int>;

private:
	vi RA; // rank array

	void countingSort(int k){		        // O(n)
		int maxi = max(300, n);				// up to 255 ASCII chars
		vi c(maxi, 0);						// clear frequency table
		for (int i = 0; i < n; ++i)			// count the frequency
			++c[i + k < n ? RA[i + k] : 0]; // of each integer rank

		for (int i = 0, sum = 0; i < maxi; ++i){
			int t = c[i];
			c[i] = sum;
			sum += t;
		}

		vi tempSA(n);
		for (int i = 0; i < n; ++i) // sort SA
			tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
			
		swap(SA, tempSA); // update SA
	}

	void constructSA(){ // can go up to 400K chars
		SA.resize(n);
		iota(SA.begin(), SA.end(), 0); // the initial SA
		RA.resize(n);
		for (int i = 0; i < n; ++i)
			RA[i] = T[i]; // initial rankings

		// repeat log_2 n times
		for (int k = 1; k < n; k <<= 1){ 
			// this is actually radix sort
			countingSort(k); // sort by 2nd item
			countingSort(0); // stable-sort by 1st item
			vi tempRA(n);
			int r = 0;
			tempRA[SA[0]] = r;			// re-ranking process
			for (int i = 1; i < n; ++i) // compare adj suffixes
				tempRA[SA[i]] =			// same pair => same rank r; otherwise, increase r
					((RA[SA[i]] == RA[SA[i - 1]]) && (RA[SA[i] + k] == RA[SA[i - 1] + k])) ? r : ++r;
			swap(RA, tempRA); // update RA
			if (RA[SA[n - 1]] == n - 1)
				break; // nice optimization
		}
	}

	void computeLCP(){
		vi Phi(n);
		vi PLCP(n);
		PLCP.resize(n);
		Phi[SA[0]] = -1;			// default value
		for (int i = 1; i < n; ++i) // compute Phi in O(n)
			Phi[SA[i]] = SA[i - 1]; // remember prev suffix
		for (int i = 0, L = 0; i < n; ++i)
		{ // compute PLCP in O(n)
			if (Phi[i] == -1)
			{
				PLCP[i] = 0;
				continue;
			} // special case
			while ((i + L < n) && (Phi[i] + L < n) && (T[i + L] == T[Phi[i] + L]))
				++L; // L incr max n times
			PLCP[i] = L;
			L = max(L - 1, 0); // L dec max n times
		}
		LCP.resize(n);
		for (int i = 0; i < n; ++i) // compute LCP in O(n)
			LCP[i] = PLCP[SA[i]];	// restore PLCP
	}

public:
	int n;   	   // the length of T
	string T;      // the input string
	vi SA;		   // Suffix Array
	vi LCP;		   // of adj sorted suffixes

	SuffixArray(string initialT) : T(initialT) {
		T.push_back((char)5); // small character. Usually '$' (not the case here obviously)
		n = T.size();
		constructSA(); // O(n log n)
		computeLCP();  // O(n)
	}

	/**
	 * Let lb be the idx of the smaller suffix that starts with
	 * string P. In the same way, let ub be the idx of the largest
	 * suffix that starts with P. This returns (lb, up). The
	 * number of matches is ub - lb + 1.
	 * If there are no suffixes that start with P, returns (-1,-1)
	*/
	ii stringMatching(const string& P){  // in O(m log n)
		int m = P.size();
        if(m > n)
            return {-1,-1};
		int lo = 0, hi = n - 1; 	// range = [0..n-1]
		while (lo < hi){						  // find lower bound
			int mid = (lo + hi) / 2;			  // this is round down
			int res = strncmp(T.c_str() + SA[mid], P.c_str(), m); // P in suffix SA[mid]?
			(res >= 0) ? hi = mid : lo = mid + 1; // notice the >= sign
		}
		if (strncmp(T.c_str() + SA[lo], P.c_str(), m) != 0)
			return {-1, -1};  // if not found
		ii ans;
		ans.first = lo;
		hi = n - 1;  // range = [lo..n-1]
		while (lo < hi){  // now find upper bound
			int mid = (lo + hi) / 2;
			int res = strncmp(T.c_str() + SA[mid], P.c_str(), m);
			(res > 0) ? hi = mid : lo = mid + 1;  // notice the > sign
		}
		if (strncmp(T.c_str() + SA[hi], P.c_str(), m) != 0)
			--hi;  // special case
		ans.second = hi;
		return ans;  // returns (lb, ub)
	}				 // where P is found

	/**
	 * Returns size and idx of Longest Repeating Substring of T
	 * (length, index)
	*/
	ii LRS(){
		int idx = 0, maxLCP = -1;
		for (int i = 1; i < n; ++i) // O(n), start from i = 1
			if (LCP[i] > maxLCP)
				maxLCP = LCP[i], idx = i;
		return {maxLCP, idx};
	}

	/**
	 * Let T = A + '#' + B
	 * Let split_idx be the 0-based position of character '#'
	 * This returns the longest common substring of strings
	 * A and B
	 * (length, index)
	*/
	ii LCS(int split_idx){
		// (LCS length, index)
		int idx = 0, maxLCP = -1;
		for (int i = 1; i < n; ++i){
			// O(n), start from i = 1
			// if suffix SA[i] and suffix SA[i-1] came from the same string, skip
			if ((SA[i] < split_idx) == (SA[i - 1] < split_idx))
				continue;
			if (LCP[i] > maxLCP)
				maxLCP = LCP[i], idx = i;
		}
		return {maxLCP, idx};
	}
};
