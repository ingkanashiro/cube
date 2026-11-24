#ifndef CUBE_SPHERE_H
#define CUBE_SPHERE_H

#include <raylib.h>
#include <math.h>

Vector3 getFromSpheric(float r, float angular, float azimuthal);
Vector3 scale(Vector3 vec, float factor);
Vector3 normalise(Vector3 vec);

Vector3 crossProduct(Vector3 a, Vector3 b);
Vector2 transform(Vector3 vec, Vector3 i, Vector3 j);

typedef struct {
    int origin, dest;
} Edge;

#endif