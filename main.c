#include <stdio.h>
#include <math.h>
#include "quaternion.h"

int main(void) {
    double axis[3] = { 0, 0, 1 };
    double vector[3] = { 0, 1, 0 };
    double angle = M_PI/4;

    double ret[3];

    rotate(vector, axis, angle, ret);
    printf("x: %f\n", ret[0]);
    printf("y: %f\n", ret[1]);
    printf("z: %f\n", ret[2]);

    return 0;
}
