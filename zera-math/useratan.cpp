#include "math.h"

double userAtan(double im, double re)
{
    double arctan = atan2(im, re) * 360.0 / (2*M_PI);
    if (arctan < 0.0)
        arctan += 360.0;
    return arctan;
}
