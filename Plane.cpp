#include "Plane.h"

bool plane_coming_to_runway(int avg)
{
    double random = rand() / (double) RAND_MAX;
    if (random < (1.0 / avg))
    {
        return true;
    }
    return false;
}

bool plane_crashed(int in, int out, int interval)
{
    if (out - in > interval)
    {
        return true;
    }
    return false;
}
