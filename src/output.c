#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#include <sys/ioctl.h>

#include "output.h"

#include "directory.h"

void initOutput(Output* o) {
    struct winsize win;
    int ok = ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);

    if (ok == -1) {
        perror("cannot get terminal size");
    }

    o->width = (int) win.ws_col;
    o->height = (int) win.ws_row;
}

void beginGrey() {
    printf("\033[90m");
}

void beginBold() {
    printf("\033[1m");
}

void reset() {
    printf("\033[0m");
}

void directoryOutput(Output o, char** list, int size, int selected) {
    printf("\n");

    for (int i = 0; i < size; ++i) {
        if (i == selected) {
            printf(">");
        } else {
            printf(" ");
        }


        if (strncmp(list[i], ".", 1) == 0) {
            beginGrey();
        }

        printf("%s", list[i]);

        if (isDirectory(list[i]) == 1) {
            beginGrey();
            printf("/");
            reset();
        }

        printf("\n");

        reset();
    }

    for (int i = 0; i < o.height - size - 2; ++i) {
        printf("\n");
    }
}
