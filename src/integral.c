#include <stdio.h>
#include <stdint.h>

#include "../includes/integral.h"

double integral( double (*f)(double k), double k0, double kf )
{
    double area = 0.0;
    double step = (kf - k0) / N_ITERATIONS;
    for (uint8_t i = 0; i < N_ITERATIONS; i++)
    {
        area += f(k0 + i*step) * step;
    }
    return area;
}