#include "tests.hpp"

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
	if (north != 0 || east != 90 || south != 180 || west != 270) {
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
/*
// Test that the Bresenham algorithm gives the correct points
bool testBresenham() {
    // Draw a line pointing West and see if it works:
    BresenhamPointIterator west = BresenhamPointIterator(&Point(0, 0), &Point(-3, 0));
    int eastResults[4][2];
    for (Point curPixel = west.getNext(), int i=4; i<4; curPixel = west.getNext(), ++i) {
        eastResults[i][0] = curPixel.x;
        eastResults[i][1] = curPixel.y;
        std::cout << "West " << i << ": (" << curPixel.x << ", " << curPixel.y << ")\n";
    }
    std::cout << std::endl;
}
*/

// Test that line of sight works:
// (Ideally we would have two tests for each octant: a "should pass" and "shouldn't pass".
// But I'm not manually writing 16 test cases.
bool testLineOfSight() {
    Environment env = Environment();
    env.addWall(100, 100, 100, 200);
    std::cout << "Created wall from (100, 100) to (100, 200)\n";
    bool testsPassed = true;
    // Unblocked line in octant 0: Should pass
    if (!env.LineOfSightExists(0, 0, 1, 0)) {
        std::cout << "No line of sight from (0, 0) to (0, 1). This is wrong\n";
        testsPassed = false;
    }
    else {
        std::cout << "Line of sight correctly exists from (0, 0) to (0, 1)\n";
    }
    // Blocked line in octant 3: Shouldn't pass:
    if (env.LineOfSightExists(101, 150, 51, 125)) {
        std::cout << "Line of sight incorrectly exists from (101, 150) to (51, 125). This is wrong\n";
        testsPassed = false;
    }
    else {
        std::cout << "Line of sight correctly blocked from (101, 150) to (51, 125).\n";
    }
    if (testsPassed) {
        std::cout << "Line of sight test passed" << std::endl;
    }
    else {
        std::cout << "LINE OF SIGHT TEST FAILED!!!" << std::endl;
    }
    return testsPassed;
}

// Test that collision detection works:
bool testCollision() {
    Environment env = Environment();

    env.addWall(100, 100, 200, 100);
    env.addWall(100, 100, 100, 200);
    std::cout << "Created wall from (100, 100) to (100, 200)\n";
    std::cout << "Created wall from (100, 100) to (200, 100)\n";
    bool testsPassed = true;

    // Blocked horizontal movement:
    if (env.MoveAllowed(101, 150, 99, 150)) {
        testsPassed = false;
        std::cout << "Movement from (101, 150) to (99, 150) was incorrectly allowed\n";
    }
    // Allowed horizontal movement:
    if (!env.MoveAllowed(101, 150, 103, 150)) {
        testsPassed = false;
        std::cout << "Movement from (101, 150) to (103, 150) was incorrectly blocked\n";
    }
    // Blocked vertical movement:
    if (env.MoveAllowed(150, 101, 150, 99)) {
        testsPassed = false;
        std::cout << "Movement from (150, 101) to (150, 99) was incorrectly allowed\n";
    }
    if (testsPassed) {
        std::cout << "Collision tests passed" << std::endl;
    }
    else {
        std::cout << "Collision TESTS FAILED!!!" << std::endl;
    }

    return testsPassed;
}