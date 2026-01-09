CFLAGS := -lm -D_REENTRANT

detected_OS := $(shell uname -s)

ifeq ($(detected_OS),Linux)
	# NOTE: added -fcommon to allow lenient multiple definitions
	# of global variables in latest gcc until I get around to fixing it
	CFLAGS += -fcommon -lSDL2 -I/usr/include/SDL2
else ifeq ($(detected_OS),Darwin)
	# macOS with Homebrew SDL2
	CFLAGS += -I$(shell brew --prefix sdl2)/include $(shell sdl2-config --libs)
else
	# Fallback for framework install
	CFLAGS += -F/Library/Frameworks -framework SDL2
endif

build: build_dir
	gcc -Wall -std=c99 -o build/renderer 3drenderer/*.c $(CFLAGS)

build_dir:
	mkdir -p build

run: build
	./build/renderer

clean:
	rm -rf build/
