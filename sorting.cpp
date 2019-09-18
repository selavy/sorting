#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>

template <
    class It,
    class Cmp = std::less<>
>
void unguarded_insertion_sort(It begin, It end, Cmp cmp = Cmp{}) noexcept {
    // pre : *(begin - 1) <= all elements in [begin, end)
    // post: [begin - 1, end) sorted
    for (; begin != end; ++begin) {
        It cur = begin, prev = begin - 1;
        while (cmp(*cur, *prev)) {
            std::iter_swap(cur--, prev--);
        }
    }
}

template <class Cont>
void print(const Cont& vs) {
    for (auto v : vs)
        std::cout << v << " ";
    std::cout << "\n";
}

int main(int argc, char** argv)
{
    constexpr int N = 100;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-10*N, 10*N);
    std::vector<int> vs;
    vs.reserve(N);
    for (int i = 0; i < N; ++i)
        vs.push_back(dis(gen));
    assert(static_cast<int>(vs.size()) == N);
    assert(!std::is_sorted(vs.begin(), vs.end()));

    std::make_heap(vs.begin(), vs.end(), std::greater<>{});
    unguarded_insertion_sort(vs.begin() + 2, vs.end());
    assert(std::is_sorted(vs.begin(), vs.end()));

    return 0;
}
