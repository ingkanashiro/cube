#include "../include/sphere.h"

Vector3 getFromSpheric(float r, float angular, float azimuthal) {
    float x, y, z;

    x = r * cos(angular) * sin(azimuthal);
    y = r * sin(angular) * sin(azimuthal);
    z = r * cos(azimuthal);

    Vector3 v = {x, y, z};
    return v;
}

Vector3 scale(Vector3 vec, float factor) {
    Vector3 rev = {
        vec.x * factor,
        vec.y * factor,
        vec.z * factor
    };
    return rev;
}

Vector3 normalise(Vector3 vec) {
    float modulus = sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
    return scale(vec, 1.0 / modulus);
}

Vector3 crossProduct(Vector3 a, Vector3 b) {
    Vector3 r = {
        a.y * b.z - b.y * a.z,
        a.z * b.x - b.z * a.x,
        a.x * b.y - b.x * a.y
    };

    return r;
}

Vector2 transform(Vector3 vec, Vector3 i, Vector3 j) {
    Vector2 result = {
        i.x * vec.x + i.y * vec.y + i.z * vec.z,
        j.x * vec.x + j.y * vec.y + j.z * vec.z
    };
    return result;
}