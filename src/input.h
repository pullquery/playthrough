#include <sys/types.h>

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NOPE,
} Input;

void initInput();

void freeInput();

ssize_t readInput(char* buffer, size_t length);

Input controlInput(char* buffer, long length);
