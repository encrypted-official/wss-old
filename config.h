#pragma once

// renderer
#define TICK_RATE 20
#define TICK_TIME (1.0f / TICK_RATE)

#define SCREEN_WIDTH (100 - 2)
#define X_CENTRE (SCREEN_WIDTH / 2)
#define SCREEN_HEIGHT (80 - 1 - 2)
#define Y_CENTRE (SCREEN_HEIGHT / 2)

// buffer
#define DEFAULT_BUFFER_CHAR 32
#define SAMPLE_STEP 0.005f