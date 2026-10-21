#pragma once

#include "camera.h"
#include "math3d.h"

struct Camera;

void buffer_reset();
void buffer_draw();

void buffer_add_Plane3(Plane3, Camera, char, int);
