#include <stdlib.h>

#include "audio.h"
#include "directory.h"
#include "output.h"
#include "input.h"

void defer() {
	freeInput();
    exit(0);
}

int main(int argc, char** argv) {
	atexit(defer);

	Directory d;
	Output o;

	initSDL("Playthrough");

	initInput();
    char buffer[16];
    long length = 16;
    long size;

	int selected = 0;

	d.name = ".";
	initDirectory(&d);
	initOutput(&o);
	directoryOutput(o, d.files, d.size, selected);


    while ((size = readInput(buffer, length)) > 0) {
        switch (controlInput(buffer, size)) {
            case UP:
				selected--;
                break;
            case DOWN:
				selected++;
                break;
            case LEFT:
				d.name = "..";
				selected = 0;
                break;
            case RIGHT:
				d.name = d.files[selected];
				selected = 0;
                break;
            case NOPE:
                break;
        }

		if (!isDirectory(d.name)) {
			Audio a;
			a.name = d.name;

			initAudio(a.name);
			loadAudio(&a);
			playAudio(&a);
			// controlAudio(&a);
			// freeAudio(&a);

			d.name = ".";
			continue;
		}

		initDirectory(&d);
		initOutput(&o);
		directoryOutput(o, d.files, d.size, selected);
		d.name = ".";
    }

	freeDirectory(&d);
	return 0;
}
