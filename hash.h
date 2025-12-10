#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <string>
#include <cctype>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
    std::string s;
    s.reserve(k.size());
    for (unsigned char c : k) {
        s.push_back(std::tolower(c));
    }

    unsigned long long w[5] = {0, 0, 0, 0, 0};
    int n = static_cast<int>(s.size());
    for (int g = 0; g < 5; ++g) {
        int end = n - g * 6;
        if (end > 0) {
            int start = end - 6;
            if (start < 0) start = 0;
            unsigned long long value = 0ULL;
            for (int i = start; i < end; ++i) {
                value = value * 36ULL + letterDigitToNumber(s[i]);
            }
            w[4 - g] = value;
        }
    }

    for (int i = 0; i < 5; ++i) {
        std::cout << "w[" << i << "] = " << w[i] << "\n";
    }

    unsigned long long hashVal = 0ULL;
    for (int i = 0; i < 5; ++i) {
        hashVal += static_cast<unsigned long long>(rValues[i]) * w[i];
    }
    return static_cast<HASH_INDEX_T>(hashVal);


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
    if (letter >= 'A' && letter <= 'Z') {
        letter = static_cast<char>(letter - 'A' + 'a');
    }
    if (letter >= 'a' && letter <= 'z') {
        return static_cast<HASH_INDEX_T>(letter - 'a');
    }
    if (letter >= '0' && letter <= '9') {
        return static_cast<HASH_INDEX_T>(26 + (letter - '0'));
    }
    return 0;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif