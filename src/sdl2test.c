#include <SDL2/SDL.h>

int map(int value, int in_min, int in_max, int out_min, int out_max)
{
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

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

		int columns = windowSize[0];
		int rows = windowSize[1];

		int rectSize[2] = {windowSize[0]/columns, windowSize[1]/rows};

		for (int column = 0; column < columns; column++)
		{
			for (int row = 0; row < rows; row++)
			{
				SDL_Rect rect;
				rect.x = column * rectSize[0];
				rect.y = row * rectSize[1];
				rect.w = (column == columns - 1) ? windowSize[0] - rect.x : rectSize[0];
				rect.h = (row == rows - 1) ? windowSize[1] - rect.y : rectSize[1];

				int shade = map(row, 0, rows - 1, 0, 255);

				SDL_SetRenderDrawColor(renderer, shade, shade, shade, 255);
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
