#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#include <sys/ioctl.h>

typedef struct {
    int width;
    int height;
} Output;

void initOutput(Output* o) {
    struct winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);

    o->width = (int) win.ws_col;
    o->height = (int) win.ws_row;
}

void printOutput(Output o, char** list, int size, int selected) {
    printf("\n");

    for (int i = 0; i < size; ++i) {
        if (i == selected) {
            printf(">>");
        }

        printf(" ");
        printf("%s\n", list[i]);
    }

    for (int i = 0; i < o.height - size - 2; ++i) {
        printf("\n");
    }
}
