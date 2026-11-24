#include "../include/tesseract.h"

/*  NOTE:
    Camera moves around the top side of the cube, pointing at the center (0, 0, 0). This movement draws a polar cap on 
    a 4 units-radius sphere that swallows the cube inside.
*/

int renderCube(Data data, int iter) {

    SetTraceLogLevel(LOG_NONE);
    InitWindow(data.window_size, data.window_size, "cube");
    SetTargetFPS(60);

    float angle = 0;
    float speed = data.speed + (data.delta * iter);
    float acceleration = data.acceleration;

    if (data.mesh == NULL) {
        Vector3 A = {L, L, -L}, B = {L, -L, -L}, C = {-L, -L, -L}, D = {-L, L, -L},
            E = {L, L, L}, F = {L, -L, L}, G = {-L, -L, L}, H = {-L, L, L}; 

        while (!WindowShouldClose()) {
            BeginDrawing();

            ClearBackground(BLACK);

            angle += (0.01 * speed);
            speed += acceleration / 60;

            DrawCubeAtAngle(A, B, C, D, E, F, G, H, angle, data.window_size);

            EndDrawing();
        }

        CloseWindow();
    }
    else {
        Vector3 verteces[MAX_VERTECES];
        Edge edges[MAX_EDGES];

        int numVert, numEdge;

        if (!ReadMesh(data.mesh, &verteces, &edges, &numVert, &numEdge)) {
            return 1;
        }

        while (!WindowShouldClose()) {
            BeginDrawing();

            ClearBackground(BLACK);

            angle += (0.01 * speed);
            speed += acceleration / 60;
            
            DrawMeshAtAngle(verteces, numVert, edges, numEdge, angle, data.window_size);

            EndDrawing();
        }

        CloseWindow();
    }

    return 1;
}