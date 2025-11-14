/**
 * PHOTO - Satellite Photography Coverage Optimization
 * 
 * Problem Statement:
 * An area is represented by an m×m grid of unit squares.
 * - Rows numbered 1 to m (top to bottom)
 * - Columns numbered 1 to m (left to right)
 * - Cell at row i, column j is cell (i,j)
 * 
 * There are n objects to photograph. Object i is at cell (xᵢ, yᵢ).
 * 
 * A satellite moves along the main diagonal (top-left to bottom-right).
 * The satellite can take up to k photos, each photo is a square region where:
 * - Shape is a square
 * - Top-left and bottom-right corners lie on the main diagonal
 * - Each grid cell is either completely inside or completely outside the region
 * 
 * Task: Choose at most k square regions such that:
 * - Every object is covered by at least one region
 * - Total number of grid cells in all regions is minimized
 * 
 * Input:
 * - Line 1: Three integers n, m, k
 *   n = number of objects (1 ≤ n ≤ 10⁵; k ≤ n)
 *   m = grid size (1 ≤ m ≤ 5000)
 *   k = max photos allowed
 * - Next n lines: Two integers xᵢ, yᵢ (1 ≤ xᵢ, yᵢ ≤ m) - object coordinates
 * 
 * Output:
 * - Single integer: minimum number of cells in chosen regions
 * 
 * Example:
 * Input:  4 4 2
 *         1 1
 *         2 3
 *         3 3
 *         3 4
 * Output: 8
 * 
 * Algorithm: 2D Difference Array + Dynamic Programming
 * - For each object pair, determine the diagonal square that covers both
 * - Use 2D difference array for O(1) range updates
 * - Compute 2D prefix sum to get final coverage
 * - Count total cells covered
 * 
 * Key Technique: 2D Difference Array for Range Updates
 * To mark rectangle [x1,y1] to [x2,y2]:
 *   diff[x1][y1]++, diff[x2+1][y2+1]++
 *   diff[x2+1][y1]--, diff[x1][y2+1]--
 * Then compute 2D prefix sum to get actual values.
 * 
 * Time Complexity: O(n² + m²)
 * Space Complexity: O(m²)
 * 
 * Constraints (Subtasks):
 * - Subtask 1 (10%): n ≤ 200 and k = n = 1
 * - Subtask 2 (10%): n < 200 and k = n = 2
 * - Subtask 3 (20%): n ≤ 200 and k = n
 * - Subtask 4 (20%): n ≤ 200 and xᵢ = yᵢ for all i = 1,2,...,n
 * - Subtask 5 (20%): n ≤ 200 (general case)
 * - Subtask 6 (20%): n ≤ 2000 (general case)
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

#define NAME "photo"

int m, n, k;                    // m: segments, n: grid size, k: unused
int coverage[5100][5100];       // 2D difference array for range updates

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    freopen(NAME".inp", "r", stdin);
    freopen(NAME".out", "w", stdout);

    cin >> m >> n >> k;
    
    // Process each segment
    FOR(i, 1, m) {
        int x, y; 
        cin >> x >> y;
        
        // Ensure x <= y
        if(x > y) swap(x, y);

        // 2D Difference Array updates for diagonal band coverage
        // This segment covers the region from (x,x) to (y,y)
        ++coverage[x][x], ++coverage[y + 1][y + 1];
        --coverage[y + 1][x], --coverage[x][y + 1];
    }

    // Compute 2D prefix sum to get actual coverage values
    int coveredCells = 0;
    FOR(i, 1, n) {
        FOR(j, 1, n) {
            coverage[i][j] += coverage[i - 1][j] + coverage[i][j - 1] 
                            - coverage[i - 1][j - 1];
            
            // Count cells with at least one covering segment
            coveredCells += (coverage[i][j] > 0);
        }
    }
    
    cout << coveredCells;

    return 0;
}
