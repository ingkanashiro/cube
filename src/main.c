#include "../include/input.h"
#include "../include/tesseract.h"

// compile:
// gcc src/sphere.c src/square.c src/input.c src/tesseract.c src/main.c -lm -lraylib -o bin/debug

// run:
// bin/debug -m <mesh> -s <speed> -a <acceleration> -c <clone> -d <delta> -w <windowsize>

int main(int argc, char **argv) {

    Data data;
    readInputFrom(argc, argv, &data);

    for (int i = 0; i < data.clone; i++) {
        renderCube(data, i);
    }

    return 0;
}