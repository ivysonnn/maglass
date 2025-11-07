#include <maglass/zoom.h>
#include <maglass/utils/clamp.h>
#include <raylib.h>
#include <raymath.h>

void zoom(Camera2D *cam, Vector2 mous_pos, float zoom_factor)
{
	Rectangle world_rect = (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()};
	Vector2 mouseWorldPos = GetScreenToWorld2D(mous_pos, *cam);

	cam->zoom += zoom_factor;

	if(cam->zoom > 3.5f)
		cam->zoom = 3.5f;
	if(cam->zoom < 1.0f)
		cam->zoom = 1.0f;

	cam->offset = mous_pos;
	cam->target = mouseWorldPos;

 	m_clamp(cam, world_rect);
}
