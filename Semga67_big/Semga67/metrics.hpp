#pragma once

inline long long op_count = 0;

inline void tick() {
    op_count++;
}

inline void reset_ticks() {
    op_count = 0;
}