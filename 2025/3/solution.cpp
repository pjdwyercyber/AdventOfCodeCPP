//
// Created by pdwye on 12/13/2025.
//

#include "solution.h"

#include <cmath>
#include <iostream>
#include <fstream>
#include <regex>

#include "../../time.h"

#define INPUT_FILE "2025\\3\\input.txt"

static void part1();
static void part2();

void day3(const short part) {
	switch (part) {
		case 0:
			part1();
			part2();
			break;
		case 1:
			part1();
			break;
		case 2:
			part2();
			break;
		default:
			break;
	}
}

static void part1() {
	std::cout << "Starting 2025 Day 3 Part 1\n";
	START_TIME
	std::ifstream inputFile(INPUT_FILE);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file." << std::endl;
		END_TIME
		std::cout << "Error in " << GET_ELAPSED_TIME << "\n";
	}
	int answer = 0;
	std::string line;
	while (std::getline(inputFile, line)) {
		int firstNum = 0, secondNum = 0;
		for (int i = 0; i < line.length(); i++) {
			if (line[i] > firstNum && i + 1 < line.length()) {
				firstNum = line[i];
				secondNum = 0;
			} else if (line[i] > secondNum) {
				secondNum = line[i];
			}
		}
		answer += (firstNum - 48) * 10 + secondNum - 48;
		//std::cout << std::to_string(firstNum - 48) << " " << std::to_string(secondNum - 48) << std::endl;
	}
	inputFile.close(); // Close the file after reading
	END_TIME
	std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
}

//12392761541722200 too high, forgot to clear the numbers beyond the most recently updated number, also power needed -1
//172167155440541 :)
static void part2() {
	std::cout << "Starting 2025 Day 3 Part 2\n";
	START_TIME
	std::ifstream inputFile(INPUT_FILE);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file." << std::endl;
		END_TIME
		std::cout << "Error in " << GET_ELAPSED_TIME << "\n";
	}
	const long long tensPlaceArray[12] = {
		100000000000LL,
		10000000000LL,
		1000000000LL,
		100000000LL,
		10000000LL,
		1000000LL,
		100000LL,
		10000LL,
		1000LL,
		100LL,
		10LL,
		1LL
	};
	long long answer = 0;
	std::string line;
	while (std::getline(inputFile, line)) {
		int numbers[12] = {0};
		int indexFirst = 0;
		for (int i = 0; i < line.length(); i++) {
			if (line.length() - i < 12) {
				indexFirst = 12 - (line.length() - i);
			}
			int checkIndex = indexFirst;
			while (checkIndex < 12) {
				if (line[i] > numbers[checkIndex]) {
					numbers[checkIndex] = line[i];
					while (checkIndex++ < 12) {
						numbers[checkIndex] = 0;
					}
					break;
				}
				checkIndex++;
			}
		}
		for (int i = 0; i < 12; i++) {
			//std::cout << numbers[i] - 48;
			answer += (numbers[i] - 48) * tensPlaceArray[i]; //std::pow(10, 12 - (i + 1));
		}
		//std::cout << std::endl;
	}
	inputFile.close(); // Close the file after reading
	END_TIME
	std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
}