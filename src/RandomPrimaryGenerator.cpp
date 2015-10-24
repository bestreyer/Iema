#include "RandomPrimaryGenerator.hpp"
#include <fstream>
#include <iostream>
#include <random>

using namespace std;

std::random_device   RPG::rd;
std::mt19937         RPG::rng(RPG::rd());

RPG::RandomPrimaryGenerator(const string & pathToFile) throw(invalid_argument)
{
    ifstream file(pathToFile, ios::in|ios::binary|ios::ate);
    if (!file.is_open()) {
        throw invalid_argument("File [" + pathToFile + "] not found");
    }

    auto end = file.tellg();
    file.seekg(0, ios::beg);
    auto begin = file.tellg();
    this->countRandomNumber = (end - begin) / sizeof(unsigned int);
    this->randomBuffer.reset(new unsigned int[this->countRandomNumber]);

    file.read(reinterpret_cast<char *>(this->randomBuffer.get()), end - begin);
    file.close();
}

RPG::~RandomPrimaryGenerator() {

}
RPG::ui RPG::get() const
{
    return randomBuffer[generateRandomNumber(countRandomNumber - 1)];
}
RPG::ui RPG::generateRandomNumber(RPG::ui limit) const
{
    uniform_int_distribution<> dis(0, limit);
    return dis(rng);
}

mt19937 & RPG::getGenerator() const {
    return RPG::rng;
}
