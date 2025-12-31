//
// Created by pdwye on 12/6/2025.
//

#include "solution.h"

#include <cmath>
#include <iostream>
#include <fstream>
#include <regex>

#include "../../time.h"

#define INPUT_FILE "2025\\2\\input.txt"
#define RANGE_PATTERN R"((\d+)-(\d+))"

static void part1();
static void part2();

void day2(const short part) {
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

//748 Too low - I was doing anwer++ instead of answer += value
//30599400849 :)
static void part1() {
	std::cout << "Starting 2025 Day 2 Part 1\n";
	START_TIME
	std::ifstream inputFile(INPUT_FILE);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file." << std::endl;
		END_TIME
		std::cout << "Error in " << GET_ELAPSED_TIME << "\n";
	}
	unsigned long long answer = 0;
	std::regex rangePattern(RANGE_PATTERN);
	if (std::string line; std::getline(inputFile, line)) {
		// input is a single line for day 2
		for (std::sregex_iterator iter(line.begin(), line.end(), rangePattern), end; iter != end; ++iter) {
			const std::smatch &match = *iter;
			unsigned long long firstNum = std::stoull(match[1]), secondNum = std::stoull(match[2]);
			int firstLen = static_cast<int>(std::log10(firstNum)) + 1;
			int secondLen = static_cast<int>(std::log10(secondNum)) + 1;
			if (firstLen != secondLen || firstLen % 2 == 0) {
				//If they are the same value they need to be even, odd numbers cant be patterned in this part
				unsigned long long nextVal = 0;
				unsigned long long tensMult = 0;
				auto maxVal = static_cast<unsigned long long>(std::pow(10, firstLen));
				if (firstLen % 2 == 0) {
					long startNum = 0, endNum = 0;
					tensMult = static_cast<unsigned long long>(std::pow(10, firstLen / 2));
					startNum = firstNum / tensMult;
					endNum = firstNum % tensMult;
					if (startNum >= endNum) {
						nextVal = (startNum * tensMult) + startNum;
					} else {
						nextVal = ((startNum + 1) * tensMult) + startNum + 1;
					}
				} else {
					//Start at the first even length pattern (11, 1010, 100100, etc)
					tensMult = static_cast<unsigned long long>(std::pow(10, (firstLen + 1) / 2));
					nextVal = maxVal + static_cast<unsigned long long>(std::pow(10, (firstLen - 1) / 2));
					maxVal *= 10;
				}
				unsigned long long step = (1 * tensMult) + 1;
				while (nextVal <= secondNum && nextVal < maxVal) {
					answer += nextVal;
					nextVal += step;
				}
			}
		}
	}
	inputFile.close(); // Close the file after reading
	END_TIME
	std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
}

//46270373595 First Try :), but I doubt this is the most efficient way
static void part2() {
	std::cout << "Starting 2025 Day 2 Part 2\n";
	START_TIME
	std::ifstream inputFile(INPUT_FILE);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file." << std::endl;
		END_TIME
		std::cout << "Error in " << GET_ELAPSED_TIME << "\n";
	}
	std::string line;
	if (!std::getline(inputFile, line)) {
		std::cout << "Unable to read line." << std::endl;
	}
	unsigned long long answer = 0;
	std::regex rangePattern(RANGE_PATTERN);
	for (std::sregex_iterator iter(line.begin(), line.end(), rangePattern), end; iter != end; ++iter) {
		const std::smatch &match = *iter;
		unsigned long long currentNum = std::stoull(match[1]), secondNum = std::stoull(match[2]);
		std::regex numberPattern(R"(^(\d+)\1+$)");
		while (currentNum <= secondNum) {
			if (std::regex_search(std::to_string(currentNum), numberPattern)) {
				answer += currentNum;
			}
			currentNum++;
		}
	}
	inputFile.close(); // Close the file after reading
	END_TIME
	std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
}