#include <stdio.h>
#include <stdint.h>

int main(void)
{
	FILE *bmp = fopen("res/blue-bmp-16-bit.bmp", "rb");

	if (!bmp) { perror("fopen"); return 1; }

	uint32_t resolution[2];
	
	fseek(bmp, 18, SEEK_SET);
	fread(&resolution, sizeof(uint32_t), 2, bmp);

	for (uint32_t i = 0; i < 2; i++)
	{
		printf("%d ", resolution[i]);
	}
	printf("\n");

	// uint32_t offset;

	// fseek(bmp, 10, SEEK_SET);
	// fread(&offset, sizeof(offset), 1, bmp);
	// fseek(bmp, offset, SEEK_SET);

	fclose(bmp);
	return 0;
}
