#include "camera.h"
#include "buffer.h"

void cam_local_axis(Camera *cam, Vec3 *forward, Vec3 *right, Vec3 *up)
{
    float cx = cosf(rad(cam->r.x)), sx = sinf(rad(cam->r.x));
    float cy = cosf(rad(cam->r.y)), sy = sinf(rad(cam->r.y));
    float cz = cosf(rad(cam->r.z)), sz = sinf(rad(cam->r.z));

    forward->x = cy * cz;
    forward->y = sx * sy * cz + cx * sz;
    forward->z = -cx * sy * cz + sx * sz;

    right->x = -cy * sz;
    right->y = -sx * sy * sz + cx * cz;
    right->z = cx * sy * sz + sx * cz;

    up->x = sy;
    up->y = -sx * cy;
    up->z = cx * cy;
}

void cam_rot_by(Camera *cam, float ax, float ay, float az)
{
    cam->r.x += ax;
    cam->r.y += ay;
    cam->r.z += az;

    if(cam->r.x > 180.0f) cam->r.x -= 360.0f;
    if(cam->r.x < -180.0f) cam->r.x += 360.0f;

    if(cam->r.y > 180.0f) cam->r.y -= 360.0f;
    if(cam->r.y < -180.0f) cam->r.y += 360.0f;

    if(cam->r.z > 180.0f) cam->r.z -= 360.0f;
    if(cam->r.z < -180.0f) cam->r.z += 360.0f;
}

void cam_tran_by(Camera *cam, float x, float y, float z)
{
    Vec3 forward, right, up;
    cam_local_axis(cam, &forward, &right, &up);

    cam->pos.x += right.x * x + up.x * y + forward.x * z;
    // cam->pos.y += right.y * x + up.y * y + forward.y * z;
    cam->pos.z += right.z * x + up.z * y + forward.z * z;
}
