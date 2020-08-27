#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include "src/canvas.h"

typedef uint32_t Color;

typedef struct point {
	int x, y;
	Color c;
} Point;

static inline Color rand_color(void)
{
	return ((double)rand()/RAND_MAX) * UINT32_MAX;
}

static inline double dist(Point *p1, Point *p2)
{
	int dx = p2->x - p1->x;
	int dy = p2->y - p1->y;
	return sqrt(dx*dx + dy*dy);
}

int main(int argc, char **argv)
{
	// Take argument
	int n_points;
	if (argc > 1)
		n_points = atoi(argv[1]);
	else
		return 1;

	// Initialize
	srand(time(NULL));
	video_start();

	// Create random points
	Point *points = malloc(n_points * sizeof(Point));
	for (int i = 0; i < n_points; i++) {
		points[i].x = rand() % CANVAS_WIDTH;
		points[i].y = rand() % CANVAS_HEIGHT;
		points[i].c = rand_color();
	}

	/*
	 *	Note: This algorithm is trivial, and very slow.
	 */

	// Plot pixel colors
#pragma omp parallel for
	for (int y = 0; y < CANVAS_HEIGHT; y++)
	for (int x = 0; x < CANVAS_WIDTH; x++) {
		Point here;
		here.x = x;
		here.y = y;

		double min_dist = DBL_MAX;
		Point *closest;
		for (int i = 0; i < n_points; i++) {
			double d = dist(&here, &points[i]);
			if (d < min_dist) {
				min_dist = d;
				closest = &points[i];
			}
			if (d == 0.0)
				break;
		}

		if (min_dist < 2.0)
			PX(x, y) = (Color)0x000000;
		else
			PX(x, y) = closest->c;
	}
	video_update();

	// Wait for exit
	while (!user_quit())
		continue;

	// Clean up and exit
	free(points);
	video_stop();

	return 0;
}
