#include "../include/input.h"
#include <raylib.h>

int ReadMesh(char *argv, Vector3 **verteces, Edge **edges, int *v, int *e) {

    FILE *file = fopen(argv, "r");

    if (file == NULL) {
        printf("file not found.\n");
        return 0;
    }

    fscanf(file, "%d", v);

    for (int l = 0; l < *v; l++) {
        float x, y, z;
        fscanf(file, "%f %f %f", &x, &y, &z);

        Vector3 vertex = {
            x, y, -1 * z
        };

        (*verteces)[l] = scale(vertex, SCALE_FACTOR);
    }

    fscanf(file, "%d", e);

    for (int q = 0; q < *e; q++) {
        int a, b;
        fscanf(file, "%d %d", &a, &b);

        Edge edge = {
            a, b
        };

        (*edges)[q] = edge;
    }

    fclose(file);

    return 1;
}

int readInputFrom(int argc, char **argv, Data *data) {

    if (argc % 2 == 0) {
        printf("syntax error: mismatched flags and arguments.\n");
        return 0;
    }

    Data temp = {
        NULL,
        NULL,
        1,
        1.0,
        0.0,
        0.0,
        1.0,
        480
    };

    for (int i = 1; i < argc; i += 2) {

        if (strlen(argv[i]) != 2 || argv[i][0] != '-') {
            printf("syntax error: unknown flag '%s'.\n", argv[i]);
            return 0;
        }

        switch (argv[i][1]) {
            case 'm':
                // mesh: the path to the input file
                temp.mesh = malloc(128 * 128 * sizeof(char));
                char buffer[128];

                int count = 0;

                int v = 0;
                for (int c = 0;; c++) {

                    if (argv[i+1][c] == '\0') {

                        buffer[v] = '\0';
                        temp.mesh[count] = strdup(buffer);

                        printf("str%d: %s\n", count, buffer);

                        count++;
                        break;
                    }

                    if (*(argv[i+1] + c) == ',') {
                        buffer[v] = '\0';
                        temp.mesh[count] = strdup(buffer);

                        count++;
                        v = 0;
                    }
                    else {
                        buffer[v] = *(argv[i+1] + c);
                        v++; 
                    }
                }

                temp.shape_count = count;
                break;

            case 's':
                // speed: the starting speed of spin
                if (sscanf(argv[i+1], "%f", &(temp.speed)) != 1) {
                    printf("syntax error: unexpected argument type for flag '-s'. expected float.\n");
                    return 0;
                }
                break;

            case 'a':
                // acceleration: the acceleration of spin
                if (sscanf(argv[i+1], "%f", &(temp.acceleration)) != 1) {
                    printf("syntax error: unexpected argument type for flag '-a'. expected float.\n");
                    return 0;
                }
                break;

            case 'c':
                // color: color for each mesh 
                temp.colors = calloc(temp.shape_count, sizeof(Color));

                if (strlen(argv[i+1]) < 2 * temp.shape_count - 1) {
                    printf("syntax error: too few arguments for flag '-c'. arguments must match nmemb at '-m'.\n");
                    return 0;
                }
                for (int iter = 0; iter < temp.shape_count; iter++) {

                    if (argv[i+1][2*iter + 1] != '\0' && argv[i+1][1] != ',') {
                        printf("syntax error: parsing error for flag '-c'. bad separators, use commas.\n");
                        return 0;
                    }

                    int color = argv[i+1][2*iter] - '0';

                    if (color < 0 || color > 7) {
                        printf("syntax error: unexpected argument type for flag '-c'. no such color.\n");
                        return 0;
                    }

                    switch (color) {
                        case 0:     temp.colors[iter] = (Color){205, 214, 244, 255};    break;  // white
                        case 1:     temp.colors[iter] = (Color){203, 166, 247, 255};    break;  // mauve
                        case 2:     temp.colors[iter] = (Color){243, 139, 168, 255};    break;  // red
                        case 3:     temp.colors[iter] = (Color){250, 179, 135, 255};    break;  // peach
                        case 4:     temp.colors[iter] = (Color){249, 226, 175, 255};    break;  // yellow
                        case 5:     temp.colors[iter] = (Color){166, 227, 161, 255};    break;  // green
                        case 6:     temp.colors[iter] = (Color){148, 226, 213, 255};    break;  // teal
                        case 7:     temp.colors[iter] = (Color){137, 180, 250, 255};    break;  // blue
                    }
                }

                break;

            case 'p':
                // phase: the fraction of starting rotation (0 == 1)
                if (sscanf(argv[i+1], "%f", &(temp.phase)) != 1) {
                    printf("syntax error: unexpected argument type for flag '-p'. expected float.\n");
                    return 0;
                }

                if (temp.phase >= 1 || temp.phase < 0) {
                    float starting_phase = temp.phase;

                    while (starting_phase >= 1) {
                        starting_phase--;
                    }

                    while (starting_phase < 0) {
                        starting_phase++;
                    }
                    
                    printf(
                        "warning: phase expected float in range 0..1 (1 exclusive), but got %f. phase will be normalised to %f\n",
                        temp.phase,
                        starting_phase
                    );

                    temp.phase = starting_phase;
                }
                break;

            case 'z':
                if (sscanf(argv[i+1], "%f", &(temp.zoom_level)) != 1) {
                    printf("syntax error: unexpected argument type for flag '-z'. expected float.\n");
                    return 0;
                }
                break;

            case 'w':
                // window_size: the side lenght of the window. window is always square
                if (sscanf(argv[i+1], "%d", &(temp.window_size)) != 1) {
                    printf("syntax error: unexpected argument type for flag '-w'. expected int.\n");
                    return 0;
                }
                
                int window_suggested[] = {
                    144, 360, 480, 720, 1080 
                };

                int dif = -1, prev = -1;

                for (int i = 0; i < 5; i++) {
                    prev = dif;
                    dif = temp.window_size - window_suggested[i];

                    if (dif == 0) {
                        // all good!
                        break;
                    }
                    else if (dif < 0) {
                        // gone over!

                        if (-1 * dif > prev && prev != -1) {
                            printf("warning: irregular screen resolution. suggested: %d.\n", window_suggested[i-1]);
                        }
                        else {
                            printf("warning: irregular screen resolution. suggested: %d.\n", window_suggested[i]);
                        }

                        break;
                    }

                    if (i == 4) {
                        printf("warning: screen resolution might be too big. suggested: %d.\n", window_suggested[4]);
                    }
                }
                break;

            default:
                printf("syntax error: unknown flag '%s'.\n", argv[i]);
                return 0;
                break;
        }
    }

    *data = temp;
    return 1;
}