//
// Created by pdwye on 12/XX/2025.
//

#include "solution.h"

#include <cmath>
#include <iostream>
#include <fstream>
#include <regex>

#include "../../time.h"

#define INPUT_FILE "2025\\5\\input.txt"

static void part1();
static void part2();

void day5(const short part) {
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
	std::cout << "Starting 2025 Day 5 Part 1\n";
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

	}
	inputFile.close(); // Close the file after reading
	END_TIME
	std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
}

static void part2() {
	std::cout << "Starting 2025 Day 5 Part 2\n";
	START_TIME
	std::ifstream inputFile(INPUT_FILE);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file." << std::endl;
		END_TIME
		std::cout << "Error in " << GET_ELAPSED_TIME << "\n";
	}
	long long answer = 0;
	std::string line;
	while (std::getline(inputFile, line)) {

	}
	inputFile.close(); // Close the file after reading
	END_TIME
	std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
}