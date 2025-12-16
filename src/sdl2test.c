#include <SDL2/SDL.h>

int main()
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Init(SDL_INIT_VIDEO);

	int windowSize[2] = {640, 480};
	SDL_CreateWindowAndRenderer(windowSize[0], windowSize[1], 0, &window, &renderer);

	SDL_Event event;
	int running = 1;
	while (running)
	{
		while (SDL_PollEvent(&event)) { if (event.type == SDL_QUIT) { running = 0; } }
	
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		int rectSize[2] = {windowSize[0]/8, windowSize[1]/8};

		int columns = 8;
		int rows = 8;

		for (int column = 0; column <= columns; column++)
		{
			for (int row = 0; row <= rows; row++)
			{
				SDL_Rect rect;
				rect.x = i * windowSize[0]/8;
				rect.y = i * windowSize[1]/8;
				rect.w = rectSize[0];
				rect.h = rectSize[1];

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(renderer, &rect);
			}
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
