#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include "metrics.hpp"

class FenwickTree {
    int n;
    std::vector<long long> tree;
    std::vector<int> arr_copy;

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1)) {
            tick();
            tree[idx] += delta;
        }
    }

    long long sum(int idx) {
        long long res = 0;
        for (; idx >= 0; idx = (idx & (idx + 1)) - 1) {
            tick();
            res += tree[idx];
        }
        return res;
    }

public:
    FenwickTree(const std::vector<int>& arr) {
        n = arr.size();
        tree.assign(n, 0);
        arr_copy = arr;
        for (int i = 0; i < n; ++i) {
            add(i, arr[i]);
        }
    }

    long long query(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void update(int idx, int val) {
        add(idx, val - arr_copy[idx]); 
        arr_copy[idx] = val;
    }
};

class SparseTable {
    int n;
    std::vector<std::vector<int>> st;
    std::vector<int> log_table;

public:
    SparseTable(const std::vector<int>& arr) {
        n = arr.size();
        int max_log = std::log2(n) + 1;
        st.assign(n, std::vector<int>(max_log));
        log_table.assign(n + 1, 0);

        for (int i = 2; i <= n; i++) {
            log_table[i] = log_table[i / 2] + 1;
        }

        for (int i = 0; i < n; i++) {
            tick();
            st[i][0] = arr[i];
        }

        for (int j = 1; j < max_log; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                tick();
                st[i][j] = std::min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r) {
        tick();
        int j = log_table[r - l + 1];
        return std::min(st[l][j], st[r - (1 << j) + 1][j]);
    }
};