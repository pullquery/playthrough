typedef struct {
	char* name;
	int size;
	char** files;
} Directory;

void initDirectory(Directory* d);

void printDirectory(Directory d);

void freeDirectory(Directory* d);