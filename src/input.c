#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#include "types.h"

void setInput() {
    struct termios attr;
    tcgetattr(STDIN_FILENO, &attr);
    attr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &attr);
}

long readInput(char* buffer, long length) {
    return read(STDIN_FILENO, buffer, length);
}

void printInput(char* buffer, long length) {
    for (long i = 0; i < length; ++i) {
        printf("%ld: %d\n", i, buffer[i]);
    }
}

Direction controlInput(char* buffer, long length) {
    if (
        strncmp(buffer, "h", length) == 0 ||
        strncmp(buffer, "H", length) == 0
    ) {
        return LEFT;
    }

    if (
        strncmp(buffer, "j", length) == 0 ||
        strncmp(buffer, "J", length) == 0
    ) {
        return DOWN;
    }

    if (
        strncmp(buffer, "k", length) == 0 ||
        strncmp(buffer, "K", length) == 0
    ) {
        return UP;
    }

    if (
        strncmp(buffer, "l", length) == 0 ||
        strncmp(buffer, "L", length) == 0
    ) {
        return RIGHT;
    }

    return NOPE;
}

int main(int argc, char **argv) {
    setInput();

    char buffer[16];
    long length = 16;
    long size;

    while (
        (size = readInput(buffer, length)) > 0
    ) {
        // printInput(buffer, size);
        switch (controlInput(buffer, size)) {
            case UP:
                printf("UP\n");
                break;
            case DOWN:
                printf("DOWN\n");
                break;
            case LEFT:
                printf("LEFT\n");
                break;
            case RIGHT:
                printf("RIGHT\n");
                break;
            case NOPE:
                printf("NOPE\n");
                break;
        }
    }

    return 0;
}