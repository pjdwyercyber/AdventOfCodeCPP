#include <iostream>

#include "2025/2025.h"

int main(const int argc, char* argv[]) {
    const auto lang = "C++";
    std::cout << "Welcome to Advent of Code in " << lang << "!\n";

    short year = 0, day = 0, part = 0;
    if (argc > 1) {
        year = static_cast<short>(std::strtol(argv[1], nullptr, 10));
        if (argc > 2) {
            day = static_cast<short>(std::strtol(argv[2], nullptr, 10));
            if (argc > 3) {
                part = static_cast<short>(std::strtol(argv[3], nullptr, 10));
            }
        }
    }

    if (year > 2014 && year < 2026) {
        std::cout << "Year: " << year;
        if (day > 0 && day  < 26) {
            std::cout << ", Day: " << day;
            if (part > 0) {
                std::cout << ", Part: " << part;
            }
        }
        std::cout << std::endl;
        switch (year) {
            case 2024:
                //run2024(day, part);
                break;
            case 2025:
                run2025(day, part);
                break;
            default:
                break;
        }
    } else {
        //Run all years
        //run2022();
        //run2023();
        //run2024();
        run2025();
    }



    return 0;
}