//
// Created by pdwye on 12/6/2025.
//

#include "2025.h"

#include <iostream>

#include "day.h"

void runAll();

//Runs the specific day and part of the 2025 AOC challenges
//If day is 0 all days are run
//If part is 0 both parts are run
void run2025(const short day, const short part) {
	if (day == 0) runAll();
	else switch (day) {
		case 1:
			day1(part);
			break;
		case 2:
			day2(part);
			break;
		case 3:
			day3(part);
			break;
		case 4:
			day4(part);
			break;
		case 5:
			day5(part);
			break;
		case 6:
			day6(part);
			break;
		case 7:
			day7(part);
			break;
		case 8:
			day8(part);
			break;
		case 9:
			day9(part);
			break;
		case 10:
			std::cout << "Uncomment Needed." << std::endl;
			//day10(part);
			break;
		case 11:
			std::cout << "Uncomment Needed." << std::endl;
			//day11(part);
			break;
		case 12:
			std::cout << "Uncomment Needed." << std::endl;
			//day12(part);
			break;
		default:
			break;
	}

}

void runAll() {
	day1();
	day2();
	day3();
	day4();
	day5();
	day6();
	day7();
	day8();
	day9();
	//day10();
	//day11();
	//day12();
}