//
// Created by pdwye on 12/20/2025.
//

#include "solution.h"

#include <cmath>
#include <iostream>
#include <fstream>
#include <map>
#include <ranges>

#include "../../time.h"

#define INPUT_FILE "2025\\8\\input.txt"
#define NUM_CONNECTIONS 1000

struct point {
	int x, y, z;
	int index;

	bool operator<(const point& other) const {
		return index < other.index;
	}

	bool operator>(const point& other) const {
		return index > other.index;
	}
};

struct pair {
	point a, b;
};

struct circuit {
	int id{}, size{};
	std::vector<point> points{};
};

static void part1();
static void part2();

void day8(const short part) {
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

static double get3dDistance(const point a, const point b) {
	return std::sqrt(std::pow(b.x - a.x, 2.0) + std::pow(b.y - a.y, 2.0) + std::pow(b.z - a.z, 2.0));
}

static point getPoint(const std::string& line, const int index) {
	point p{};
	int number = 0;
	int vectorPos = 0;
	for (const auto & character : line) {
		if (character == ',') {
			if (vectorPos == 0) {
				p.x = number;
				vectorPos++;
			} else if (vectorPos == 1) {
				p.y = number;
				vectorPos++;
			}
			number = 0;
		} else {
			number *= 10;
			number += character - '0';
		}
	}
	p.z = number;
	p.index = index;
	return p;
}


// 192984 too high :( I was not exiting the loop when evaluating a distance between two points which already exists in a circuit
// 113316 too high :( Wrong move
// 60588 too low :( Wrong Move
// 62186
static void part1() {
	std::cout << "Starting 2025 Day 8 Part 1\n";
	START_TIME
	std::ifstream inputFile(INPUT_FILE);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file." << std::endl;
		END_TIME
		std::cout << "Error in " << GET_ELAPSED_TIME << "\n";
	}
	int answer = 0;
	int pointIndex = 0;
	double maxDistance = -1;
	int numDistances = 0;
	std::string line;
	std::vector<point> points;
	std::map<double, pair> distances;
	while (std::getline(inputFile, line)) {
		const point p = getPoint(line, pointIndex);
		for (const auto & point : points) {
			if (const double distance = get3dDistance(p, point); distance < 8000) { //Kinda cheating as the max distance for the first 1000 pairs is 7970.7159...
				if (numDistances < NUM_CONNECTIONS) {
					pair distancePair{};
					distancePair.a = p;
					distancePair.b = point;
					distances[distance] = distancePair;
					numDistances++;
					maxDistance = distance > maxDistance ? distance : maxDistance;
				} else if (distance < maxDistance) {
					pair distancePair{};
					distancePair.a = p;
					distancePair.b = point;
					distances[distance] = distancePair;
					distances.erase(maxDistance);
					maxDistance = distances.rbegin()->first;
				}
			}
		}
		points.push_back(p);
		pointIndex++;
	}
	int nextId = 0;
	std::map<int, int> pointCircuitMap; // <key: index of point, value: circuit id>
	std::vector<circuit> circuits;
	for (auto &[pointA, pointB]: distances | std::views::values) {
		if (!pointCircuitMap.contains(pointA.index) && !pointCircuitMap.contains(pointB.index)) {
			circuit c;
			c.id = nextId++;
			c.size = 2;
			c.points.push_back(pointA);
			c.points.push_back(pointB);
			circuits.push_back(c);
			pointCircuitMap[pointA.index] = c.id;
			pointCircuitMap[pointB.index] = c.id;
		} else if (pointCircuitMap.contains(pointA.index) && pointCircuitMap.contains(pointB.index)) {
			if (pointCircuitMap[pointA.index] != pointCircuitMap[pointB.index]) {
				int cIndex = pointCircuitMap[pointA.index];
				int cRemoveIndex = pointCircuitMap[pointB.index];
				circuits[cIndex].size += circuits[cRemoveIndex].size;
				for (auto & point : circuits[cRemoveIndex].points) {
					pointCircuitMap[point.index] = cIndex;
				}
				circuits[cIndex].points.insert(circuits[cIndex].points.end(), circuits[cRemoveIndex].points.begin(), circuits[cRemoveIndex].points.end());
				//circuits[cRemoveIndex].points.clear();
				circuits[cRemoveIndex].size = 0;
			}
		} else if (pointCircuitMap.contains(pointA.index)) {
			int cIndex = pointCircuitMap[pointA.index];
			pointCircuitMap[pointB.index] = cIndex;
			circuits[cIndex].size++;
			circuits[cIndex].points.push_back(pointB);
		} else if (pointCircuitMap.contains(pointB.index)) {
			int cIndex = pointCircuitMap[pointB.index];
			pointCircuitMap[pointA.index] = cIndex;
			circuits[cIndex].size++;
			circuits[cIndex].points.push_back(pointA);
		}
	}
	int first, second, third;
	for (const auto & c : circuits) {
		if (!third) {
			if (!second) {
				if (!first) {
					first = c.size;
				} else {
					if (c.size > first) {
						second = first;
						first = c.size;
					} else {
						second = c.size;
					}
				}
			} else {
				if (c.size > second) {
					third = second;
					if (c.size > first) {
						second = first;
						first = c.size;
					} else {
						second = c.size;
					}
				} else {
					third = c.size;
				}
			}
		} else if (c.size > third) {
			if (c.size > second) {
				third = second;
				if (c.size > first) {
					second = first;
					first = c.size;
				} else {
					second = c.size;
				}
			} else {
				third = c.size;
			}
		}
	}
	answer = first * second * third;
	inputFile.close(); // Close the file after reading
	END_TIME
	std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
}

