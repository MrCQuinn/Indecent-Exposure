#include "environment.hpp"
#include <string>
#include "point.hpp"

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
		std::cout << "ANGLE TEST FAILED!!!" << std::endl;
		return false;
	}
	else {
		std::cout << "angle test success" << std::endl;
		return true;
	}
}

// Test that octants are determined correctly:
bool testOctantDetection() {
    int octResults[8];
    octResults[0] = BresenhamPointIterator::get_octant(2, 1);
    octResults[1] = BresenhamPointIterator::get_octant(1, 2);
    octResults[2] = BresenhamPointIterator::get_octant(-1, 2);
    octResults[3] = BresenhamPointIterator::get_octant(-2, 1);
    octResults[4] = BresenhamPointIterator::get_octant(-2, -1);
    octResults[5] = BresenhamPointIterator::get_octant(-1, -2);
    octResults[6] = BresenhamPointIterator::get_octant(1, -2);
    octResults[7] = BresenhamPointIterator::get_octant(2, -1);
    bool isgood = true;
    for (int i = 0; i < 8; ++i) {
        std::cout << "octant " << i << " was: " << octResults[i] << "\n";
        if (octResults[i] != i) {
            isgood = false;
        }
    }
    if (isgood) {
        std::cout << "octants were okay" << std::endl;
    }
    else {
        std::cout << "OCTANT TEST FAILED!!!" << std::endl;
    }
    return isgood;
}

