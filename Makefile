build:
	gcc -Wall -std=c99 3drenderer/*.c -o renderer

run:
	./renderer

clean:
	rm renderer