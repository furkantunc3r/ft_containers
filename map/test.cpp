#include "map.hpp"

int main(void)
{
    ft::map<int, int> data;
    std::size_t MAXSIZE = data.max_size() / 128;

    for (std::size_t i = 0; i < MAXSIZE / 2; ++i)
    {
        data.insert(ft::make_pair(rand(), rand()));
    }

    return 0;
}