#include "../include/square.h"

void DrawCubeAtAngle(Vector3 A, Vector3 B, Vector3 C, Vector3 D, Vector3 E, Vector3 F, Vector3 G, Vector3 H, float angle, float window_size, Color color) {
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

    a.x += window_size/2;
    b.x += window_size/2;
    c.x += window_size/2;
    d.x += window_size/2;
    e.x += window_size/2;
    f.x += window_size/2;
    g.x += window_size/2;
    h.x += window_size/2;

    a.y += window_size/2;
    b.y += window_size/2;
    c.y += window_size/2;
    d.y += window_size/2;
    e.y += window_size/2;
    f.y += window_size/2;
    g.y += window_size/2;
    h.y += window_size/2;

    // DrawCircle(a.x, a.y, 1, RAYWHITE);
    // DrawCircle(b.x, b.y, 1, RAYWHITE);
    // DrawCircle(c.x, c.y, 1, RAYWHITE);
    // DrawCircle(d.x, d.y, 1, RAYWHITE);
    // DrawCircle(e.x, e.y, 1, RAYWHITE);
    // DrawCircle(f.x, f.y, 1, RAYWHITE);
    // DrawCircle(g.x, g.y, 1, RAYWHITE);
    // DrawCircle(h.x, h.y, 1, RAYWHITE);

    DrawLine(a.x, a.y, b.x, b.y, color);
    DrawLine(a.x, a.y, d.x, d.y, color);
    DrawLine(a.x, a.y, e.x, e.y, color);
    DrawLine(b.x, b.y, c.x, c.y, color);
    DrawLine(b.x, b.y, f.x, f.y, color);
    DrawLine(c.x, c.y, d.x, d.y, color);
    DrawLine(c.x, c.y, g.x, g.y, color);
    DrawLine(d.x, d.y, h.x, h.y, color);
    DrawLine(e.x, e.y, f.x, f.y, color);
    DrawLine(e.x, e.y, h.x, h.y, color);
    DrawLine(f.x, f.y, g.x, g.y, color);
    DrawLine(g.x, g.y, h.x, h.y, color);
}

void DrawMeshAtAngle(Vector3 *verteces, int vertex_count, Edge *edges, int edge_count, float angle, float window_size, Color color) {

    Vector3 i = {-1 * sin(angle), cos(angle), 0};
    Vector3 j;
    Vector3 k = normalise(getFromSpheric(1, angle, INCLINATION)); 
    
    j = crossProduct(k, i);

    Vector2 *points;
    points = malloc(vertex_count * sizeof(Vector3));

    for (int v = 0; v < vertex_count; v++) {
        points[v] = transform(verteces[v], i, j);

        points[v].x += window_size / 2;
        points[v].y += window_size / 2;
    }

    for (int l = 0; l < edge_count; l++) {
        DrawLine(
            points[edges[l].origin].x,
            points[edges[l].origin].y,
            points[edges[l].dest].x,
            points[edges[l].dest].y,
            color
        );
    }
}
