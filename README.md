# DL Problem Set - Competitive Programming Solutions

Solutions to challenging algorithmic problems from **Vietnam National Informatics Training Camp 2022**, demonstrating advanced data structures and optimization techniques.

How to run (example):
```bash
g++ -std=c++17 -O2 attack.cpp -o attack && ./attack < input.txt
```

## 🎯 Problem Overview

| Problem     | Algorithms & Data Structures              | Complexity |
|-------------|-------------------------------------------|------------|
| **ATTACK**  | Dynamic Programming, Bitmask, Greedy      | O(L·n)     | 
| **PHOTO**   | 2D Difference Array, 2D Prefix Sum.       | O(n²+m)    |
| **SHLGOOD** | Fenwick Tree, DSU, Coordinate Compression | O(n log n) |



## 📋 Problem Descriptions

### ATTACK - Optimal Cannon Positioning

Position `n` cannons (radius `R`) to cover `L` zones with minimum repositioning cost.

**Key Techniques:**
- Bitmask enumeration for small inputs
- Dynamic Programming for general case
- Greedy formula for special case: L = n×(2R-1)

**Files:** `attack.cpp` • Full problem statement in code header

--------------

### PHOTO - Satellite Coverage Optimization

Cover `m` objects on n×n grid using minimum cells with square regions along diagonal.

**Key Techniques:**
- 2D Difference Array for O(1) range updates
- 2D Prefix Sum for efficient computation

**Files:** `photo.cpp` • Full problem statement in code header

--------------

### SHLGOOD - Good Left-Shift Sequences

Count contiguous subsequences where rotation makes first half dominate second half.

**Key Techniques:**
- Fenwick Tree for O(log n) range operations
- DSU with path compression for interval merging
- Coordinate compression for large value ranges

**Files:** `shlgood.cpp` • Full problem statement in code header

--------------

## 📊 Complexity Analysis

### ATTACK
- **Brute Force (L ≤ 20):** O(2^L · L)
- **Greedy (Special):** O(n)
- **DP (General):** O(L · n)
- **Space:** O(L)

### PHOTO
- **Time:** O(n² + m)
- **Space:** O(n²)

### SHLGOOD
- **Time:** O(n log n)
- **Space:** O(n)

---

## 📝 Notes

- Complete problem statements with examples are in each `.cpp` file header
- All solutions tested and verified against original test cases
- **Code has been AI normalized:**
  - Added full problem statements to file headers
  - Renamed variables/functions from Vietnamese to English
  - Added contextual comments for clarity

- Some files include detailed English comments and complexity analysis


---

## 📜 License

Educational purposes - Free to use with attribution

---

*Last Updated: October 2025*
