typedef struct {
	char* name;
	int size;
	char** files;
} Directory;

void initDirectory(Directory* d);

void freeDirectory(Directory* d);

int isDirectory(char* name);

int isReadable(char* name);