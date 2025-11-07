#include <maglass/panning.h>
#include <maglass/utils/clamp.h>
#include <raylib.h>

void drag_and_move(Camera2D* cam, Vector2 mous_pos)
{	
	Rectangle world_rect = (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()};
	Vector2 mouse_delta = GetMouseDelta();

	cam->target.x -= mouse_delta.x / cam->zoom;
	cam->target.y -= mouse_delta.y / cam->zoom;

	m_clamp(cam, world_rect);
}
