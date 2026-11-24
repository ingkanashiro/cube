#include "../include/input.h"

int ReadMesh(char *argv, Vector3 (*verteces)[256], Edge (*edges)[512], int *v, int *e) {

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
        printf("syntax error: mismatched arguments and flags.\n");
        return 0;
    }

    Data temp = {
        NULL,
        1,
        0,
        0,
        1,
        480
    };

    for (int i = 1; i < argc; i += 2) {

        if (strlen(argv[i]) != 2 || argv[i][0] != '-') {
            printf("syntax error: unknown flag '%s'.\n", argv[i+1]);
            return 0;
        }

        switch (argv[i][1]) {
            case 'm':
                // mesh: the path to the input file
                temp.mesh = strdup(argv[i+1]);
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
                // clone: how many copies of the cube will be displayed 
                if (sscanf(argv[i+1], "%d", &(temp.clone)) != 1) {
                    printf("syntax error: unexpected argument type for flag '-c'. expected int.\n");
                    return 0;
                }
                break;

            case 'd':
                // delta: the variation in starting speed per clone
                if (sscanf(argv[i+1], "%f", &(temp.delta)) != 1) {
                    printf("syntax error: unexpected argument type for flag '-d'. expected float.\n");
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
                printf("syntax error: unknown flag '%s'.\n", argv[i+1]);
                return 0;
                break;
        }
    }

    *data = temp;
    return 1;
}