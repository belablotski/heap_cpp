#include <algorithm>
#include <iostream>
#include <map>
#include <string>

// See also https://github.com/belablotski/heap/blob/main/anagram.py

std::ostream& operator<<(std::ostream& o, std::map<char, int> counter) {
    for (auto kv : counter) {
        o << kv.first << "\t" << kv.second << std::endl;
    }
    return o;
}

bool is_anagram(const std::string& s1, const std::string & s2) {
    auto frq = std::map<char, int>();
    if (s1.size() != s2.size()) {
        return false;
    }
    for (auto it = s1.begin(); it != s1.end(); ++it) {
        frq[std::tolower(*it)]++;
    }
    for (auto it = s2.begin(); it != s2.end(); ++it) {
        frq[std::tolower(*it)]--;
    }
    return std::all_of(frq.begin(), frq.end(), [](const auto& kv) { return kv.second == 0; });
}
