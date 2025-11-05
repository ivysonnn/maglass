#pragma once

#include <raylib.h>

void zoom(Camera2D *cam, Vector2 mous_pos, float zoom_factor);
void fix_zoom(Camera2D* cam, Rectangle world_rect);
