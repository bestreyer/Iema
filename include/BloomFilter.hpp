#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <cstdint>
#include <iostream>
#include "RandomPrimaryGenerator.hpp"

class BloomFilter {
public:
    typedef std::pair<int, int> HashFunc;
protected:
    // Генератор случайных простых чисел
    RPG & rpg;
    // Массив битов
    std::unique_ptr<char[]> bits;
    // Максимальное кол-во элементов которое будет вставлено
    uint maxCountElements;
    // Количестов hash функций
    uint countHashFunc;
    // Количество бит
    uint countBits;
    // вероятность ложного срабатывания
    float error;

    std::unique_ptr<HashFunc[]> hashFuncs;
    /**
     * Определение оптимальных параметров для фильтра блума(количество бит и кол-во хэш функций)
     * @param maxCountElements Максимальное количестов элементов, которое будет хранится в фильтре
     * @param error            Желаемая вероятность ложного срабатывания
     */
    void setOptimalParams();
    void setHashFuncs();
    void initBits();

    void setBit(uint bit);
    bool checkBit(uint bit);
public:
    uint32_t hash(const std::string & s, uint16_t a, uint16_t p);
    BloomFilter(uint mce, float error, RPG & rpg);
    void add(const std::string & el);
    bool check(const std::string & el);

    void debugBits();
};
#endif
