#include "BloomFilter.hpp"
#include "RandomPrimaryGenerator.hpp"
#include <iostream>

void setting() {
    // Отключить синхронизация с stdio
    std::ios_base::sync_with_stdio(false);
}

int main(int argc, char **argv) {
    RPG pr(argv[1]);
    BloomFilter filter(10, 0.3, pr);

    filter.add("test");
    std::cout << filter.check("test") << " " << filter.check("test1");
}
