#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readHex(const char *filename)
{
	FILE *pF = fopen(filename, "rb");
	if (!pF) { return NULL; }

	if (fseek(pF, 0, SEEK_END) != 0) { return NULL; }

	long fSize = ftell(pF);
	if (fSize < 0) { fclose(pF); return NULL; } 
	
	rewind(pF);

	char *result = malloc((size_t)fSize * 2 + 1);
	if (!result) { fclose(pF); return NULL; }

	unsigned char buffer[8192];
	size_t bytesRead;
	char *pResult = result;

	while ((bytesRead = fread(buffer, 1, sizeof(buffer), pF)) > 0)
	{
		for (size_t i = 0; i < bytesRead; i++)
		{
			static const char hexTable[] = "0123456789ABCDEF";
			*pResult++ = hexTable[buffer[i] >> 4];
			*pResult++ = hexTable[buffer[i] & 0x0F];
		}
	}

	*pResult = '\0';
	fclose(pF);
	return result;
}

int main(int argc, char *argv[])
{
	if (argc != 2) { printf("no file provided, input a file as an argument\n"); return 1; }

	char *hex = readHex(argv[1]);
	if (!hex) { printf("error reading file\n"); } else { printf("%s\n", hex); free(hex); }

	return 0;
}
