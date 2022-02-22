build: build_dir
	gcc -Wall -std=c99 -o build/renderer 3drenderer/*.c -I/usr/include/SDL2 -D_REENTRANT -lSDL2 -lm

build_dir:
	mkdir -p build

run: build
	./build/renderer

clean:
	rm -rf build/
