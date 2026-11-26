#ifndef CUBE_SQUARE_H
#define CUBE_SQUARE_H

#include "../include/const.h"
#include "../include/sphere.h"
#include <stdlib.h>

void DrawCubeAtAngle(Vector3 A, Vector3 B, Vector3 C, Vector3 D, Vector3 E, Vector3 F, Vector3 G, Vector3 H, float angle, float window_size, Color color);
void DrawMeshAtAngle(Vector3 *verteces, int vertex_count, Edge *edges, int edge_count, float angle, float window_size, Color color);

#endif