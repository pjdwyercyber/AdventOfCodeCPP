//
// Created by pdwye on 12/14/2025.
//

#include "solution.h"

#include <cmath>
#include <iostream>
#include <fstream>
#include <regex>

#include "../../time.h"

#define INPUT_FILE "2025\\4\\input.txt"

static void part1();
static bool isSurrounded(const std::vector<std::string>&, int, int);
static void part2();

void day4(const short part) {
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

//1518 :)
static void part1() {
	std::cout << "Starting 2025 Day 4 Part 1\n";
	START_TIME
	std::ifstream inputFile(INPUT_FILE);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file." << std::endl;
		END_TIME
		std::cout << "Error in " << GET_ELAPSED_TIME << "\n";
	}
	auto answer = 0;
	std::string line;
	std::vector<std::string> paperMap;
	while (std::getline(inputFile, line)) {
		paperMap.push_back("." + line + "."); //Add the lines, surrounding them in extra array boundaries.
		//Fill in 2D vector vector.push_back(item)
		//Consider adding extra boundaries to endure no checking outside the array
		//also once the length of a line is known reserve the exact memory with vector.reserve() (? syntax may be wrong)
	}
	const auto lineLength = paperMap.at(0).length();
	std::string topBotBounds(lineLength, '.');
	paperMap.emplace_back(topBotBounds);
	paperMap.insert(paperMap.begin(), topBotBounds);
	for (int i = 1; i < paperMap.size() - 1; i++) {
		for (int j = 1; j < paperMap.at(0).length() - 1; j++) {
			if (paperMap.at(i).at(j) != '.' && !isSurrounded(paperMap, i, j)) {
				answer++;
			}
		}
	}
	inputFile.close(); // Close the file after reading
	END_TIME
	std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
}

static bool isSurrounded(const std::vector<std::string> &words, int i, int j) {
	int rolls = 0;
	if (words.at(i-1).at(j-1) != '.') {
		rolls++;
	}
	if (words.at(i-1).at(j) != '.') {
		rolls++;
	}
	if (words.at(i-1).at(j+1) != '.') {
		rolls++;
	}
	if (words.at(i).at(j-1) != '.') {
		rolls++;
	}
	if (words.at(i).at(j+1) != '.') {
		rolls++;
	}
	if (words.at(i+1).at(j-1) != '.') {
		rolls++;
	}
	if (words.at(i+1).at(j) != '.') {
		rolls++;
	}
	if (words.at(i+1).at(j+1) != '.') {
		rolls++;
	}
	return rolls >= 4;
}

//4250 Too low
//8665 :)
static void part2() {
	std::cout << "Starting 2025 Day 4 Part 2\n";
	START_TIME
	std::ifstream inputFile(INPUT_FILE);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file." << std::endl;
		END_TIME
		std::cout << "Error in " << GET_ELAPSED_TIME << "\n";
	}
	auto answer = 0;
	std::string line;
	std::vector<std::string> paperMap;
	while (std::getline(inputFile, line)) {
		paperMap.push_back("." + line + "."); //Add the lines, surrounding them in extra array boundaries.
	}
	const auto lineLength = paperMap.at(0).length();
	std::string topBotBounds(lineLength, '.');
	paperMap.emplace_back(topBotBounds);
	paperMap.insert(paperMap.begin(), topBotBounds);
	bool checkMap = true;
	while (checkMap) {
		checkMap = false;
		for (int i = 1; i < paperMap.size() - 1; i++) {
			for (int j = 1; j < paperMap.at(0).length() - 1; j++) {
				if (paperMap.at(i).at(j) != '.' && !isSurrounded(paperMap, i, j)) {
					paperMap.at(i).at(j) = '.';
					answer++;
					checkMap = true;
				}
			}
		}
	}
	// for (int i = 0; i < paperMap.size(); i++) {
	// 	std::cout << paperMap.at(i) << std::endl;
	// }

	inputFile.close(); // Close the file after reading
	END_TIME
	std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
}