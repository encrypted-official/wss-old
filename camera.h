#pragma once

#include "math3d.h"
#include <math.h>

#define FOV_X 80.0f
#define VIEWFRAME_DISTANCE ((SCREEN_WIDTH / 2.0f) / tan((FOV_X * M_PI / 180.0f) / 2.0f))

// combine fox, viewframe distance to individual cameras
// also use each camera in the rendering pipeline for enhanced viewframe visuals

typedef struct { Vec3 pos, r; } Camera;

void cam_tran_by(Camera *, float, float, float);
void cam_rot_by(Camera *, float, float, float);
