#include "../include/tesseract.h"

/*  NOTE:
    Camera moves around the top side of the cube, pointing at the center (0, 0, 0). This movement draws a polar cap on 
    a 4 units-radius sphere that swallows the cube inside.
*/

int renderMesh(Data data) {

    SetTraceLogLevel(LOG_NONE);
    InitWindow(data.window_size, data.window_size, "cube");
    SetTargetFPS(60);

    float angle = data.phase * (2 * PI);
    float speed = data.speed;
    float acceleration = data.acceleration;

    if (data.mesh == NULL) {
        Vector3 A = {L, L, -L}, B = {L, -L, -L}, C = {-L, -L, -L}, D = {-L, L, -L},
            E = {L, L, L}, F = {L, -L, L}, G = {-L, -L, L}, H = {-L, L, L}; 

        A = scale(A, data.zoom_level);
        B = scale(B, data.zoom_level);
        C = scale(C, data.zoom_level);
        D = scale(D, data.zoom_level);
        E = scale(E, data.zoom_level);
        F = scale(F, data.zoom_level);
        G = scale(G, data.zoom_level);
        H = scale(H, data.zoom_level);

        while (!WindowShouldClose()) {
            BeginDrawing();

            ClearBackground(BLACK);

            angle += (0.01 * speed);
            speed += acceleration / 60;

            DrawCubeAtAngle(
                A, B, C, D, E, F, G, H, angle,
                data.window_size, 
                (data.colors == NULL) ? (Color){205, 214, 244, 255} : data.colors[0]
            );

            EndDrawing();
        }

        CloseWindow();
    }
    else {

        CubeMesh *meshArray = calloc(64, sizeof(CubeMesh));

        for (int iter = 0; iter < data.shape_count; iter++) {

            Vector3 *verteces = calloc(MAX_VERTECES, sizeof(Vector3));
            Edge *edges = calloc(MAX_EDGES, sizeof(Edge));

            int numVert, numEdge;

            if (!ReadMesh(data.mesh[iter], &verteces, &edges, &numVert, &numEdge)) {
                printf("syntax error: error parsing mesh with id=%d.\n", iter);
                return 1;
            }
            
            for (int i = 0; i < numVert; i++) {
                verteces[i] = scale(verteces[i], data.zoom_level);
            }

            CubeMesh mesh = {
                verteces,
                edges,
                numVert,
                numEdge
            };

            meshArray[iter] = mesh;
        }

        while (!WindowShouldClose()) {
            BeginDrawing();

            ClearBackground(BLACK);

            angle += (0.01 * speed);
            speed += acceleration / 60;
            
            for (int iter = 0; iter < data.shape_count; iter++) {
                DrawMeshAtAngle(
                    meshArray[iter].verteces, 
                    meshArray[iter].numVert, 
                    meshArray[iter].edges, 
                    meshArray[iter].numEdge, 
                    angle, 
                    data.window_size,
                    (data.colors == NULL) ? (Color){205, 214, 244, 255} : data.colors[iter]
                );
            }
            EndDrawing();
        }

        CloseWindow();
    }

    return 1;
}