/**
 * SHLGOOD - Dãy Dịch Trái Tốt (Good Left-Shift Sequence)
 * 
 * Problem Statement:
 * Given an array A of n elements (A₁, A₂, ..., Aₙ).
 * A left-shift operation moves all elements left by 1, with A₁ moving to the end.
 * Result: (A₂, A₃, ..., Aₙ, A₁)
 * 
 * A sequence is called "good left-shift sequence" if:
 * - n is even
 * - After 0 or more left-shift operations, every element in first n/2 positions
 *   is greater than all elements in last n/2 positions (left to right)
 * 
 * Task: Count the number of contiguous subsequences that are "good left-shift sequences"
 * 
 * Input:
 * - Line 1: Integer n (1 ≤ n ≤ 5×10⁵)
 * - Line 2: n integers A₁, A₂, ..., Aₙ (-10⁹ ≤ Aᵢ ≤ 10⁹)
 * 
 * Output:
 * - Single integer: count of good left-shift subsequences
 * 
 * Example:
 * Input:  6
 *         1 3 2 6 4 5
 * Output: 7
 * Good subsequences: (1,3), (3,2), (2,6), (6,4), (4,5), (3,2,6,4), (1,3,2,6,4,5)
 * 
 * Algorithm:
 * - Use Fenwick Tree (BIT) for efficient range queries
 * - Use Disjoint Set Union (DSU) with path compression for interval merging
 * - Process elements in descending order of values
 * - Coordinate compression for handling large value ranges
 * 
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 * 
 * Constraints:
 * - 12% tests: n ≤ 500
 * - 24% tests: n ≤ 5000
 * - 20% tests: all elements distinct
 * - 44% tests: no additional constraints
 * 
 * Author: Truong Trung Bao
 * Source: DL Problem Set - Vietnam National Training Camp
 */

#include <bits/stdc++.h>
using namespace std;

//===============================TrB===============================//

#define ALL(v) (v).begin(), (v).end()
#define pb push_back

#define fi first
#define se second
#define mp make_pair
#define ii pair<int, int>

#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, n) for (int i = 0, _n = (n); i < _n; i++)

#define MASK(i) (1LL << (i))
#define BIT(x, i) (((x) >> (i)) & 1LL)

#define ll long long
#define ld long double

template<class M1, class M2> bool minimize(M1 &x, const M2 &y) {
    if (x > y) {x = y; return true;} return false;
}
template<class M1, class M2> bool maximize(M1 &x, const M2 &y) {
    if (x < y) {x = y; return true;} return false;
}
const int INF = (int)1e9 + 7;

/**
 * Fenwick Tree (Binary Indexed Tree)
 * Supports point update and prefix sum query in O(log n)
 */

struct FenwickTree {
    vector<int> tree;
    int n;
    
    FenwickTree(int _n = 0) {
        n = _n;
        tree.assign(n + 1, 0);
    }
    
    // Add val to position x
    void update(int x, int val) {
        for (; x <= n; x += x & -x) 
            tree[x] += val;
    }
    
    // Get prefix sum [1..x]
    int get(int x) {
        int res = 0;
        for (; x >= 1; x -= x & -x) 
            res += tree[x];
        return res;
    }
    
    // Find smallest index where prefix sum >= x
    // Binary search on Fenwick Tree
    int lowerBound(int x) {
        if (x == 0) return 0;
        
        int res = 0, sum = 0;
        int lg2 = 31 - __builtin_clz(n);
        
        FORD(i, lg2, 0) {
            if (res + MASK(i) <= n && sum + tree[res + MASK(i)] < x) {
                sum += tree[res + MASK(i)];
                res += MASK(i);
            }
        }
        return res + 1;
    }
};

#define MAX 500500

int n, a[MAX];                      // Array size and elements
int nextPos[MAX], prevPos[MAX];     // DSU arrays for finding next/prev active positions
vector<int> valueGroups[MAX];       // Group indices by value (after compression)

// DSU: Find next active position (with path compression)
int findNext(int x) {
    return nextPos[x] < 0 ? x : nextPos[x] = findNext(nextPos[x]);
}

// DSU: Find previous active position (with path compression)
int findPrev(int x) {
    return prevPos[x] < 0 ? x : prevPos[x] = findPrev(prevPos[x]);
}

