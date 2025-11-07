#include <maglass/handle_input.h>
#include <maglass/zoom.h>
#include <maglass/panning.h>
#include <raylib.h>
#include <stdbool.h>

#define ZOOM_IN "in"
#define ZOOM_OUT "out"

void handle_keyboard_input(Camera2D *cam, Vector2 mous_pos)
{ 
	float scroll = GetMouseWheelMove();
	float zoom_factor = 0.5f;

	if(IsKeyPressed(KEY_EQUAL))
	{	
		zoom(cam, mous_pos, zoom_factor);
	}
	else if(IsKeyPressed(KEY_MINUS)) 
	{
		zoom_factor *= -1.0f;
		zoom(cam, mous_pos, zoom_factor);
	}

	zoom_factor = 0.2f * scroll;
	if(scroll > 0)
	{
		zoom(cam, mous_pos, zoom_factor);
	}
	else if(scroll < 0)
	{
		zoom(cam, mous_pos, zoom_factor);
	}

	if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
		drag_and_move(cam, mous_pos);
	}
}
