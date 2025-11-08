#include <maglass/spotlight.h>
#include <maglass/handle_input.h>
#include <maglass/zoom.h>
#include <maglass/panning.h>
#include <raylib.h>
#include <stdbool.h>

#define ZOOM_IN "in"
#define ZOOM_OUT "out"

void handle_inputs(Camera2D *cam, Vector2 mous_pos, Spotlight *spotlight)
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
	if(scroll != 0 && !IsKeyDown(KEY_LEFT_CONTROL))
	{
		zoom(cam, mous_pos, zoom_factor);
	}

	if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
		drag_and_move(cam, mous_pos);
	}

	if(IsKeyPressed(KEY_F))
	{
		toggle_spotlight(spotlight);
	}

	if(spotlight->is_on && IsKeyDown(KEY_LEFT_CONTROL) && scroll != 0)
	{
		change_spotlight_radius(spotlight, scroll);
	}
}
