#include <maglass/handle_input.h>
#include <raylib.h>

void handle_keyboard_input(Camera2D *cam, Vector2 mous_pos)
{
	if(IsKeyPressed(KEY_EQUAL))
	{	
        Vector2 mouseWorldPos = GetScreenToWorld2D(mous_pos, *cam);
        cam->offset = mous_pos;
        cam->target = mouseWorldPos;
		cam->zoom += 0.5f;
	}
	if(cam->zoom > 3.5f) cam->zoom = 3.5f;
	if(IsKeyPressed(KEY_MINUS)) 
	{
        Vector2 mouseWorldPos = GetScreenToWorld2D(mous_pos, *cam);
        cam->offset = mous_pos;
        cam->target = mouseWorldPos;
		cam->zoom -= 0.5f;
	}
	if(cam->zoom < 1.0f) cam->zoom = 1.0f;
}
