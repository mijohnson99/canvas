# Parameters

CC = clang
CFLAGS = -Os -Wall
LD = ld
LDFLAGS = -lm -lSDL2

BACKEND = sdl2

ALL = grad draw life dot test

# Executables

all: $(ALL)

life:	life.o canvas.o
	$(CC) $(LDFLAGS) $^ -o $@

draw:	draw.o canvas.o cursor.o
	$(CC) $(LDFLAGS) $^ -o $@

grad:	grad.o canvas.o
	$(CC) $(LDFLAGS) $^ -o $@

dot:	dot.o canvas.o
	$(CC) $(LDFLAGS) $^ -o $@

test:	test.o canvas.o
	$(CC) $(LDFLAGS) $^ -o $@

# Object files

canvas.o: src/canvas_$(BACKEND).c src/canvas.h
	$(CC) $(CFLAGS) $< -c -o $@

cursor.o: src/cursor.c src/cursor.h
	$(CC) $(CFLAGS) $< -c -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

# Cleanup

.PHONY: clean
clean:
	$(RM) $(ALL) *.o
