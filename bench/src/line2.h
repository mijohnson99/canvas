#ifndef LINE2_H
#define LINE2_H

#include <stdbool.h>

// Calls f on every point in a line, in correct order, until f returns true.
// Returns true if it stopped for this reason.
bool line2(bool (*f)(int x, int y), int x0, int y0, int x1, int y1);

#endif