// Check if intervals [x, findNext(x)] and [y, findNext(y)] intersect
bool intersect(int x, int y) {
    return findNext(x) < findNext(y);
}
// Range maximum and minimum for small test cases
int mx[1000 + 1][1000 + 1];
int mn[1000 + 1][1000 + 1];

// Naive solution for verification (O(n³))
void naive() {
    // Initialize range min/max arrays
    memset(mx, -0x3f, sizeof mx);
    memset(mn, 0x3f, sizeof mn);
    
    // Precompute range max and min for all [i,j]
    FOR(i, 1, n) FOR(j, i, n) {
        mx[i][j] = max(mx[i][j - 1], a[j]);
        mn[i][j] = min(mn[i][j - 1], a[j]);
    }
    
    int result = 0;
    
    // Check all even-length subsequences
    for (int len = 2; len <= n; len += 2) {
        FOR(l, 1, n - len + 1) {
            int r = l + len - 1;
            bool isGood = false;
            
            // Try all possible split points
            FOR(i, l, r - len / 2 + 1) {
                // Check if left half minimum > both adjacent maxima
                if (mn[i][i + len / 2 - 1] > max(mx[l][i - 1], mx[i + len / 2][r]))
                    isGood = true;
            }
            result += isGood;
        }
    }
    cout << result << " ";
}
void solve() {
    cin >> n;
    FOR(i, 1, n) cin >> a[i];
    
    // Coordinate compression: map values to ranks
    vector<int> uniqueValues;
    FOR(i, 1, n) uniqueValues.push_back(a[i]);
    sort(ALL(uniqueValues)); 
    uniqueValues.erase(unique(ALL(uniqueValues)), uniqueValues.end());
    
    // Group indices by compressed value
    FOR(i, 1, n) {
        int compressedValue = lower_bound(ALL(uniqueValues), a[i]) - uniqueValues.begin() + 1;
        valueGroups[compressedValue].push_back(i);
    }

    // Initialize DSU
    memset(nextPos, -1, sizeof nextPos);
    memset(prevPos, -1, sizeof prevPos);
    
    FenwickTree bit(n + 1);
    bit.update(n + 1, 1);  // Sentinel

    ll result = 0;
    
    // Process values in descending order
    FORD(valueRank, uniqueValues.size(), 1) {
        // Add current value's positions to active set
        for (auto i : valueGroups[valueRank]) {
            nextPos[i] = findNext(i + 1);
            prevPos[i] = findPrev(i - 1);
            bit.update(i, 1);
        }

        int minPos = INF, maxPos = 0;
        
        // Process consecutive positions with same value
        REP(i, valueGroups[valueRank].size()) {
            minimize(minPos, valueGroups[valueRank][i]);
            maximize(maxPos, valueGroups[valueRank][i]);
            
            // Check if intervals don't intersect with next group
            if (i + 1 != valueGroups[valueRank].size() && 
                !intersect(valueGroups[valueRank][i], valueGroups[valueRank][i + 1]))
                continue;

            // Calculate valid range for this group
            int leftBound = findPrev(valueGroups[valueRank][i]) + 1;
            int rightBound = findNext(valueGroups[valueRank][i]) - 1;
            
            int prevActive = bit.lowerBound(bit.get(leftBound) - 1) + 1;
            int nextActive = bit.lowerBound(bit.get(rightBound) + 1) - 1;
            
            int len = rightBound - leftBound + 1;
            int l = max(prevActive, leftBound - len);
            int r = min(nextActive, rightBound + len);
            
            // Count valid subsequences
            result += max(0, min(r - (l + len + len - 1) + 1, 
                                (r - len - len + 1) - l + 1));

            result += max(0, min(rightBound - minPos, 
                                leftBound - (minPos - leftBound + 1) - l + 1));
            result += max(0, min(maxPos - leftBound, 
                                r - (rightBound + rightBound - maxPos + 1) + 1));

            minPos = INF, maxPos = 0;
        }
    }
    
    cout << result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    freopen("SHLGOOD.inp", "r", stdin);
    freopen("SHLGOOD.out", "w", stdout);

    int testCases = 1; 
    // cin >> testCases;
    
    while (testCases--) solve();
    
    return 0;
}
