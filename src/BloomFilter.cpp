#include "BloomFilter.hpp"
#include "RandomPrimaryGenerator.hpp"

#include <cmath>
#include <random>
#include <iostream>

uint32_t BloomFilter::hash(const std::string & s, uint16_t a, uint16_t p)
{
    uint32_t h = 0;
    for (const char & c : s) {
        h  = ((h*a) + (uint8_t)c) % p;
    }
    return h;
}

BloomFilter::BloomFilter(uint mce, float error, RPG & rpg)
    :rpg(rpg), maxCountElements(mce), error(error)
{
    setOptimalParams();
    setHashFuncs();
    initBits();

}

void BloomFilter::initBits()
{
    uint countChar = countBits / 8 + 1;
    bits.reset(new char[countChar]);
    for (int i = 0; i < countChar; i++) {
        bits[i] = 0;
    }
}

void BloomFilter::setBit(uint bit)
{
     bits[bit / 8] |= (1 << bit % 8);
}

bool BloomFilter::checkBit(uint bit)
{
    return (bits[bit / 8] & (1 << bit % 8)) == (1 << bit % 8);
}

void BloomFilter::setOptimalParams()
{
    countBits =  -(maxCountElements*log(error) / 0.48) + 1;
    countHashFunc = (countBits / maxCountElements ) * 0.6931 + 1;
}

void BloomFilter::setHashFuncs()
{
    auto & gen = rpg.getGenerator();
    hashFuncs.reset(new HashFunc[countHashFunc]);
    uint p = 0;
    for(int i = 0; i < countHashFunc; i++)
    {
        p = rpg.get();
        std::uniform_int_distribution<> dis(1, p);

        hashFuncs[i].first = dis(gen);
        hashFuncs[i].second = p;
    }
}

void BloomFilter::add(const std::string & el)
{
    uint bit = 0;
    for(int i = 0 ;i < countHashFunc; i++) {
        bit = hash(el, hashFuncs[i].first, hashFuncs[i].second) % countBits;
        setBit(bit);
    }
}

bool BloomFilter::check(const std::string & el)
{
    uint bit = 0;
    for(int i = 0 ;i < countHashFunc; i++) {
        bit = hash(el, hashFuncs[i].first, hashFuncs[i].second) % countBits;
        if (!checkBit(bit)) {
            return false;
        }
    }
    return true;
}

void BloomFilter::debugBits()
{
    for (int i = 0; i < countBits / 8 + 1; i++) {
            for (int j = 0 ; j < 8; j++) {
                std::cout << ((bits[i] & (1 << j)) == (1 << j));
            }
    }
}
