#ifndef CUBE_INPUT_H
#define CUBE_INPUT_H

#include "../include/sphere.h"
#include "../include/const.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {    
    char** mesh;
    Color* colors;
    int shape_count;
    float speed, acceleration, phase, zoom_level;

    int window_size;
} Data;

typedef struct mesh {
    Vector3* verteces;
    Edge* edges;
    int numVert, numEdge;
} CubeMesh;

int ReadMesh(char *argv, Vector3 **verteces, Edge **edges, int *v, int *e);
int readInputFrom(int argc, char **argv, Data *data);

#endif