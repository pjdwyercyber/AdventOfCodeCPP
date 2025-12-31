//
// Created by pdwye on 12/6/2025.
//

#ifndef ADVENTOFCODE_TIME_H
#define ADVENTOFCODE_TIME_H

#include <chrono>

#define START_TIME const auto start = std::chrono::high_resolution_clock::now();
#define END_TIME const auto end = std::chrono::high_resolution_clock::now();
#define GET_ELAPSED_TIME (end - start) // gets ns time //std::chrono::duration<double>(end - start).count() //get ms double

#endif //ADVENTOFCODE_TIME_H