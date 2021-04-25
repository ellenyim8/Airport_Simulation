#ifndef PLANE_H
#define PLANE_H
#include <iostream>
using namespace std;
#include <iomanip>
#include <math.h>   // using STL Library: for rand() and RAND_MAX

/**************************************************
 * bool plane_coming_to_runway(int)
 *
 * checks to see if there's a plane coming into the
 * runway
 *      Parameters: int avg (IN: average interval)
 *      Returns: bool
***************************************************/
bool plane_coming_to_runway(int avg);

/**************************************************
 * bool plane_crashed(int, int, int)
 *
 * checks to see if the plane has crashed.
 *      Parameters: int avg (IN: average interval)
 *      Returns: bool
***************************************************/
bool plane_crashed(int in, int out, int interval);


#endif // PLANE_H
