typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NOPE,
} Input;

void initInput();

void freeInput();

int readInput(char* buffer, long length);

Input controlInput(char* buffer, long length);
