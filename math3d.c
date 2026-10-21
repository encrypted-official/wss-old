#include "math3d.h"
#include <math.h>

float rad(float deg)
{
    return deg * (float)M_PI / 180.0f;
}

// Vec3 rotate_by(Vec3 r, Axis axis, float angle)
// {
//     float t = rad(angle);
//     float ct = cosf(t), st = sinf(t);

//     float nx = r.x, ny = r.y, nz = r.z;

//     Vec3 result = {nx, ny, nz};

//     // hardcoded rodrigues' formula for fixed x,y,z in space to our convention
//     switch (axis) {
//         case AXIS_X:
//             result.y =  ny * ct - nz * st;
//             result.z =  ny * st + nz * ct;
//             break;
//         case AXIS_Y:
//             result.x =  nx * ct + nz * st;
//             result.z = -nx * st + nz * ct;
//             break;
//         case AXIS_Z:
//             result.x =  nx * ct - ny * st;
//             result.y =  nx * st + ny * ct;
//             break;
//         default:
//             break;
//     }
    
//     return result;
// }

// Vec3 rotate_by_XYZ(Vec3 r, float ax, float ay, float az)
// {
//     r = rotate_by(r, AXIS_X, ax);
//     r = rotate_by(r, AXIS_Y, ay);
//     r = rotate_by(r, AXIS_Z, az);

//     return r;
// }

Vec3 rotate_about(Vec3 p, Vec3 c, Axis axis, float angle)
{
    float t = rad(angle);
    float ct = cosf(t), st = sinf(t);

    float x = p.x - c.x;
    float y = p.y - c.y;
    float z = p.z - c.z;

    float nx = x, ny = y, nz = z;

    // rotation matrix multiplication
    switch (axis) {
        case AXIS_X:
            ny =  y * ct - z * st;
            nz =  y * st + z * ct;
            break;
        case AXIS_Y:
            nx =  x * ct + z * st;
            nz = -x * st + z * ct;
            break;
        case AXIS_Z:
            nx =  x * ct - y * st;
            ny =  x * st + y * ct;
            break;
        default:
            break;
    }

    return (Vec3){ nx + c.x, ny + c.y, nz + c.z };
}

Vec3 rotate_about_XYZ(Vec3 p, Vec3 c, float ax, float ay, float az)
{
    p = rotate_about(p, c, AXIS_X, ax);
    p = rotate_about(p, c, AXIS_Y, ay);
    p = rotate_about(p, c, AXIS_Z, az);

    return p;
}
