typedef struct {
    int width;
    int height;
} Output;

void initOutput(Output* o);

void directoryOutput(Output o, char** list, int size, int selected);
