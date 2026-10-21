#pragma once

typedef enum { AXIS_X, AXIS_Y, AXIS_Z } Axis;

/*
    Every shape/form follows CXYZ convention.
    X is +ve to right.
    Y is +ve to up.
    Z is +ve to back.
    Eular rotation goes X->Y->Z.
*/

typedef struct { float x, y; } Vec2;
typedef struct { float x, y, z; } Vec3;

typedef struct { Vec2 C00, C10, C11, C01; } Plane2;
typedef struct { Vec3 C00, C10, C11, C01; } Plane3;
typedef struct { Vec3 C000, C100, C110, C010, C001, C101, C111, C011; } Cube;

float rad(float);

// Vec3 rotate_by(Vec3, Axis, float);
// Vec3 rotate_by_XYZ(Vec3, float, float, float);
Vec3 rotate_about(Vec3, Vec3, Axis, float);
Vec3 rotate_about_XYZ(Vec3, Vec3, float, float, float);
