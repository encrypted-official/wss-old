#include "examples.h"
#include "renderer.h"
#include "buffer.h"
#include "input.h"
#include "camera.h"
#include "config.h"
#include "math3d.h"

void crazy_cube(Camera cam)
{
    static float angle = 0.0f;
    static Vec3 centre = { 0.0f, 0.0f, 100.0f };

    static Cube cube = {
        .C000 = { -10, -10,  90 },
        .C100 = {  10, -10,  90 },
        .C110 = {  10,  10,  90 },
        .C010 = { -10,  10,  90 },
        .C001 = { -10, -10, 110 },
        .C101 = {  10, -10, 110 },
        .C111 = {  10,  10, 110 },
        .C011 = { -10,  10, 110 }
    };

    Cube rcube = {
        .C000 = rotate_about_XYZ(cube.C000, centre, angle, angle, angle),
        .C100 = rotate_about_XYZ(cube.C100, centre, angle, angle, angle),
        .C110 = rotate_about_XYZ(cube.C110, centre, angle, angle, angle),
        .C010 = rotate_about_XYZ(cube.C010, centre, angle, angle, angle),
        .C001 = rotate_about_XYZ(cube.C001, centre, angle, angle, angle),
        .C101 = rotate_about_XYZ(cube.C101, centre, angle, angle, angle),
        .C111 = rotate_about_XYZ(cube.C111, centre, angle, angle, angle),
        .C011 = rotate_about_XYZ(cube.C011, centre, angle, angle, angle)
    };

    Plane3 front  = { rcube.C001, rcube.C101, rcube.C111, rcube.C011 };
    Plane3 back   = { rcube.C000, rcube.C100, rcube.C110, rcube.C010 };
    Plane3 left   = { rcube.C000, rcube.C010, rcube.C011, rcube.C001 };
    Plane3 right  = { rcube.C100, rcube.C110, rcube.C111, rcube.C101 };
    Plane3 top    = { rcube.C010, rcube.C110, rcube.C111, rcube.C011 };
    Plane3 bottom = { rcube.C000, rcube.C100, rcube.C101, rcube.C001 };

    buffer_add_Plane3(front, cam,  '*', 31);
    buffer_add_Plane3(back, cam,   '#', 32);
    buffer_add_Plane3(left, cam,   '$', 33);
    buffer_add_Plane3(right, cam,  '%', 34);
    buffer_add_Plane3(top, cam,    '&', 35);
    buffer_add_Plane3(bottom, cam, '@', 36);

    angle += 2.5f;
}

void red_plane(Camera cam)
{
    Plane3 p1 = {
        .C00 = { -30, -30,  70 },
        .C10 = {  30, -30,  70 },
        .C11 = {  30, -30, 130 },
        .C01 = { -30, -30, 130 }
    };

    buffer_add_Plane3(p1, cam, '#', 37);
}
