#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "IL/il.h"

int main(int argc, char *argv[]) {
	if (argc < 3 || argc > 4) {
		fprintf(stderr, "%1$s: usage: %1$s <color> <input> [output]\n", argv[0]);
		return 1;
	}

	unsigned long long remColorL = strtoul(argv[1], NULL, 16);
	uint32_t remColorI = remColorL;
	uint8_t* remColor = (uint8_t*) &remColorI;

	double ra = remColor[3] / 255.0;
	double rr = remColor[2] / 255.0;
	double rg = remColor[1] / 255.0;
	double rb = remColor[0] / 255.0;

	ilInit();

	ILboolean result = ilLoadImage(argv[2]);

	if (result == IL_FALSE) {
		fprintf(stderr, "%s: failed to load image `%s'\n", argv[0], argv[2]);
		return 2;
	}

	int w = ilGetInteger(IL_IMAGE_WIDTH);
	int h = ilGetInteger(IL_IMAGE_HEIGHT);
	uint8_t* bytes = (uint8_t*) malloc(w*h*4);

	ilCopyPixels(0, 0, 0, w, h, 1, IL_RGBA, IL_UNSIGNED_BYTE, bytes);

	for (int i = 0; i < w*h; i++) {
		// Sloppily ported from the Grim Color Reaper paint.net plugin
		int idx = i*4;
		double r = bytes[idx] / 255.0;
		double g = bytes[idx+1] / 255.0;
		double b = bytes[idx+2] / 255.0;
		double a = bytes[idx+3] / 255.0;

		double rdif = r - rr;
		double gdif = g - rg;
		double bdif = b - rb;

		double dist = sqrt(rdif*rdif + gdif+gdif * bdif+bdif);


		if (dist < a) {
			a = dist;

			r = (r - rr*(1-dist)) / dist;
			g = (g - rg*(1-dist)) / dist;
			b = (b - rb*(1-dist)) / dist;
		}
		bytes[idx] = (uint8_t)(r*255);
		bytes[idx+1] = (uint8_t)(g*255);
		bytes[idx+2] = (uint8_t)(b*255);
		bytes[idx+3] = (uint8_t)(a*255);
	}

	ilSetPixels(0, 0, 0, w, h, 1, IL_RGBA, IL_UNSIGNED_BYTE, bytes);
	free(bytes);

	char* outFile;
	if (argc >= 4) {
		outFile = argv[3];
	} else {
		outFile = argv[2];
	}

	ilEnable(IL_FILE_OVERWRITE);
	ilSaveImage(outFile);

	return 0;
}
