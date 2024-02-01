#include <stdio.h>

#include "audio.h"
#include "directory.h"

int main(int argc, char** argv) {
    initSDL("Playthrough");

	Directory d;
	d.name = argv[1];

	while (1) {
		initDirectory(&d);
		printDirectory(d);
		freeDirectory(&d);

		char query[1024];
		printf(">> ");
		scanf("%s", query);
		printf("\n");

		// Cannot read
		if (!isReadable(query)) {
			continue;
		}

		// Play audio
		if (!isDirectory(query)) {
			Audio a;
			a.name = query;

			initAudio(a.name);
			loadAudio(&a);
			playAudio(&a);
			controlAudio(&a);
			freeAudio(&a);

			continue;
		}

		// Go to directory
		d.name = query;
	}

	return 0;
}
