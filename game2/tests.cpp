#include "environment.hpp"
#include <string>

// All tests return true if success, false if failure

// Test that angles are measured properly:
bool testAngleMeasure() {
	float north = Environment::GetAngle(0, 0, 0, 1);
	float east = Environment::GetAngle(0, 0, 1, 0);
	float south = Environment::GetAngle(0, 0, 0, -1);
	float west = Environment::GetAngle(0, 0, -1, 0);
	std::cout << "N: " + std::to_string(north) + "\n";
	std::cout << "E: " + std::to_string(east) + "\n";
	std::cout << "S: " + std::to_string(south) + "\n";
	std::cout << "W: " + std::to_string(west) + "\n";
	if (north != 0 | east != 90 | south != 180 | west != 270) {
		std::cout << "ANGLE TEST FAILED" << std::endl;
		return false;
	}
	else {
		std::cout << "angle test success" << std::endl;
		return true;
	}
}