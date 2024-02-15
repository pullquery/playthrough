#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

#include <sys/stat.h>

#include "directory.h"

void initDirectory(Directory* d) {
	if (chdir(d->name) == -1) {
		perror("cannot change current working directory");
	}

	DIR* stream = opendir(".");
	if (stream == NULL) {
		perror("cannot open directory");
	}

	struct dirent** entries;
	int size = scandir(".", &entries, 0, alphasort);
	if (size < 0) {
		perror("cannot read directory");
	} else {
		d->size = size;
	}

	char** files = calloc(d->size, sizeof(char**));
	if (files == NULL) {
		perror("cannot allocate memory for file name list");
	} else {
		d->files = files;
		for (int i = 0; i < d->size; ++i) {
			d->files[i] = entries[i]->d_name;
		}
	}

	if (closedir(stream) == -1) {
		perror("cannot close directory");
	}
}

void freeDirectory(Directory* d) {
	free(d->files);
}

int isDirectory(char* name) {
	struct stat status;

	if (stat(name, &status) != 0) {
		perror("cannot get status of file");
	}

	return S_ISDIR(status.st_mode) == 1;
}

int isReadable(char* name) {
	int ok = access(name, R_OK);

	if (ok == -1) {
		perror("cannot test for access to file");
	}

	return ok == 0;
}
