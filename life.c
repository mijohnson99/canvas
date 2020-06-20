#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "src/canvas.h"

static bool cells[CANVAS_AREA], tmp[CANVAS_AREA];

static inline int offset(int x, int y, int dx, int dy)
{
	x += dx;
	y += dy;

	if (x < 0)
		x += CANVAS_WIDTH;
	else if (x >= CANVAS_WIDTH)
		x -= CANVAS_WIDTH;

	if (y < 0)
		y += CANVAS_HEIGHT;
	else if (y >= CANVAS_HEIGHT)
		y -= CANVAS_HEIGHT;

	return x + y * CANVAS_WIDTH;
}

int main(int argc, char **argv)
{
	double f = 30.0;
	if (argc > 1)
		f = atof(argv[1]);

	srand(time(NULL));
	video_start();

	for (int i = 0; i < CANVAS_AREA; i++)
		cells[i] = rand() & 1;

	while (!user_quit()) {
		tick();

		for (int i = 0, y = 0; y < CANVAS_HEIGHT; y++)
		for (int x = 0; x < CANVAS_WIDTH; x++, i++) {
			int neighbors = 0;
			for (int dx = -1; dx <= 1; dx++)
			for (int dy = -1; dy <= 1; dy++)
				if (dx || dy)
					neighbors += cells[offset(x, y, dx, dy)];

			if (neighbors == 3)
				tmp[i] = true;
			else if (neighbors != 2)
				tmp[i] = false;

			PX(x, y) = tmp[i] ? ~0 : 0;
		}

		for (int i = 0; i < CANVAS_AREA; i++)
			cells[i] = tmp[i];

		video_update();

		while (!user_quit() && tock() < 1.0/f)
			continue;
	}

	video_stop();
	return 0;
}
