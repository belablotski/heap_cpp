/*
Given a collection of intervals, merge all overlapping intervals.

Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Intervals [1,3] and [2,6] overlap, merge them into [1,6].

Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.

Example 3:
Input: intervals = [[1,4],[0,4]]
Output: [[0,4]]

See also https://github.com/belablotski/heap/blob/main/merge_intervals.py
*/

#include <algorithm>
#include <iostream>
#include <vector>

using Interval = std::pair<int, int>;
using Intervals = std::vector<Interval>;

std::ostream& operator<<(std::ostream& o, Intervals intervals) {
    for (auto interval : intervals) {
        o << "[" << interval.first << ", " << interval.second << "] ";
    }
    return o;
}

Intervals merge_intervals(const Intervals& intervals) {
    auto merged = Intervals();
    auto sorted_intervals = intervals;
    
    std::sort(sorted_intervals.begin(), sorted_intervals.end(), [](const auto& p1, const auto&p2) {
        return p1.first < p2.first;
    });

    auto it = sorted_intervals.begin();
    
    if (it != sorted_intervals.end()) {
        auto intv = *it;
        for (++it; it != sorted_intervals.end(); ++it) {
            if (it->first >= intv.first && it->first <= intv.second) {
                if (it->second > intv.second) {
                    intv.second = it->second;
                }
            }
            else {
                merged.push_back(intv);
                intv = *it;
            }
        }
        merged.push_back(intv);
    }

    return merged;
}

int main_() {
    Intervals intervals {};
    std::cout << "Merged " << intervals << "in " << merge_intervals(intervals) << std::endl;

    intervals = Intervals {{1, 2}};
    std::cout << "Merged " << intervals << "in " << merge_intervals(intervals) << std::endl;

    intervals = Intervals {{1, 4}, {3, 5}};
    std::cout << "Merged " << intervals << "in " << merge_intervals(intervals) << std::endl;
    
    intervals = Intervals {{1, 2}, {4, 5}};
    std::cout << "Merged " << intervals << "in " << merge_intervals(intervals) << std::endl;
    
    return 0;
}