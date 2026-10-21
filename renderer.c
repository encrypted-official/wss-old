#include "renderer.h"
#include "config.h"
#include "camera.h"
#include "input.h"
#include "examples.h"
#include <time.h>
#include <stdio.h>

void map(Camera cam)
{
    Plane3 floor = {
        .C00 = { -50, -20, -50 },
        .C10 = {  50, -20, -50 },
        .C11 = {  50, -20,  50 },
        .C01 = { -50, -20,  50 }
    };
    buffer_add_Plane3(floor, cam, '.', 34); // Blue floor

    // Wall 1
    Plane3 wall1 = {
        .C00 = { -50, -20, -50 },
        .C10 = { -50, -20,  50 },
        .C11 = { -50,  20,  50 },
        .C01 = { -50,  20, -50 }
    };
    buffer_add_Plane3(wall1, cam, '#', 31); // Red wall

    // Wall 2
    Plane3 wall2 = {
        .C00 = { 50, -20, -50 },
        .C10 = { 50, -20,  50 },
        .C11 = { 50,  20,  50 },
        .C01 = { 50,  20, -50 }
    };
    buffer_add_Plane3(wall2, cam, '#', 31); // Red wall

    // // Platform in the middle
    // Plane3 platform = {
    //     .C00 = { -20, 0, -20 },
    //     .C10 = {  20, 0, -20 },
    //     .C11 = {  20, 0,  20 },
    //     .C01 = { -20, 0,  20 }
    // };
    // buffer_add_Plane3(platform, cam, '=', 33); // Yellow platform

    // Small block to jump on
    Plane3 block = {
        .C00 = { -10, 10, -10 },
        .C10 = {  0,  10, -10 },
        .C11 = {  0,  10,   0 },
        .C01 = { -10, 10,   0 }
    };
    buffer_add_Plane3(block, cam, '+', 32); // Green block
}

void update(Camera *cam)
{
    crazy_cube(*cam);
    red_plane(*cam);

    map(*cam);

    if (get_input())
    {
        char c = getchar();
        if (c == 'w') cam_tran_by(cam, 0.0f, 5.0f, 0.0f);
        else if (c == 's') cam_tran_by(cam, 0.0f, -5.0f, 0.0f);
        else if (c == 'a') cam_tran_by(cam, 0.0f, 0.0f, -5.0f);
        else if (c == 'd') cam_tran_by(cam, 0.0f, 0.0f, 5.0f);
        else if (c == 27) {
            if (getchar() == '[') {
                c = getchar();
                // if (c == 'A') cam_rot_by(cam, -5.0f, 0.0f, 0.0f);
                // else if (c == 'B') cam_rot_by(cam, 5.0f, 0.0f, 0.0f);
                if (c == 'C') cam_rot_by(cam, 0.0f, 5.0f, 0.0f);
                else if (c == 'D') cam_rot_by(cam, 0.0f, -5.0f, 0.0f);
            }
        }
    }
}

void render(Camera cam)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    while (1) {
        update(&cam);
        buffer_draw();
        
        clock_gettime(CLOCK_MONOTONIC, &end);
        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        double sleep_time = TICK_TIME - elapsed;

        if (sleep_time > 0) {
            struct timespec req = {
                .tv_sec = (time_t)sleep_time,
                .tv_nsec = (long)((sleep_time - (time_t)sleep_time) * 1e9)
            };
            nanosleep(&req, NULL);
        }

        clock_gettime(CLOCK_MONOTONIC, &start);
        buffer_reset();
    }
}
