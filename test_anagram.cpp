#include <cassert>
#include <string>
#include "anagram.cpp"

int main() {
    std::cout << "Tests started..." << std::endl;

    // True cases
    assert(is_anagram("listen", "silent") == true);
    assert(is_anagram("anagram", "nagaram") == true);
    assert(is_anagram("abcbcc", "bcbacc") == true);
    assert(is_anagram("", "") == true);

    // False cases
    assert(is_anagram("hello", "bello") == false);
    assert(is_anagram("test", "ttew") == false);
    assert(is_anagram("a", "aa") == false);
    assert(is_anagram("abc", "def") == false);

    std::cout << "All tests passed! Have a nice day!" << std::endl;
    return 0;
}