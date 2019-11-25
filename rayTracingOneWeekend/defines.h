#pragma once

#define PLATFORM_WIN 1

//Setup screen and output image
//4K 3840x2160, 2K 2560x1440
#define DEFAULT_RENDER_WIDTH 600
#define DEFAULT_RENDER_HEIGHT 600
#define DEFAULT_RENDER_AA 1
#define DEBUG_RUN_THREADS 6 //0 selects max available threads

#define OUTPUT_BMP_EN 0
#define RUN_RAY_TRACE 1
#define BYPASS_SCENE_CONFIG 1

#define DISPLAY_FPS 1
#define OUTPUT_RANDOM_SCENE 0
#define DISPLAY_WINDOW 1
#define CAPTURE_MOUSE 1
#define ENABLE_CONTROLS 1

#define GLOBAL_ILLUM_EN 0
#define SKY_ILLUM_GAIN 0.3
#define GLOBAL_ILLUM_GAIN 0.3
#define CAMERA_DOF_EN 0
#define DEPTH_RECURSION 50

#define ENABLE_BITBLIT 1
#define DEBUG_SET_PIXEL 0