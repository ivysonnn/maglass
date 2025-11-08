#include "maglass/spotlight.h"
#include <raylib.h>

#include <stdlib.h>
#include <stdio.h>

#include <maglass/handle_input.h>

const char* FILENAME = "screenshot.png";

int main(void)
{
	char command[256];
	snprintf(command, sizeof(command), "grim -t png %s", FILENAME);
	system(command);

	InitWindow(0, 0, "");
	SetTargetFPS(300);
	ToggleFullscreen();

	Camera2D cam = 
	{
		.offset = (Vector2){0.0f, 0.0f},
		.rotation = 0.0f,
		.zoom = 1.0f,
	};
	Texture2D tex = LoadTexture(FILENAME);
	
	Vector2 mous_pos;

	Spotlight spotlight = init_spotlight();

	while(!WindowShouldClose())
	{
		mous_pos.x = GetMouseX();
		mous_pos.y = GetMouseY();
	
		handle_inputs(&cam, mous_pos, &spotlight);

		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode2D(cam);
		if(!spotlight.is_on)
		{
			DrawTexture(tex, 0, 0, WHITE);
		}
		else 
		{
			BeginShaderMode(spotlight.shader);
			draw_spotlight(&spotlight, tex, spotlight.radius / cam.zoom);
			fix_spotlight_position(&spotlight, &cam, mous_pos);
			DrawTexture(tex, 0, 0, WHITE);
			EndShaderMode();
		}
		EndMode2D();
		EndDrawing();
	}

	UnloadTexture(tex);
	UnloadShader(spotlight.shader);

	CloseWindow();
	remove(FILENAME);

	return 0;
}
