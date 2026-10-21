#include "renderer.h"
#include "buffer.h"
#include "input.h"
#include "camera.h"
#include "math3d.h"
#include "config.h"
#include "examples.h"

void update(Camera);

int main(void)
{
    static Camera cam = {
        .pos = { 0.0f, 0.0f, 0.0f },
        .r   = { 0.0f, 0.0f, 0.0f }
    };

    buffer_reset();
    render(cam);

    return 0;
}
