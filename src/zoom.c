#include <maglass/zoom.h>
#include <raylib.h>
#include <raymath.h>
#include <string.h>

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

	fix_zoom(cam, world_rect);
}

void fix_zoom(Camera2D *cam, Rectangle world_rect)
{
	float min_target_x = cam->offset.x / cam->zoom;
	float max_target_x = world_rect.width - (GetScreenWidth() - cam->offset.x) / cam->zoom;
	float min_target_y = cam->offset.y / cam->zoom;
	float max_target_y = world_rect.height - (GetScreenHeight() - cam->offset.y) / cam->zoom;

	cam->target.x = Clamp(cam->target.x, min_target_x, max_target_x);
	cam->target.y = Clamp(cam->target.y, min_target_y, max_target_y);
}
