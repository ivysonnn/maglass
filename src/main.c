#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL_main.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>

#define WIN_WIDTH 1080
#define WIN_HEIGHT 720

typedef struct
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width;
	int height;
} AppState;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char** argv)
{
	AppState* app_state = SDL_malloc(sizeof(AppState));
	*app_state = (AppState)
	{ 
		.width = WIN_WIDTH,
		.height = WIN_HEIGHT
	};
	*appstate = app_state;

	if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_CAMERA))
	{
		SDL_Log("Couldn't initialize maglass: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	if(!SDL_CreateWindowAndRenderer("", app_state->width, app_state->height, SDL_WINDOW_FULLSCREEN, &(app_state->window), &(app_state->renderer)))
	{
		SDL_Log("Couldn't create window or renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
	AppState* app_state = appstate;
	SDL_SetRenderDrawColorFloat(app_state->renderer, 0.4f, 0.6f, 1.0f, SDL_ALPHA_OPAQUE_FLOAT);

	SDL_RenderClear(app_state->renderer);
	SDL_RenderPresent(app_state->renderer);
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	if(event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	AppState* app_state = appstate;
	SDL_free(appstate);
	SDL_Quit();
}
