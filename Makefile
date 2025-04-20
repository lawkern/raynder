compile:
	mkdir -p build
	$(CC) -o build/raynder src/main.c src/platform_sdl.c `pkg-config sdl3 --cflags --libs`

run:
	build/raynder
