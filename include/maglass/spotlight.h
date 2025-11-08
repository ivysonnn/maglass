#pragma once

#include <raylib.h>
#include <stdbool.h>

typedef struct Spotlight {
    bool is_on;
    Shader shader;
	float radius;
    int res_loc;
    int radius_loc;
    int light_pos_loc;
} Spotlight;

Spotlight init_spotlight();
void toggle_spotlight(Spotlight* spotlight);
void draw_spotlight(Spotlight* spotlight, Texture2D tex, float radius);
void fix_spotlight_position(Spotlight* spotlight, Camera2D* cam, Vector2 mous_pos);
void change_spotlight_radius(Spotlight* spotlight, float scroll);
