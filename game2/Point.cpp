#include "Point.hpp"

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point Point::switchToOctZero(Point *p, int cur_octant) {
    switch (cur_octant) {
        case 0: return Point(p->x, p->y);
        case 1: return Point(p->y, p->x);
        case 2: return Point(p->y, -p->x);
        case 3: return Point(-p->x, p->y);
        case 4: return Point(-p->x, -p->y);
        case 5: return Point(-p->y, -p->x);
        case 6: return Point(-p->y, p->x);
        case 7: return Point(p->x, -p->y);
    }
}

BresenhamPointIterator::BresenhamPointIterator(Point* start, Point* end)
{
    this->octant = BresenhamPointIterator::get_octant(end->x - start->x, end->y - start->y);
    this->start = Point::switchToOctZero(start, this->octant);
    this->end = Point::switchToOctZero(end, this->octant);
    this->cur_x = this->start.x;
    this->cur_y = this->start.y;
    this->delta_x = this->end.x - this->start.x;
    this->delta_y = this->end.y - this->start.y;
    this->cur_dif = this->delta_y - this->delta_x;
}


/*
 *  Checks which octant a line is in
 *  Octants: (graphic copied from Wikipedia)
 *   \2|1/
 *   3\|/0
 *  ---+---
 *   4/|\7
 *   /5|6\
 */
int BresenhamPointIterator::get_octant(int delta_x, int delta_y)
{

    if (delta_x >= 0) {
        // We're in right half
        if (delta_y >= 0) {
            // We're in the top right quadrant
            if (delta_x >= delta_y) {
                return 0;
            }
            return 1;

        } else {
            // We're in bottom right quadrant; y is negative
            if (delta_x >= -delta_y) {
                return 7;
            }
            return 6;
        }

    } else {
        // We're in left half; x is negative
        if (delta_y >= 0) {
            // We're in the top left quadrant
            if (-delta_x >= delta_y) {
                return 3;
            }
            return 2;

        }
        else {
            // We're in bottom left quadrant; y is negative
            if (delta_x <= delta_y) {
                return 4;
            }
            return 5;
        }
    }
}

// Get the next point to be drawn
Point BresenhamPointIterator::getNext()
{
    int old_x = cur_x;
    int old_y = cur_y;

    if (cur_dif >= 0) {
        ++cur_y;
        cur_dif -= delta_x;
    }
    cur_dif += delta_y;
    ++cur_x;

    // We have to transform the values back to the original octant:
    switch (octant) {
        case 0: return Point(old_x, old_y);
        case 1: return Point(old_y, old_x);
        case 2: return Point(-old_y, old_x);
        case 3: return Point(-old_x, old_y);
        case 4: return Point(-old_x, -old_y);
        case 5: return Point(-old_y, -old_x);
        case 6: return Point(old_y, -old_x);
        case 7: return Point(old_x, -old_y);
    }
}
