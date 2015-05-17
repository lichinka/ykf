#pragma once

#include <string>
#include "vector2d.h"



namespace ykf {

// the screen dimensions
static const int WIN_WIDTH  = 320;
static const int WIN_HEIGHT = 200;

// the zoom level applied when rendering
static const int WIN_ZOOM   = 3.0f;

static const int FPS        = 12;
static const int DELAY_TIME = 1000.0f / FPS;

// assets are kept in this directory
static const std::string DATA_DIR = "data";

// acceleration due to gravity
static const Vector2D<float> GRAVITY (0.0, 0.98);

}
