#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <dirent.h>
#include <sys/stat.h>

typedef struct {
	char* name;
	int size;
	char** files;
} Directory;

void initDirectory(Directory* d) {
	chdir(d->name);

	DIR* stream = opendir(".");
	struct dirent** entries;

	d->size = scandir(".", &entries, 0, alphasort);

	d->files = calloc(d->size, sizeof(char**));
	for (int i = 0; i < d->size; ++i) {
		d->files[i] = entries[i]->d_name;
	}

	closedir(stream);
}

void printDirectory(Directory d) {
	for (int i = 0; i < d.size; ++i) {
		printf("%s\n", d.files[i]);
	}
}

void freeDirectory(Directory* d) {
	free(d->files);
}

