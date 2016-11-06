#include "BloomFilter.hpp"
#include "RandomPrimaryGenerator.hpp"
#include "LRUCache.cpp"

#include <iostream>

void setting() {
    // Отключить синхронизация с stdio
    std::ios_base::sync_with_stdio(false);
}

struct Test {
    int value;
    int tag;

    Test() : value(0), tag(0) {

    }

    Test(int value, int tag):value(value), tag(tag) {

    }

    Test(Test & other) {
      this->swap(other);
    }

    Test(Test && other) {
        this->swap(other);
    }

    void swap(Test & other) {
      std::swap(this->value, other.value);
      std::swap(this->tag, other.tag);
    }

    Test& operator=(Test other) {
        swap(other);
        return *this;
    }

    void debug() {
      std::cout << value << " " << tag << std::endl;
    }

};

int main(int argc, char **argv) {

    /*RPG pr(argv[1]);
    BloomFilter filter(10, 0.3, pr);*/
    LRUCache<std::string, Test> cache(2);
    for (int i = 0; i < 100; i++) {
        auto test = Test(i, i + 20);
        cache.push(std::string("test") + std::to_string(i), test);
        cache.get(std::string("test0"));
    }

    cache.debug();
    //std::cout << test.value;

    /*filter.add("test");
    std::cout << filter.check("test") << " " << filter.check("test1");*/
}
