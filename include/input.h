#ifndef CUBE_INPUT_H
#define CUBE_INPUT_H

#include "../include/sphere.h"
#include "../include/const.h"
#include <stdio.h>
#include <string.h>

typedef struct data {    
    char *mesh;
    float speed, acceleration, delta, phase, zoom_level;
    int clone;

    int window_size;
} Data;

int ReadMesh(char *argv, Vector3 (*verteces)[256], Edge (*edges)[512], int *v, int *e);
int readInputFrom(int argc, char **argv, Data *data);

#endif