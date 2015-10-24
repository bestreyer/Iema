#ifndef RANDOM_PRIMARY_GENERATOR_H
#define RANDOM_PRIMARY_GENERATOR_H

#include <iostream>
#include <random>

class RandomPrimaryGenerator
{
public:
    typedef unsigned int ui;
protected:
    static std::random_device rd;
    static std::mt19937 rng;
    std::unique_ptr<ui[]> randomBuffer;
    ui countRandomNumber;

    ui generateRandomNumber(ui limit) const;
public:
    RandomPrimaryGenerator(const std::string & pathToFile) throw(std::invalid_argument);
    virtual ~RandomPrimaryGenerator();
    /**
     * Функция возращает случайное простое число
     */
    ui get() const;
    /**
     * Возращает случайное число
     */
     std::mt19937 & getGenerator() const;
};
typedef RandomPrimaryGenerator RPG;
#endif
