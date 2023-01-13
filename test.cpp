#include <iostream>
#include <vector>

int main(void)
{
    std::vector<int> a;

    a.assign(31, 31);
    std::cout << a[31] << std::endl;
}