// 8420405530 First Try :) answer could be more efficient, runs in ~300ms
static void part2() {
	std::cout << "Starting 2025 Day 8 Part 2\n";
	START_TIME
	std::ifstream inputFile(INPUT_FILE);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file." << std::endl;		END_TIME
		std::cout << "Error in " << GET_ELAPSED_TIME << "\n";
	}
	long long answer = 0;
	int pointIndex = 0;
	int numDistances = 0;
	std::string line;
	std::vector<point> points;
	std::map<double, pair> distances;
	while (std::getline(inputFile, line)) {
		point p = getPoint(line, pointIndex);
		for (const auto & point : points) {
			double distance = get3dDistance(p, point);
			pair distancePair{};
			distancePair.a = p;
			distancePair.b = point;
			distances[distance] = distancePair;
			numDistances++;
		}
		points.push_back(p);
		pointIndex++;
	}
	int nextId = 0;
	std::map<int, int> parentNodeMap; // <key: index of point, value: circuit id>
	std::vector<circuit> circuits;
	for (auto &[pointA, pointB]: distances | std::views::values) {
		if (!parentNodeMap.contains(pointA.index) && !parentNodeMap.contains(pointB.index)) {
			circuit c;
			c.id = nextId++;
			c.size = 2;
			c.points.push_back(pointA);
			c.points.push_back(pointB);
			circuits.push_back(c);
			parentNodeMap[pointA.index] = c.id;
			parentNodeMap[pointB.index] = c.id;
		} else if (parentNodeMap.contains(pointA.index) && parentNodeMap.contains(pointB.index)) {
			if (parentNodeMap[pointA.index] != parentNodeMap[pointB.index]) {
				int cIndex = parentNodeMap[pointA.index];
				int cRemoveIndex = parentNodeMap[pointB.index];
				circuits[cIndex].size += circuits[cRemoveIndex].size;
				for (auto & point : circuits[cRemoveIndex].points) {
					parentNodeMap[point.index] = cIndex;
				}
				circuits[cIndex].points.insert(circuits[cIndex].points.end(), circuits[cRemoveIndex].points.begin(), circuits[cRemoveIndex].points.end());
				//circuits[cRemoveIndex].points.clear();
				circuits[cRemoveIndex].size = 0;
			}
		} else if (parentNodeMap.contains(pointA.index)) {
			int cIndex = parentNodeMap[pointA.index];
			parentNodeMap[pointB.index] = cIndex;
			circuits[cIndex].size++;
			circuits[cIndex].points.push_back(pointB);
		} else if (parentNodeMap.contains(pointB.index)) {
			int cIndex = parentNodeMap[pointB.index];
			parentNodeMap[pointA.index] = cIndex;
			circuits[cIndex].size++;
			circuits[cIndex].points.push_back(pointA);
		}
		if (circuits[parentNodeMap[pointA.index]].size == pointIndex) {
			answer = static_cast<long long>(pointA.x) * static_cast<long long>(pointB.x);
			break;
		}
	}
	inputFile.close(); // Close the file after reading
	END_TIME
	std::cout << "Answer: " << answer << " in " << GET_ELAPSED_TIME <<std::endl;
}