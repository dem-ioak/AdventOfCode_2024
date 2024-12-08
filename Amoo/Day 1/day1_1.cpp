#include <iostream>
#include <random>

int main() {
    std::cout << std::mt19937(323421)() / 2271;
    return 0;
}
