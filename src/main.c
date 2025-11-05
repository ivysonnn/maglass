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
	SetTargetFPS(60);
	ToggleFullscreen();

	Camera2D cam = 
	{
		.offset = (Vector2){0.0f, 0.0f},
		.rotation = 0.0f,
		.zoom = 1.0f,
	};
	Texture2D tex = LoadTexture(FILENAME);
	Vector2 mous_pos;

	while(!WindowShouldClose())
	{
		mous_pos.x = GetMouseX();
		mous_pos.y = GetMouseY();
	
		handle_keyboard_input(&cam, mous_pos);
		BeginDrawing();
			ClearBackground(BLACK);
			BeginMode2D(cam);
				DrawTexture(tex, 0, 0, WHITE);
			EndMode2D();
		EndDrawing();
	}

	CloseWindow();
	remove(FILENAME);

	return 0;
}
