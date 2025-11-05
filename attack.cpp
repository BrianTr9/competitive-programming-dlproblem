/**
 * ATTACK - Minimum Cost Cannon Positioning
 * 
 * Problem Statement:
 * Kingdom X is under threat of attack from Empire Y. Empire Y has organized 
 * L military groups numbered 1 to L in a line attacking from the North.
 * Kingdom X built a fortress parallel to enemy formation, divided into L zones.
 * 
 * Kingdom X manufactured n heavy cannons with attack radius R.
 * A cannon at position i can destroy all enemy groups in range [i-R+1, i+R-1].
 * 
 * Initially, cannon i is placed at zone Aᵢ (1 ≤ Aᵢ ≤ L).
 * Moving a cannon to an adjacent zone costs 1 unit.
 * Final position xᵢ must satisfy: 1 ≤ xᵢ ≤ L.
 * 
 * Task: Find minimum cost to reposition cannons so that when fired simultaneously,
 * all enemy groups are destroyed.
 * 
 * Input (attack.inp):
 * - Line 1: Three integers n, L, R
 *   n = number of cannons (1 ≤ n ≤ 10⁵)
 *   L = number of enemy groups/zones (1 ≤ L ≤ 10⁷)
 *   R = attack radius
 * - Line 2: n integers Aᵢ (1 ≤ Aᵢ ≤ L) - initial positions
 * 
 * Output (attack.out):
 * - Single integer: minimum cost to destroy all enemies
 * 
 * Examples:
 * Input:   2 5 2        Input:   2 5 2
 *          3 5                   5 5
 * Output:  1            Output:  3
 * 
 * Explanation (Example 1):
 * - Cannon 1 at pos 3: covers [2,4]
 * - Cannon 2 at pos 5: covers [4,6] (but zone 6 doesn't exist, so [4,5])
 * - Zone 1 not covered! Move cannon 1 left by 1 → cost = 1
 * 
 * Algorithm Approaches:
 * - Sub1 (L ≤ 20): Brute force with bitmask - O(2^L × L)
 * - Sub2 (L = n×(2R-1)): Greedy assignment - O(n)
 * - Sub3 (General): Dynamic Programming - O(L × n)
 * 
 * Subtasks:
 * - Subtask 1 (25%): All values ≤ 100
 * - Subtask 2 (25%): All values ≤ 5000 and L = n×(2R-1)
 * - Subtask 3 (25%): n ≤ 20 and L ≤ 1000
 * - Subtask 4 (25%): n ≤ 1000 and L ≤ 10000
 * 
 * Time Complexity: O(L×n) for DP solution
 * Space Complexity: O(L)
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

template<class T> bool minimize(T &res, const T &x) { if (res > x) { res = x; return true; } return false; }

// File I/O helper function
void setupIO(string filename) {
    if (fopen((filename + ".INP").c_str(), "r")) {
        freopen((filename + ".INP").c_str(), "r", stdin);
        freopen((filename + ".OUT").c_str(), "w", stdout);
    }
}

const int N = 1e5 + 16;
const int Lim = 1e7 + 16;
const ll Linf = 2e18;



int n, L, R;               // n soldiers, L positions, R coverage radius
int arr[N], cnt[N];        // arr: soldier positions, cnt: coverage count

// Check if a bitmask assignment covers all L positions
bool check(int mask) {
    // Initialize coverage counter
    FOR(i, 1, L) cnt[i] = 0;
    
    // Mark coverage ranges using difference array technique
    FOR(i, 1, L) if (mask >> i - 1 & 1)
        cnt[max(1, i - R + 1)] += 1, cnt[min(L, i + R - 1) + 1] -= 1;

    // Check if all positions are covered
    FOR(i, 1, L) {
        cnt[i] += cnt[i - 1];
        if (cnt[i] == 0) return false;  // Position i is not covered
    }
    return true;
}

// Calculate total movement cost for a given assignment (bitmask)
ll calc(int mask) {
    int soldierIdx = 0;
    ll totalCost = 0;
    FOR(i, 1, L) if (mask >> i - 1 & 1) { 
        ++soldierIdx;
        totalCost += abs(arr[soldierIdx] - i);
    }
    return totalCost;
}

// Solution 1: Brute Force with Bitmask (L ≤ 20)
// Try all possible ways to assign n soldiers to L positions
void sub1() {
    int maxMask = (1LL << L) - 1;
    ll minCost = Linf;
    
    // Iterate through all bitmasks with exactly n bits set
    FOR(mask, 0, maxMask) if (__builtin_popcount(mask) == n) {
        if (check(mask)) {
            minimize(minCost, calc(mask));
        }
    }
    cout << minCost;
}

// Solution 2: Greedy Assignment (L = n*(2R-1))
// When positions perfectly fit soldiers with coverage radius R
void sub2() {
    ll totalCost = 0;
    
    // Assign soldier i to position ((i-1)*(2R-1) + R)
    // This ensures optimal spacing with coverage
    FOR(i, 1, n)
        totalCost += abs(arr[i] - ((i - 1) * (2 * R - 1) + R));
    
    cout << totalCost;
}

ll dp[Lim];  // dp[j] = minimum cost to cover positions [1..j] with assigned soldiers

// Solution 3: Dynamic Programming (General Case)
// dp[j] = minimum cost to cover all positions up to j
void sub3() {
    // Initialize: impossible to cover any position initially
    FOR(i, 0, L) dp[i] = Linf;
    dp[0] = 0;  // Base case: no positions to cover
    
    // Process each soldier
    FOR(i, 1, n) {
        // Try assigning soldier i to each position j
        // If assigned to j, it covers range [max(1,j-R+1), min(L,j+R-1)]
        FORD(j, L, 1)
            minimize(dp[min(L, j + R - 1)], 
                    dp[max(1, j - R + 1) - 1] + abs(arr[i] - j));

        // Propagate: if positions [1..j] are covered, then [1..j-1] are also covered
        FORD(j, L, 1)
            minimize(dp[j - 1], dp[j]);
    }
    
    cout << dp[L];  // Minimum cost to cover all L positions
}

void solve() {
    // Read input
    cin >> n >> L >> R;
    FOR(i, 1, n) cin >> arr[i];
    
    // Sort soldier positions for optimal assignment
    sort(arr + 1, arr + n + 1);

    // Choose solution based on constraints
    if (L <= 20) 
        sub1();  // Brute force for small L
    else if (L == 1LL * (2 * R - 1) * n) 
        sub2();  // Greedy for perfect spacing
    else 
        sub3();  // DP for general case
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    setupIO("ATTACK");

    int testCases = 1;
    // cin >> testCases;  // Uncomment for multiple test cases

    while (testCases-- > 0) {
        solve();
        cout << "\n";
    }
    
    return 0;
}
