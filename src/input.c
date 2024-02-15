#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#include <sys/types.h>

#include "input.h"

void initInput() {
    struct termios attr;
    if (tcgetattr(STDIN_FILENO, &attr) == -1) {
        perror("cannot get terminal attribute");
    }

    attr.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &attr) == -1) {
        perror("cannot set terminal attribute");
    }
}

void freeInput() {
    struct termios attr;
    if (tcgetattr(STDIN_FILENO, &attr) == -1) {
        perror("cannot get terminal attribute");
    }

    attr.c_lflag |= (ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &attr) == -1) {
        perror("cannot set terminal attribute");
    }
}

ssize_t readInput(char* buffer, size_t length) {
    ssize_t size = read(STDIN_FILENO, buffer, length);

    if (size == -1) {
        perror("cannot read keyboard input from standard input");
    }

    return size;
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
