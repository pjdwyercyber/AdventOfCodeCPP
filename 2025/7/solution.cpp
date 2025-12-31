//
// Created by pdwye on 12/17/2025.
//

#include "solution.h"

#include <atomic>
#include <cmath>
#include <iostream>
#include <fstream>
#include <queue>
#include <ranges>
#include <regex>

#include "../../time.h"

#define INPUT_FILE "2025\\7\\input.txt"

struct splitter {
	int index, row;

	bool operator<(const splitter& other) const {
		if (row == other.row) {
			return index < other.index;
		}
		return row < other.row;
	}

	bool operator>(const splitter& other) const {
		if (row == other.row) {
			return index > other.index;
		}
		return row > other.row;
	}

	bool operator==(const splitter& other) const {
		return row == other.row && index == other.index;
	}
};

std::vector<std::string> tachyonLines;
std::map<splitter, int> splitterCache;

static void part1();
static void part2();

void day7(const short part) {
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

static int followTachyonSplits(int particleIndex, int nextRow, const bool individual) {
	while (nextRow < tachyonLines.size() && tachyonLines[nextRow][particleIndex] == '.') {
		nextRow++;
	}
	const splitter currentKey = {particleIndex, nextRow};
	if (nextRow >= tachyonLines.size() || splitterCache.contains(currentKey)) {
		return 0;
	}
	nextRow++;
	const splitter leftKey = {particleIndex - 1, nextRow}, rightKey = {particleIndex + 1, nextRow};
	const int left = splitterCache.contains(leftKey) ? 0 : followTachyonSplits(particleIndex - 1, nextRow, individual);
	const int right = splitterCache.contains(rightKey) ? 0 : followTachyonSplits(particleIndex + 1, nextRow, individual);
	splitterCache[currentKey] = left + right + 1;
	return left + right + 1;
}

static long long followTachyonBeams(const int startIndex) {
	long long totalBeams = 0;
	std::vector<int> particlesQueue;
	std::map<int, long long> particlesMap;
	particlesQueue.push_back(startIndex);
	particlesMap[startIndex] = 1;
	//Do a bfs, add 1 for every beam moving between rows
	for (auto & line : tachyonLines) {
		const unsigned long long queueSize = particlesQueue.size();
		for (int i = 0; i < queueSize; i++) {
			if (line[particlesQueue.front()] == '^') {
				if (particlesMap.contains(particlesQueue.front() - 1)) {
					particlesMap[particlesQueue.front() - 1] += particlesMap[particlesQueue.front()];
				} else {
					particlesMap[particlesQueue.front() - 1] = particlesMap[particlesQueue.front()];
					particlesQueue.push_back(particlesQueue.front() - 1);
				}
				if (particlesMap.contains(particlesQueue.front() + 1)) {
					particlesMap[particlesQueue.front() + 1] += particlesMap[particlesQueue.front()];
				} else {
					particlesMap[particlesQueue.front() + 1] = particlesMap[particlesQueue.front()];
					particlesQueue.push_back(particlesQueue.front() + 1);
				}
				particlesMap.erase(particlesQueue.front());
				particlesQueue.erase(particlesQueue.begin());
			} else {
				particlesQueue.push_back(particlesQueue.front());
				particlesQueue.erase(particlesQueue.begin());
			}
		}
	}
	for (const auto &val: particlesMap | std::views::values) {
		totalBeams += val;
	}
	return totalBeams;
}

//7980501 too high, was caching wrong, so much double counting...
//1598 :)
static void part1() {
	std::cout << "Starting 2025 Day 7 Part 1\n";
	START_TIME
	std::ifstream inputFile(INPUT_FILE);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file." << std::endl;
		END_TIME
		std::cout << "Error in " << GET_ELAPSED_TIME << "\n";
	}
	int answer = 0;
	std::string line;
	int lineNum = 0;
	while (std::getline(inputFile, line)) {
		if (lineNum % 2 == 0) {
			tachyonLines.push_back(line);
		}
		lineNum++;
	}
	int startIndex = tachyonLines[0].find_first_of("S", tachyonLines[0].length()/2 - 1);
	answer += followTachyonSplits(startIndex, 1, false);
	inputFile.close(); // Close the file after reading
	END_TIME
	std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
}

//7980502 Too low, idk why I thought that might be right, fucking int overflow...
//4509723641302
static void part2() {
	std::cout << "Starting 2025 Day 7 Part 2\n";
	START_TIME
	std::ifstream inputFile(INPUT_FILE);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file." << std::endl;
		END_TIME
		std::cout << "Error in " << GET_ELAPSED_TIME << "\n";
	}
	long long answer = 0;
	std::string line;
	int lineNum = 0;
	while (std::getline(inputFile, line)) {
		if (lineNum % 2 == 0) {
			tachyonLines.push_back(line);
		}
		lineNum++;
	}
	const unsigned long long startIndex = tachyonLines[0].find_first_of('S', tachyonLines[0].length()/2 - 1);
	answer += followTachyonBeams(static_cast<int>(startIndex));
	inputFile.close(); // Close the file after reading
	END_TIME
	std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
}