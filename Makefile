CFLAGS := -lm -D_REENTRANT

detected_OS := Linux
# NOTE: bug in the detection keeps falling back to non-linux
# ifeq ($(OS),Windows_NT) # is Windows_NT on XP, 2000, 7, Vista, 10...
# 	detected_OS := Windows
# else
# 	detected_OS := $(shell uname)  # same as "uname -s"
# endif

ifeq ($(detected_OS),Linux)
	# NOTE: added -fcommon to allow lenient multiple definitions
	# of global variables in latest gcc until I get around to fixing it
	CFLAGS += -fcommon -lSDL2 -I/usr/include/SDL2
else
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
