#include "buffer.h"
#include "config.h"
#include <stdio.h>
#include <string.h>

static char fbuffer[SCREEN_HEIGHT][SCREEN_WIDTH];
static float zbuffer[SCREEN_HEIGHT][SCREEN_WIDTH];
static int colorbuffer[SCREEN_HEIGHT][SCREEN_WIDTH];

void clear_fbuffer()
{
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        memset(fbuffer[i], DEFAULT_BUFFER_CHAR, SCREEN_WIDTH);
    }
}

void clear_zbuffer()
{
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            zbuffer[y][x] = 1e9f;
        }
    }
}

void clear_colorbuffer()
{
    memset(colorbuffer, 0, sizeof(colorbuffer));
}

void buffer_reset()
{
    clear_fbuffer();
    clear_zbuffer();
    clear_colorbuffer();
}

void buffer_draw()
{
    printf("\n");
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        printf(" ");
        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            int color = colorbuffer[y][x];
            if (color) {
                printf("\033[1;%dm%c\033[0m", color, fbuffer[y][x]);
            } else {
                printf("%c", fbuffer[y][x]);
            }
        }
        printf(" ");
        printf("\n");
    }
    printf("\n");
}

Vec3 world_to_cam(Vec3 point, Camera cam)
{
    Vec3 rel = { point.x - cam.pos.x, point.y - cam.pos.y, point.z - cam.pos.z };
    Vec3 result = rotate_about_XYZ(rel, (Vec3){0.0f, 0.0f, 0.0f}, -cam.r.x, -cam.r.y, -cam.r.z);

    return result;
}

Vec3 projected(Vec3 point)
{
    // here z is for indexing
    Vec3 projected_point = {
        X_CENTRE + (point.x * VIEWFRAME_DISTANCE / point.z),
        Y_CENTRE - (point.y * VIEWFRAME_DISTANCE / point.z),
        point.z
    };

    return projected_point;
}

void buffer_add_Plane3(Plane3 obj, Camera cam, char chr, int color)
{
    for (float u = 0; u <= 1.0f; u += SAMPLE_STEP) {
        for (float v = 0; v <= 1.0f; v += SAMPLE_STEP) {
            Vec3 interpolated_point = {
                .x = ((1 - u) * (1 - v) * obj.C00.x + u * (1 - v) * obj.C10.x + (1 - u) * v * obj.C01.x + u * v * obj.C11.x),
                .y = ((1 - u) * (1 - v) * obj.C00.y + u * (1 - v) * obj.C10.y + (1 - u) * v * obj.C01.y + u * v * obj.C11.y),
                .z = ((1 - u) * (1 - v) * obj.C00.z + u * (1 - v) * obj.C10.z + (1 - u) * v * obj.C01.z + u * v * obj.C11.z)
            };
            
            Vec3 cam_point = world_to_cam(interpolated_point, cam);
            if (cam_point.z <= 0.01f) continue;

            Vec3 projected_point = projected(cam_point);
            
            int x = (int)(projected_point.x + 0.05f);
            int y = (int)(projected_point.y + 0.05f);

            if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
                if (projected_point.z >= zbuffer[y][x]) continue;
                fbuffer[y][x] = chr;
                zbuffer[y][x] = projected_point.z;
                colorbuffer[y][x] = color;       
            }
        }
    }
}
