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

	initAudio("Playthrough");

	Directory d;
	d.name = ".";
	initDirectory(&d);

	Output o;
	initOutput(&o);

	initInput();
    char buffer[16];
    long length = 16;
    long size;

	int selected = 0;
	directoryOutput(o, d.files, d.size, selected);

    while ((size = readInput(buffer, length)) > 0) {
        switch (controlInput(buffer, size)) {
            case UP:
				if (selected == 0) break;
				selected--;
                break;
            case DOWN:
				if (selected == d.size - 1) break;
				selected++;
                break;
            case LEFT:
				d.name = "..";
				selected = 0;
                break;
            case RIGHT:
				d.name = d.files[selected];
				if (isDirectory(d.name)) selected = 0;
                break;
            case NOPE:
                break;
        }

		if (!isDirectory(d.name)) {
			Audio a;
			a.name = d.name;

			freeAudio(&a);
			openAudio(a.name);
			loadMusic(&a);
			playMusic(&a);

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
