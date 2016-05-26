#ifndef POINT_HPP
#define POINT_HPP


class Point
{
public:
    Point(int x, int y);
    static Point switchToOctZero(Point * p, int cur_octant);
    int x;
    int y;
};

/*
 * An implementation of Bresenham's line drawing algorithm
 * as an iterator.
 * But not as a "proper C++ iterator" cause it looks like
 * it'd take a while to learn that...
 */
class BresenhamPointIterator {
public:
    BresenhamPointIterator(Point* start, Point* end);
    static int get_octant(int delta_x, int delta_y);
    Point getNext();
private:
    Point start;
    Point end;
    int delta_x;
    int delta_y;
    int cur_dif;
    int cur_x;
    int cur_y;
    int octant;
   /*
    *  Octants: (graphic copied from Wikipedia)
    *   \2|1/
    *   3\|/0
    *  ---+---
    *   4/|\7
    *   /5|6\
    */
};

#endif // POINT_HPP