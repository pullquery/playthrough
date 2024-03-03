#include <stdlib.h>

#include "output.h"
#include "input.h"

void defer() {
	freeInput();
    exit(0);
}

int main(int argc, char** argv) {
	atexit(defer);

	initAudio("Playthrough");
	Audio a;
	a.name = "";

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
	printOutput(o, a, d, selected);

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
			a.name = d.name;

			freeAudio(&a);
			openAudio(a.name);
			loadMusic(&a);
			playMusic(&a);

			printOutput(o, a, d, selected);
			d.name = ".";
			continue;
		}

		initDirectory(&d);
		initOutput(&o);
		printOutput(o, a, d, selected);
		d.name = ".";
    }

	freeDirectory(&d);
	return 0;
}
