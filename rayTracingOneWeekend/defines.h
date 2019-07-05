#pragma once

#define PLATFORM_WIN 1

//Setup screen and output image
//4K 3840x2160, 2K 2560x1440
#define DEFAULT_RENDER_WIDTH 500
#define DEFAULT_RENDER_HEIGHT 500
#define DEFAULT_RENDER_AA 1
#define DEBUG_RUN_THREADS 8

#define OUTPUT_BMP 0
#define RUN_RAY_TRACE 1
#define BYPASS_SCENE_CONFIG 1

#define GLOBAL_ILLUM 0
#define DEPTH_RECURSION 50

#define OUTPUT_RANDOM_SCENE 0
#define DISPLAY_WINDOW 0