typedef struct {
    int width;
    int height;
} Output;

void initOutput(Output* o);

void printOutput(Output o, char** list, int size, int selected);
