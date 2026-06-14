#include <iostream>
#include <vector>
#include <random>
#include "RSQ_RMQ.hpp"

using namespace std;

vector<int> generate_array(int n) {
    vector<int> arr(n);
    for(int i = 0; i < n; ++i) arr[i] = rand() % 1000;
    return arr;
}

int main() {
    cout << "N,Structure,Operation,Avg_Operations\n";

    vector<int> N_values = {10, 50, 100, 200, 500, 1000, 2000, 5000};
    int query_count = 1000;
    int update_count = 100;

    for (int n : N_values) {
        auto arr = generate_array(n);

        auto measure_build = [&](const string& name, auto build_func) {
            reset_ticks();
            auto ds = build_func();
            cout << n << "," << name << ",Build," << op_count << "\n";
            return ds;
        };

        auto measure_query = [&](const string& name, auto& ds, auto query_func) {
            reset_ticks();
            for(int q = 0; q < query_count; ++q) {
                int l = rand() % n;
                int r = rand() % n;
                if(l > r) swap(l, r);
                query_func(ds, l, r);
            }
            cout << n << "," << name << ",Query," << op_count / query_count << "\n";
        };

        auto measure_update = [&](const string& name, auto& ds, auto update_func) {
            reset_ticks();
            for(int q = 0; q < update_count; ++q) {
                int idx = rand() % n;
                int val = rand() % 1000;
                update_func(ds, idx, val);
            }
            cout << n << "," << name << ",Update," << op_count / update_count << "\n";
        };

        auto ftree = measure_build("FenwickTree", [&](){ return FenwickTree(arr); });
        measure_query("FenwickTree", ftree, [](auto& ds, int l, int r){ ds.query(l, r); });
        measure_update("FenwickTree", ftree, [](auto& ds, int i, int v){ ds.update(i, v); });

        auto sptable = measure_build("SparseTable", [&](){ return SparseTable(arr); });
        measure_query("SparseTable", sptable, [](auto& ds, int l, int r){ ds.query(l, r); });
    }

    return 0;
}