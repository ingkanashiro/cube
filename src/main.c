#include <raylib.h>
#include <math.h>

#define WIDTH 480
#define HEIGHT 480

#define L 75

#define INCLINATION PI / 3

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

/*  NOTE:
    Camera moves around the top side of the cube, pointing at the center (0, 0, 0). This movement draws a polar cap on 
    a 4 units-radius sphere that swallows the cube inside.
*/
void DrawCubeAtAngle(Vector3 A, Vector3 B, Vector3 C, Vector3 D, Vector3 E, Vector3 F, Vector3 G, Vector3 H, float angle) {
    // ABCD-EFGH at system XYZ with center at P = <ABCDEFGH>.
    // A'B'C'D'-E'F'G'H' 
    // projection to plane of center with spheric coordinates K(r, 45°, angle) and normal KP

    Vector3 i = {-1 * sin(angle), cos(angle), 0};
    Vector3 j;
    Vector3 k = normalise(getFromSpheric(1, angle, INCLINATION)); 
    
    j = crossProduct(k, i);

    Vector2 a, b, c, d, e, f, g, h;
    a = transform(A, i, j);
    b = transform(B, i, j);
    c = transform(C, i, j);
    d = transform(D, i, j);
    e = transform(E, i, j);
    f = transform(F, i, j);
    g = transform(G, i, j);
    h = transform(H, i, j);

    a.x += WIDTH/2;
    b.x += WIDTH/2;
    c.x += WIDTH/2;
    d.x += WIDTH/2;
    e.x += WIDTH/2;
    f.x += WIDTH/2;
    g.x += WIDTH/2;
    h.x += WIDTH/2;

    a.y += HEIGHT/2;
    b.y += HEIGHT/2;
    c.y += HEIGHT/2;
    d.y += HEIGHT/2;
    e.y += HEIGHT/2;
    f.y += HEIGHT/2;
    g.y += HEIGHT/2;
    h.y += HEIGHT/2;

    DrawCircle(a.x, a.y, 1, RAYWHITE);
    DrawCircle(b.x, b.y, 1, RAYWHITE);
    DrawCircle(c.x, c.y, 1, RAYWHITE);
    DrawCircle(d.x, d.y, 1, RAYWHITE);
    DrawCircle(e.x, e.y, 1, RAYWHITE);
    DrawCircle(f.x, f.y, 1, RAYWHITE);
    DrawCircle(g.x, g.y, 1, RAYWHITE);
    DrawCircle(h.x, h.y, 1, RAYWHITE);

    DrawLine(a.x, a.y, b.x, b.y, RAYWHITE);
    DrawLine(a.x, a.y, d.x, d.y, RAYWHITE);
    DrawLine(a.x, a.y, e.x, e.y, RAYWHITE);
    DrawLine(b.x, b.y, c.x, c.y, RAYWHITE);
    DrawLine(b.x, b.y, f.x, f.y, RAYWHITE);
    DrawLine(c.x, c.y, d.x, d.y, RAYWHITE);
    DrawLine(c.x, c.y, g.x, g.y, RAYWHITE);
    DrawLine(d.x, d.y, h.x, h.y, RAYWHITE);
    DrawLine(e.x, e.y, f.x, f.y, RAYWHITE);
    DrawLine(e.x, e.y, h.x, h.y, RAYWHITE);
    DrawLine(f.x, f.y, g.x, g.y, RAYWHITE);
    DrawLine(g.x, g.y, h.x, h.y, RAYWHITE);
}

int main() {

    InitWindow(WIDTH, HEIGHT, "cube");
    SetTargetFPS(60);

    // make a cube ABCD-EFGH
    Vector3 A = {L, L, -L}, B = {L, -L, -L}, C = {-L, -L, -L}, D = {-L, L, -L},
        E = {L, L, L}, F = {L, -L, L}, G = {-L, -L, L}, H = {-L, L, L}; 

    float angle = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        angle += 0.01;
        DrawCubeAtAngle(A, B, C, D, E, F, G, H, angle);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}