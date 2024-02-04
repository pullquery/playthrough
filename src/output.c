#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/ioctl.h>

typedef struct {
    int row;
    int column;
    char* output;
} Output;

typedef struct {
    int startX, startY;
    int endX, endY;
} Area;

void initOutput(Output* o) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    o->row = w.ws_row;
    o->column = w.ws_col;
    o->output = calloc(o->row * o->column, sizeof(int));

    memset(o->output, ' ', o->row * o->column * sizeof(o->output[0]));
}

int getIndex(Output o, int r, int c) {
    return o.column * r + c;
}

void renderArea(Output* o, Area a) {
    o->output[getIndex(*o, a.startY, a.startX)] = '+';
    o->output[getIndex(*o, a.startY, a.endX)] = '+';
    for (int x = a.startX + 1; x < a.endX; ++x) {
        o->output[getIndex(*o, a.startY, x)] = '-';
    }

    for (int y = a.startY + 1; y < a.endY; ++y) {
        o->output[getIndex(*o, y, a.startX)] = '|';
        o->output[getIndex(*o, y, a.endX)] = '|';
    }

    o->output[getIndex(*o, a.endY, a.startX)] = '+';
    o->output[getIndex(*o, a.endY, a.endX)] = '+';
    for (int x = a.startX + 1; x < a.endX; ++x) {
        o->output[getIndex(*o, a.endY, x)] = '-';
    }

    // clear inside
}

void renderInformation(Output *o, Area a) {
    renderArea(o, a);
}

void renderDirectory(Output* o, Area a, char** list, int size) {
    renderArea(o, a);

    for (int r = 0; r < size; ++r) {
        int index = getIndex(*o, a.startY + 1 + r, a.startX + 1);

        int c = 0;
        while (list[r][c]) {
            ++index;
            o->output[index] = list[r][c];
            ++c;
        }
    }
}

void renderProgress(Output* o, Area a, double position, double length) {
    renderArea(o, a);

    double progress = position / length;

    int size = a.endX - a.startX;
    int point = size * progress;

    for (int c = 0; c < point - 1; ++c) {
        int index = getIndex(*o, a.startY + 1, a.startX + 1 + c);
        o->output[index] = '/';
    }
}

void printOutput(Output o) {
    for (int r = 0; r < o.row; ++r) {
        for (int c = 0; c < o.column; ++c) {
            long index = getIndex(o, r, c);
            putchar(o.output[index]);
        }
    }
}

void freeOutput(Output* o) {
    free(o->output);
}

int main() {
    Output current;
    initOutput(&current);

    Area informationArea = {
        0, 0,
        current.column * 0.4, current.row - 4
    };
    renderInformation(&current, informationArea);

    Area directoryArea = {
        current.column * 0.4 + 1, 0,
        current.column - 1, current.row - 4
    };
    char* list[] = {"one", "two", "three", "four", "five", "six"};
    renderDirectory(&current, directoryArea, list, sizeof(list) / sizeof(list[0]));

    Area progressArea = {
        0, current.row - 3,
        current.column - 1, current.row - 1
    };
    renderProgress(&current, progressArea, 30.0, 300.0);

    printOutput(current);
    freeOutput(&current);
    getchar();

    return 0;
}