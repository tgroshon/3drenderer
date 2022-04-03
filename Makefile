CFLAGS := -lm -D_REENTRANT 

ifeq ($(OS),Windows_NT) # is Windows_NT on XP, 2000, 7, Vista, 10...
	detected_OS := Windows
else
	detected_OS := $(shell uname)  # same as "uname -s"
endif

ifeq ($(detected_OS),Linux)
	CFLAGS += -lSDL2 -I/usr/include/SDL2
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
