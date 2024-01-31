int main(int argc, char** argv) {
	return 0;
}

/*
#include <stdio.h>

#include "directory.h"

int main(int argc, char** argv) {
	Directory current;
	current.name = argv[1];

	while (1) {
		initDirectory(&current);
		printDirectory(current);
		freeDirectory(&current);

		char query[4096];
		printf(">> ");
		scanf("%s", query);
		printf("\n");

		current.name = query;
	}

	return 0;
}
*/

/*
#include "audio.h"

int main(int argc, char** argv) {
    initSDL("Playthrough");

    Audio current;
    current.name = argv[1];

    initAudio(current.name);
    loadAudio(&current);
    playAudio(&current);
    controlAudio(&current);
    freeAudio(&current);

    return 0;
}
*/
