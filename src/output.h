#include "audio.h"
#include "directory.h"

typedef struct {
    int width;
    int height;
} Output;

void initOutput(Output* o);

void printOutput(Output o, Audio a, Directory d, int selected);
