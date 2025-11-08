#include <maglass/spotlight.h>
#include <raylib.h>

const float INITIAL_RADIUS = 150.0f;
const float MIN_RADIUS = 100.0f;
const float MAX_RADIUS = 400.0f;
Spotlight init_spotlight()
{
	Shader shader = LoadShader(0, "/usr/local/share/maglass/assets/shaders/spotlight.fs");

	int res_loc = GetShaderLocation(shader, "resolution");
	int radius_loc = GetShaderLocation(shader, "radius");
	int light_pos_loc = GetShaderLocation(shader, "lightPos");

	Vector2 res = {(float)GetScreenWidth(), (float)GetScreenHeight()};
	SetShaderValue(shader, res_loc, &res, SHADER_UNIFORM_VEC2);

	

	return (Spotlight)
	{
		.is_on = false,
		.shader = shader,
		.radius = INITIAL_RADIUS,
		.res_loc = res_loc,
		.radius_loc = radius_loc,
		.light_pos_loc = light_pos_loc,
	};
}

void toggle_spotlight(Spotlight* spotlight)
{
	spotlight->is_on = !spotlight->is_on;
	spotlight->radius = INITIAL_RADIUS;
}

void draw_spotlight(Spotlight* spotlight, Texture2D tex, float radius)

{
	SetShaderValue(spotlight->shader, spotlight->radius_loc, &radius, SHADER_UNIFORM_FLOAT);
	Vector2 mouse = GetMousePosition();

	SetShaderValue(spotlight->shader, spotlight->light_pos_loc, &mouse, SHADER_UNIFORM_VEC2);
}

void fix_spotlight_position(Spotlight* spotlight, Camera2D* cam, Vector2 mous_pos)
{
	Vector2 new_pos = GetScreenToWorld2D(mous_pos, *cam);
	SetShaderValue(spotlight->shader, spotlight->light_pos_loc, &new_pos, SHADER_UNIFORM_VEC2);
}

void change_spotlight_radius(Spotlight *spotlight, float scroll)
{
	if(spotlight->radius > MIN_RADIUS || spotlight->radius < MAX_RADIUS)
	{
		spotlight->radius += (scroll * -5.0);
	}

	if(spotlight->radius < MIN_RADIUS)
	{
		spotlight->radius = MIN_RADIUS;
	}
	else if(spotlight->radius > MAX_RADIUS)
	{
		spotlight->radius = MAX_RADIUS;
	}
}
