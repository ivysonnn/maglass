#include <maglass/utils/clamp.h>

void m_clamp(Camera2D *cam, Rectangle world_rect)
{
	float min_target_x = cam->offset.x / cam->zoom;
	float max_target_x = world_rect.width - (GetScreenWidth() - cam->offset.x) / cam->zoom;
	float min_target_y = cam->offset.y / cam->zoom;
	float max_target_y = world_rect.height - (GetScreenHeight() - cam->offset.y) / cam->zoom;

	cam->target.x = Clamp(cam->target.x, min_target_x, max_target_x);
	cam->target.y = Clamp(cam->target.y, min_target_y, max_target_y);
}
