//
// Created by pdwye on 12/6/2025.
//

#include "solution.h"
#include <iostream>
#include <fstream>

#include "../../time.h"

#define INPUT_FILE "2025\\1\\input.txt"

static void part1();
static void part2();

void day1(const short part) {
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
	std::cout << "Starting 2025 Day 1 Part 1\n";
	START_TIME
	// Check if the file was successfully opened
	if (std::ifstream inputFile(INPUT_FILE); inputFile.is_open()) {
		int answer = 0;
		int pos = 50;
		std::string line;
		// Read the file line by line until the end of the file is reached
		while (std::getline(inputFile, line)) {
			if (line.at(0) == 'R') {
				pos += std::stoi(line.substr(1));
			} else {
				pos -= std::stoi(line.substr(1));
			}
			pos %= 100;
			if (pos == 0) answer++;
		}
		inputFile.close(); // Close the file after reading
		END_TIME
		std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
	} else {
		std::cerr << "Error: Unable to open file." << std::endl;
		END_TIME
		std::cout << "Error in " << GET_ELAPSED_TIME << "\n";
	}
}

//6917 Incorrect - Was not accounting for when pos is negative added we move left (added extra counts)
//6358 Money :)
static void part2() {
	std::cout << "Starting 2025 Day 1 Part 2\n";
	START_TIME
	if (std::ifstream inputFile(INPUT_FILE); inputFile.is_open()) {
		int answer = 0;
		int pos = 50;
		int value = 0;
		std::string line;
		while (std::getline(inputFile, line)) {
			value = std::stoi(line.substr(1));
			answer += value / 100;
			value %= 100;
			if (line.at(0) == 'R') {
				pos += value;
			} else {
				if (pos && value > pos) pos += 100 + (100 - value);
				else if (!pos) pos += 100 - value;
				else pos -= value;
			}
			if (pos == 0) {
				answer++;
			} else {
				answer += pos / 100;
				pos %= 100;
			}
		}
		inputFile.close(); // Close the file after reading
		END_TIME
		std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
	} else {
		std::cerr << "Error: Unable to open file." << std::endl;
		END_TIME
		std::cout << "Error in " << GET_ELAPSED_TIME << "\n";
	}
}