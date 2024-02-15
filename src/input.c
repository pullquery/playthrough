#include <string.h>
#include <unistd.h>
#include <termios.h>

#include "input.h"

void initInput() {
    struct termios attr;
    tcgetattr(STDIN_FILENO, &attr);
    attr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &attr);
}

void freeInput() {
    struct termios attr;
    tcgetattr(STDIN_FILENO, &attr);
    attr.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &attr);
}

int readInput(char* buffer, long length) {
    return read(STDIN_FILENO, buffer, length);
}

Input controlInput(char* buffer, long length) {
    if (strncmp(buffer, "h", length) == 0) {
        return LEFT;
    }

    if (strncmp(buffer, "j", length) == 0) {
        return DOWN;
    }

    if (strncmp(buffer, "k", length) == 0) {
        return UP;
    }

    if (strncmp(buffer, "l", length) == 0) {
        return RIGHT;
    }

    return NOPE;
}
