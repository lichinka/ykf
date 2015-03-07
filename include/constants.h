#pragma once

#include <string>



namespace ykf {

// the screen dimensions
static const int WIN_WIDTH  = 320;
static const int WIN_HEIGHT = 200;

// the zoom level applied when rendering
static const int WIN_ZOOM   = 3.0f;

static const int FPS        = 10;
static const int DELAY_TIME = 1000.0f / FPS;

// assets are kept in this directory
static const std::string DATA_DIR = "data";

}
