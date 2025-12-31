//
// Created by pdwye on 12/16/2025.
//

#include "solution.h"

#include <cmath>
#include <cstring>
#include <iostream>
#include <fstream>
#include <regex>

#include "../../time.h"

#define INPUT_FILE "2025\\6\\input.txt"

static void part1();
static void part2();

void day6(const short part) {
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

static long long strToLongLong(std::string strNum, int length) {
	auto tensIndex = 0;
	auto number = 0;
	for (auto i = length - 1; i >= 0; i--) {
		if (strNum[i] >= '0' && strNum[i] <= '9') {
			const int tensTable[6] = {1, 10, 100, 1000, 10000, 100000};
			number += (strNum[i] - '0') * tensTable[tensIndex];
			tensIndex++;
		}
	}
	return number;
}

static long long addArray(const long long *values, int size) {
	long long total = 0;
	for (int i = 0; i < size; i++) {
		total += values[i];
	}
	return total;
}

static long long multArray(const long long *values, int size) {
	long long total = 1; //Assume the list is not empty
	for (int i = 0; i < size; i++) {
		total *= values[i];
	}
	return total;
}

static long long doColumnMath(const std::vector<std::string>& strNumbers, int index, int length, long long (*arrayOperation)(const long long *, int)) {
	long long numArray[length];
	memset(numArray, 0, length * sizeof(long long));
	for (int i = 0; i < length; i++) {
		auto tensIndex = 0;
		for (int j = strNumbers.size() - 2; j >= 0; j--) { // minus two to skip the mult/add row
			if (strNumbers[j][index + i] >= '0' && strNumbers[j][index + i] <= '9') {
				const int tensTable[6] = {1, 10, 100, 1000, 10000, 100000};
				numArray[i] += (strNumbers[j][index + i] - '0') * tensTable[tensIndex];
				tensIndex++;
			}
		}
	}
	return arrayOperation(numArray, length);
}

//7437295298 too, int overflow on stoi, changed to stoll
//6299564383938 :)
static void part1() {
	std::cout << "Starting 2025 Day 6 Part 1\n";
	START_TIME
	std::ifstream inputFile(INPUT_FILE);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file." << std::endl;
		END_TIME
		std::cout << "Error in " << GET_ELAPSED_TIME << "\n";
	}
	long long answer = 0;
	std::string line;
	std::vector<std::string> matches;
	while (std::getline(inputFile, line)) {
		matches.push_back(line);
	}
	std::vector<int> opIndexes;
	for (int i = 0; i < matches[4].length(); i++) {
		if (matches[4][i] != ' ') {
			opIndexes.push_back(i);
		}
	}
	opIndexes.push_back(matches[4].length() + 4); //Adding four ensures the final chars are included
	for (int i = 0; i < opIndexes.size() - 1; i++) {
		int stringLen = (opIndexes[i + 1] - opIndexes[i]) - 1;
		if (matches[4][opIndexes[i]] == '+') {
			answer += strToLongLong(matches[0].substr(opIndexes[i], stringLen), stringLen) +
				strToLongLong(matches[1].substr(opIndexes[i], stringLen), stringLen) +
				strToLongLong(matches[2].substr(opIndexes[i], stringLen), stringLen) +
				strToLongLong(matches[3].substr(opIndexes[i], stringLen), stringLen);
		} else {
			answer += strToLongLong(matches[0].substr(opIndexes[i], stringLen), stringLen) *
				strToLongLong(matches[1].substr(opIndexes[i], stringLen), stringLen) *
				strToLongLong(matches[2].substr(opIndexes[i], stringLen), stringLen) *
				strToLongLong(matches[3].substr(opIndexes[i], stringLen), stringLen);
		}
	}
	inputFile.close(); // Close the file after reading
	END_TIME
	std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
}

//11950004808442 :) First Try, fast as fuck boiiiii
static void part2() {
	std::cout << "Starting 2025 Day 6 Part 2\n";
	START_TIME
	std::ifstream inputFile(INPUT_FILE);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file." << std::endl;
		END_TIME
		std::cout << "Error in " << GET_ELAPSED_TIME << "\n";
	}
	long long answer = 0;
	std::string line;
	std::vector<std::string> matches;
	while (std::getline(inputFile, line)) {
		matches.push_back(line);
	}
	std::vector<int> opIndexes;
	for (int i = 0; i < matches[4].length(); i++) {
		if (matches[4][i] != ' ') {
			opIndexes.push_back(i);
		}
	}
	opIndexes.push_back(matches[4].length() + 4); //Adding four ensures the final chars are included
	for (int i = 0; i < opIndexes.size() - 1; i++) {
		int stringLen = (opIndexes[i + 1] - opIndexes[i]) - 1;
		if (matches[4][opIndexes[i]] == '+') {
			answer += doColumnMath(matches, opIndexes[i], stringLen, addArray);
		} else {
			answer += doColumnMath(matches, opIndexes[i], stringLen, multArray);
		}
	}

	inputFile.close(); // Close the file after reading
	END_TIME
	std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
}