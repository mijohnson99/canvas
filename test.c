#include "src/canvas.h"
#include "src/line.h"

int main()
{
	video_start();

	for (int x = 0; x < CANVAS_WIDTH; x++)
	for (int y = 0; y < CANVAS_HEIGHT; y++)
		PX(x, y) = ~0;


	for (int i = 0; i < CANVAS_HEIGHT; i+=10) {
		for LINE(CANVAS_HEIGHT-i, 0, 0, i)
			PX(x, y) = 0;
	}

	video_update();

	while (!user_quit())
		continue;

	video_stop();
	return 0;
}
