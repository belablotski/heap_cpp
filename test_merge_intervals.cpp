#include <cassert>
#include <vector>
#include <iostream>
#include "merge_intervals.cpp"

void test_merge_intervals() {
    assert((merge_intervals({{1,2}}) == Intervals{{1,2}}));
    assert((merge_intervals({{1,2}, {2,3}}) == Intervals{{1,3}}));
    assert((merge_intervals({{1,2}, {2,3}, {1,3}}) == Intervals{{{1,3}}}));
    assert((merge_intervals({{1,2}, {2,3}, {1,3}, {4,5}, {4,6}, {5,7}}) == Intervals{{1,3}, {4,7}}));
    assert((merge_intervals({{1,2}, {2,3}, {1,3}, {4,5}, {4,6}, {5,7}, {2,6}}) == Intervals{{1,7}}));
    assert((merge_intervals({{1,2}, {2,3}, {1,3}, {4,5}, {4,6}, {5,7}, {2,6}, {0,8}, {1,9}}) == Intervals{{0,9}}));
    assert((merge_intervals({{1,2}, {2,3}, {1,3}, {4,5}, {4,6}, {5,7}, {2,6}, {0,8}, {1,9}, {13,15}, {10,16}, {11,14}}) == Intervals{{0,9},{10,16}}));
    assert((merge_intervals({{1,3},{2,6},{8,10},{15,18}}) == Intervals{{1,6},{8,10},{15,18}}));
    assert((merge_intervals({{1,4},{4,5}}) == Intervals{{1,5}}));
    assert((merge_intervals({{1,4},{0,4}}) == Intervals{{0,4}}));
    assert((merge_intervals({{1,4},{0,4},{2,10},{3,9},{4,11}}) == Intervals{{0,11}}));
}

int main() {
    std::cout << "Start testing..." << std::endl;
    test_merge_intervals();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}