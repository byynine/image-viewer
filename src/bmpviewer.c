#include <stdio.h>
#include <stdint.h>

#include <SDL2/SDL.h>

int map(int value, int inMin, int inMax, int outMin, int outMax)
{
    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

int readBitmap(
    const char *bitmapFilename,
    uint32_t resolution[2],
    uint8_t **pixelArray
)
{
    FILE *bmp = fopen(bitmapFilename, "rb");
    if (!bmp) { perror("fopen"); return 1; }

    uint16_t bpp;
    uint32_t offset;
    int32_t height;

    fseek(bmp, 18, SEEK_SET);
    fread(&resolution[0], 4, 1, bmp);
    fread(&height,        4, 1, bmp);

    resolution[1] = (height < 0) ? -height : height;

    fseek(bmp, 28, SEEK_SET);
    fread(&bpp, 2, 1, bmp);

    if (bpp != 32) { fprintf(stderr, "only 32-bit BMP supported\n"); fclose(bmp); return 1; }

    fseek(bmp, 10, SEEK_SET);
    fread(&offset, 4, 1, bmp);
	fseek(bmp, offset, SEEK_SET);

    uint32_t pixelArrayBytes = resolution[0] * resolution[1] * 4;

	*pixelArray = malloc(pixelArrayBytes);
    if (!*pixelArray) { perror("malloc"); fclose(bmp); return 1; }

    fread(*pixelArray, 1, pixelArrayBytes, bmp);

    fclose(bmp);
    return 0;
}

void SDL_StartSdl(
	const uint32_t bmpResolution[2],
	uint8_t *pixelArray
)
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_CreateWindowAndRenderer(bmpResolution[0], bmpResolution[1], 0, &window, &renderer);

	SDL_Event event;
	unsigned int running = 1;
	while (running)
	{
		while (SDL_PollEvent(&event)) { if (event.type == SDL_QUIT) { running = 0; } }
	
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		const unsigned int width = bmpResolution[0];
		const unsigned int height = bmpResolution[1];
		const unsigned int bpp = 4;

		for (unsigned int y = 0; y < height; y++)
		{
			for (unsigned int x = 0; x < width; x++)
			{
		        size_t pidx = ((height - 1 - y) * width + x) * bpp;
		        uint8_t b = pixelArray[pidx+0];
		        uint8_t g = pixelArray[pidx+1];
		        uint8_t r = pixelArray[pidx+2];
		        uint8_t a = pixelArray[pidx+3];
		
		        SDL_SetRenderDrawColor(renderer, r, g, b, a);

		        SDL_Rect rect = { x, y, 1, 1 };
		        SDL_RenderFillRect(renderer, &rect);
			}
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	if (argc != 2) { printf("incorrect argument count\n"); return 1; }

	uint32_t res[2];
	uint8_t *pxarr = NULL;

	if (readBitmap(argv[1], res, &pxarr) != 0) { return 1; }
	
	SDL_StartSdl(res, pxarr);

	free(pxarr);
	return 0;
}
