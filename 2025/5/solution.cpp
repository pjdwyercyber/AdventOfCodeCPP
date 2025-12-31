//
// Created by pdwye on 12/15/2025.
//

#include "solution.h"

#include <cmath>
#include <iostream>
#include <fstream>
#include <regex>

#include <format>
#include <bitset>
#include <vector>

#include "../../time.h"

#define INPUT_FILE "2025\\5\\input.txt"

struct idRange {
	long long start, end;
};

static void insertRange(std::vector<idRange>&, idRange);
static bool existsInRanges(const std::vector<idRange>&, long long);
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

static void insertRange(std::vector<idRange> &rangeList, idRange newRange) {
	int prevIndex = -1;
	int nextIndex = rangeList.size() / 2;
	int startRange = 0;
	int endRange = rangeList.size() - 1;
	if (rangeList.empty()) {
		rangeList.push_back(newRange);
		return;
	}
	while (nextIndex != prevIndex) { //&& nextIndex < rangeList.size()) {
		prevIndex = nextIndex;
		if (rangeList[nextIndex].start > newRange.end + 1) { //new range is smaller than current index
			endRange = nextIndex - 1;
			nextIndex = (endRange - startRange) / 2 + startRange;
		} else if (rangeList[nextIndex].end < newRange.start - 1) { //new range is larger than current index
			startRange = nextIndex + 1;
			nextIndex = (endRange - startRange) / 2 + startRange;
		} else { //There is some range overlap
			//std::cout << rangeList[nextIndex].start << "-" << rangeList[nextIndex].end << "\n" << newRange.start << "-" << newRange.end << std::endl;
			newRange.start = rangeList[nextIndex].start <= newRange.start ? rangeList[nextIndex].start : newRange.start;
			newRange.end = rangeList[nextIndex].end >= newRange.end ? rangeList[nextIndex].end : newRange.end;
			rangeList.erase(rangeList.begin() + nextIndex);
			insertRange(rangeList, newRange);
			//std::cout << rangeList[nextIndex].start << "-" << rangeList[nextIndex].end << "\n" << std::endl;
			return;
		}
	}
	rangeList.insert(rangeList.begin() + nextIndex, newRange);
}

static bool existsInRanges(const std::vector<idRange> &rangeList, const long long input) {
	int prevIndex = -1;
	int nextIndex = rangeList.size() / 2;
	int startRange = 0;
	int endRange = rangeList.size() - 1;
	while (nextIndex != prevIndex) {
		prevIndex = nextIndex;
		if (rangeList[nextIndex].start > input) {
			endRange = nextIndex - 1;
			nextIndex = (endRange - startRange) / 2 + startRange;
		} else if (rangeList[nextIndex].end < input) {
			startRange = nextIndex + 1;
			nextIndex = (endRange - startRange) / 2 + startRange;
		} else {
			return true;
		}
	}
	return false;

}

//848
//Gives 1000 when part 1 and 2 are run simultaneously.
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
	std::getline(inputFile, line);
	const std::regex rangePattern(R"((\d+)-(\d+))");
	std::vector<idRange> rangeList;
	while (!line.empty()) {
		std::smatch match;
		std::regex_search(line, match, rangePattern);
		idRange newRange = {std::stoll(match[1]), std::stoll(match[2])};
		insertRange(rangeList, newRange);
		std::getline(inputFile, line);
	}
	//Skip the empty line
	while (std::getline(inputFile, line)) {
		long long input = std::stoll(line);
		if (existsInRanges(rangeList, input)) {
			answer++;
		}
	}
	inputFile.close(); // Close the file after reading
	END_TIME
	std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
}

//334714395325710 :) First Try
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
	std::getline(inputFile, line);
	const std::regex rangePattern(R"((\d+)-(\d+))");
	std::vector<idRange> rangeList;
	while (!line.empty()) {
		std::smatch match;
		std::regex_search(line, match, rangePattern);
		idRange newRange = {std::stoll(match[1]), std::stoll(match[2])};
		insertRange(rangeList, newRange);
		std::getline(inputFile, line);
	}
	for (auto &[start, end] : rangeList) {
		answer += (end - start) + 1;
	}
	inputFile.close(); // Close the file after reading
	END_TIME
	std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
}