#include <SDL2/SDL.h>

int main()
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
	// SDL_RenderSetScale(renderer, 4, 4);

	
	SDL_Event event;
	int running = 1;
	while (running)
	{
		while (SDL_PollEvent(&event)) { if (event.type == SDL_QUIT) { running = 0; } }
	
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = 50;
		rect.h = 50;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderPresent(renderer);	
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
