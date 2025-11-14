/**
 * ATTACK - Minimum Cost Cannon Positioning
 * File Input:  attack.inp
 * File Output: attack.out
 * 
 * Problem Statement:
 * Kingdom X is under threat from Empire Y, which has organized L military groups
 * (numbered 1 to L) in a line attacking from the North. Kingdom X has built a
 * fortress parallel to the enemy formation, divided into L zones.
 * 
 * Kingdom X has manufactured N heavy cannons with attack radius R. Each cannon
 * can destroy all enemy groups in its attack range [position - R + 1, position + R - 1].
 * 
 * Initially, cannon i is placed at zone pᵢ (1 ≤ pᵢ ≤ L).
 * Moving a cannon to an adjacent zone costs 1 unit.
 * Final position qᵢ must satisfy: 1 ≤ qᵢ ≤ L.
 * 
 * Task: Find the minimum cost to reposition cannons so that when fired
 * simultaneously, all L enemy groups are destroyed.
 * 
 * Input (attack.inp):
 * - Line 1: Three integers N, L, R
 *   N = number of cannons
 *   L = number of enemy groups/zones
 *   R = attack radius
 * - Line 2: N integers pᵢ (1 ≤ pᵢ ≤ L) - initial cannon positions
 * 
 * Output (attack.out):
 * - Single integer: minimum cost to destroy all enemy groups
 * 
 * Examples:
 * Example 1:
 *   Input:  2 5 2
 *           3 5
 *   Output: 1
 *   Explanation: Cannon 1 at pos 3 covers [2,4]; Cannon 2 at pos 5 covers [4,5].
 *   Zone 1 is not covered. Move cannon 1 left by 1 → cost = 1. Zones covered: [1,5].
 * 
 * Example 2:
 *   Input:  2 5 2
 *           5 5
 *   Output: 3
 * 
 * Algorithm Approaches:
 * - Subtask 1: Brute force with bitmask - O(2^L)
 * - Subtask 2 (special case L = N×(2R-1)): Greedy - O(N)
 * - General: Dynamic Programming - O(L×N)
 * 
 * Constraints (Subtasks):
 * - Subtask 1 (25%): All values ≤ 10
 * - Subtask 2 (25%): All values ≤ 1000 and (2R-1)×N = L
 * - Subtask 3 (25%): 1 ≤ N ≤ 10³, 1 ≤ L, pᵢ, R ≤ 10⁸
 * - Subtask 4 (25%): 1 ≤ N ≤ 10⁵, 1 ≤ L, pᵢ, R ≤ 10⁸
 * 
 * Time Complexity: O(L×N) for DP solution
 * Space Complexity: O(L)
 * 
 * Author: Truong Trung Bao
 * Source: DL Problem Set - Vietnam National Informatics Training Camp 2022
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
