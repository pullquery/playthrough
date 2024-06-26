#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#include <sys/ioctl.h>

#include "output.h"

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

void modeOutput(Output o) {
    char* mode = "REPEAT";

    for (int i = 0; i < o.width - strlen(mode) - 1; ++i) {
        printf(" ");
    }

    printf("%s ", mode);
}

void playingOutput(Output o, Audio a) {
    char* playing = a.name;

    for (int i = 0; i < o.width - strlen(playing) - 1; ++i) {
        printf(" ");
    }

    printf("%s ", playing);
}

void printOutput(Output o, Audio a, Directory d, int selected) {
    printf("\033[2J");
    printf("\033[H");

    modeOutput(o);

    for (int i = 0; i < d.size; ++i) {
        if (i == selected) {
            printf(">");
        } else {
            printf(" ");
        }

        if (strncmp(d.files[i], ".", 1) == 0) {
            beginGrey();
        }

        printf("%s", d.files[i]);

        if (isDirectory(d.files[i]) == 1) {
            beginGrey();
            printf("/");
            reset();
        }

        printf("\n");

        reset();
    }

    for (int i = 0; i < o.height - d.size - 2; ++i) {
        printf("\n");
    }

    // playingOutput(o, a);

    fflush(stdout);
}
